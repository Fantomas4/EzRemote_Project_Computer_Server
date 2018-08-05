#include <iostream>
#include "nlohmann/json.hpp"
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"

#ifdef _WIN32

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#include <windows.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>

#else

/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include <thread>

typedef int SOCKET;

#endif

#define DEFAULT_BUFLEN 512

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////

class TimeObject {
    // class used to save time data, such as hours, minutes, seconds, milliseconds

private:

    unsigned int hrs;
    unsigned int mins;
    unsigned int secs;
    unsigned int msecs;

public:

    unsigned int get_msecs(){
        // returns the saved time data, after converting it to milliseconds

        return (hrs * 60 * 60 * 1000) + (mins * 60 * 1000) + (secs * 1000) + (msecs);
    }

    TimeObject(){
        this->hrs = 0;
        this->mins = 0;
        this->secs = 0;
        this->msecs = 0;
    }

    TimeObject(unsigned int hrs, unsigned int mins, unsigned int secs, unsigned int msecs){
        this->hrs = hrs;
        this->mins = mins;
        this->secs = secs;
        this->msecs = msecs;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////

class App {

private:

    // states whether the server is currently connected to a client.
    bool static in_connection = false;
    // holds the ip of the client that the application is currently bonded to.
    string static ip_bond;

    /////////////////////////////////////////////////////////////////////////////////////
    // The messages between the server and the client are transmitted in JSON form, using the
    // following format:
    //
    // - msg_type: can either be "request" or "response"
    // - msg_content: describes the purpose of the message, the type of data it holds
    // - msg_data: the actual data the message contains, in JSON form.
    class MsgAnalysisThread {

    private:

        char *recv_msg;
        std::thread msg_analysis_thread;

        void process_received_message(char *recv_msg){

            using namespace nlohmann;

            // convert recv_msg to string
            string s_msg = recv_msg;

            json json_msg = json::parse(s_msg);

            string msg_type = json_msg["msg_type"];
            string msg_content = json_msg["msg_content"];
            json msg_data = json_msg["msg_data"];

            if (msg_type == "request"){

                if (msg_content == "make_connection") {

                    if(!in_connection) {
                        // checks whether the application is already connected to a client
                        in_connection = true;
                        ip_bond = msg_data["ip"];

                    }

                } else if (msg_content == "identify") {

                }

            } else if (msg_type == "response") {
                // Under Construction
            }




        }

    public:

        MsgAnalysisThread(char *recv_buf) {
            recv_msg = recv_buf;
            msg_analysis_thread = thread(process_received_message, this, recv_msg);
        }

//        void set_msg(char *recv_buf) {
//            // sets the msg that will be analyzed by the thread.
//            // MUST be called before start_thread()
//            recv_msg = recv_buf;
//        }
//
//        void start_thread() {
//            // starts the thread
//            msg_analysis_thread = thread(process_received_message, this, recv_msg);
//        }

    };

    /////////////////////////////////////////////////////////////////////////////////////

    class RemoteServer {
    private:
        // sets up a server used to listen for and accept commands from remote clients

        SOCKET s , new_socket;
        struct sockaddr_in server , client;
        //int c;
        socklen_t c;
//        char *message;
        string final_message;
        nlohmann::json json_message;
        unsigned short PORT = 7789;
        int recv_size;
        char recv_buf[DEFAULT_BUFLEN];
        int recv_buf_len = DEFAULT_BUFLEN;
        vector<MsgAnalysisThread> msg_analysis_threads;

        nlohmann::json generate_json_msg(string msg_type, string msg_content, map<string, string> data) {
            // msg_type is "request" or "response
            // msg_content describes the data content of the message
            // for example, identification_info

            nlohmann::json json_msg;

            json_msg = {
                    {"msg_type", msg_type},
                    {"msg_content", msg_content},
                    {"msg_data", data}
            };



            return json_msg;
        }

        int sockInit() {
            #ifdef _WIN32
                WSADATA wsa_data;
                return WSAStartup(MAKEWORD(1,1), &wsa_data);
            #else
                return 0;
            #endif
        }

        /* Note: For POSIX, typedef SOCKET as an int. */

        int sockClose(SOCKET sock) {

            int status = 0;

            #ifdef _WIN32
                status = shutdown(sock, SD_BOTH);
                if (status == 0) {
                    status = closesocket(sock);
                }
            #else
                status = shutdown(sock, SHUT_RDWR);
                if (status == 0) {
                    status = close(sock);
                }
            #endif

            return status;

        }

        int sockQuit() {
            #ifdef _WIN32
                return WSACleanup();
            #else
                return 0;
            #endif
        }

        void run() {
            printf("\nInitialising socket...");
            if (sockInit() != 0) {
                printf("Socket initialization failed.");
            }
            printf("Socket initialised!\n");

            //Create a socket
            if((s = socket(AF_INET , SOCK_STREAM , 0 )) == 0) {
                // 0 means INVALID_SOCKET in WinSock
                printf("Error. Could not create socket.");
            }
            printf("Socket created.\n");

            //Prepare the sockaddr_in structure
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(PORT);

            //Bind
            if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == -1) {
                printf("Socket bind failed.");
                exit(EXIT_FAILURE);
            }
            puts("Socket bind done");

            //Listen to incoming connections
            listen(s , 3);

            //Accept an incoming connection
            puts("Waiting for incoming connections...");

            c = sizeof(struct sockaddr_in);

            while ( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != 0 ) {

                // 0 means INVALID_SOCKET in WinSock

                puts("Connection accepted");

                // Receive the client message
                if((recv_size = recv(new_socket, recv_buf, recv_buf_len, 0)) == -1) {
                    // -1 means SOCKET_ERROR in WinSock
                    puts("Receive failed");
                }
                puts("Reply received!\n");

                //Add a NULL terminating character to make it a proper string before printing
                recv_buf[recv_size] = '\0';
                puts(recv_buf);

                // Process the received message to determine the client's given command
                msg_analysis_threads.emplace_back(MsgAnalysisThread(recv_buf));



                //Reply to the client
//                message = "Hello Client , I have received your connection. But I have to go now, bye\n";

                json_message = generate_json_msg("response", "id_info", CommandExec().get_identification_info());
                final_message = json_message.dump(4);

                cout << json_message.dump(4) << "\n";

                //send(new_socket , (const char *)&message , sizeof(message) , 0);


                // c_str() returns the contents of the string as a const char*
                // and the pointer it returns is valid as long as the given string object exists.
                send(new_socket , final_message.c_str(), final_message.size() , 0);
                cout << "============================================-1";
            }

            cout << "============================================-2";

            if (new_socket == 0) {
                // 0 means INVALID_SOCKET in WinSock
                printf("accept failed!");
            }

            sockClose(s);
            sockQuit();


        }

    public:
        RemoteServer() {
            run();
        }
    };



    /////////////////////////////////////////////////////////////////////////////////////
    class CommandExec {

    public:

        map<string, string> static get_identification_info() {
            string id;
            string ip;
            string status;
            map<string, string> info;

            //get computer name
            id = "test_computer_name";

            //get computer ip
            ip = "192.168.1.234";

            //get computer readiness status
            status = "Ready";

            info["id"] = id;
            info["ip"] = ip;
            info["status"] = status;

            return info;

        }

        void static execute_shutdown_command(TimeObject time_data){
            // executes the sleep timer that puts the application in a hold
            // for a requested amount of time.

            #ifdef _WIN32
                cout << "get_msecs: " << time_data.get_msecs() << "\n";
                Sleep(time_data.get_msecs());
            #else
                // usleep takes sleep time in us (1 millionth of a second)
                usleep(time_data.get_msecs() * 1000);   // usleep takes sleep time in us (1 millionth of a second)
            #endif

            // -s is used for shutdown, -f is used to force shutdown,
            // preventing the computer from getting stuck from background applications.
            //system("shutdown -s -f");
            cout << "Diag: Shutdown would be executed here!";
        }



    };

    /////////////////////////////////////////////////////////////////////////////////////

public:

    App() {
        run();
    }

    void run(){
        RemoteServer server = RemoteServer();
    }

};

/////////////////////////////////////////////////////////////////////////////////////////

int main() {

    App MainApp = App();


}