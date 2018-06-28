#include <iostream>

#ifdef _WIN32

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#include <windows.h>

#endif

#define DEFAULT_BUFLEN 512

using namespace std;


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


class App {

private:

    void process_received_message(char *recv_msg){

        int pos = 0;
        string command;


        while(recv_msg[pos] != ' '){
            command += recv_msg[pos];
            pos ++;
        }
        cout << "The command is: " << command << endl;

        if (command == "shutdown"){

            // The shutdown command is followed by the time set in the following format:
            // shutdown hh mm ss ms

            string s_hrs;
            string s_mins;
            string s_secs;
            string s_msecs;

            // advance to the next position of recv_msg (after space)
            pos ++;

            cout << "TEST: " << recv_msg[pos] << endl;

            // extract the hours number from recv_msg
            while(recv_msg[pos] != ' '){
                s_hrs += recv_msg[pos];
                pos ++;
            }

            cout << "s_hrs: " << s_hrs << endl;

            // advance to the next position of recv_msg (after space)
            pos ++;

            // extract the mins number from recv_msg
            while(recv_msg[pos] != ' '){
                s_mins += recv_msg[pos];
                pos ++;
            }

            cout << "s_mins: " << s_mins << endl;

            // advance to the next position of recv_msg (after space)
            pos ++;

            // extract the secs number from recv_msg
            while(recv_msg[pos] != ' '){
                s_secs += recv_msg[pos];
                pos ++;
            }

            cout << "s_secs: " << s_secs << endl;

            // advance to the next position of recv_msg (after space)
            pos ++;

            // extract the msecs number from recv_msg
            while(recv_msg[pos] != ' ' && recv_msg[pos] != '\0'){
                s_msecs += recv_msg[pos];
                pos ++;
            }

            cout << "s_msecs: " << s_msecs << endl;

            cout << "Time data extracted: " << stoi(s_hrs) << stoi(s_mins) << stoi(s_secs) << stoi(s_msecs) << endl;

            // call execute_sleep_timer() method
            this->execute_sleep_timer(TimeObject((unsigned int)stoi(s_hrs), (unsigned int)stoi(s_mins),
                                                 (unsigned int)stoi(s_secs), (unsigned int)stoi(s_msecs)));
        }
    }


    void remote_server(){
        // sets up a server used to listen for and accept commands from remote clients

        WSADATA wsa;
        SOCKET s , new_socket;
        struct sockaddr_in server , client;
        int c;
        char *message;
        unsigned short PORT = 7789;
        int recv_size;
        char recv_buf[DEFAULT_BUFLEN];
        int recv_buf_len = DEFAULT_BUFLEN;

        printf("\nInitialising Winsock...");
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d",WSAGetLastError());
        }
        printf("Initialised.\n");

        //Create a socket
        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d" , WSAGetLastError());
        }
        printf("Socket created.\n");

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);

        //Bind
        if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
        {
            printf("Bind failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        puts("Bind done");

        //Listen to incoming connections
        listen(s , 3);

        //Accept an incoming connection
        puts("Waiting for incoming connections...");

        c = sizeof(struct sockaddr_in);

        while ( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
        {
            puts("Connection accepted");

            // Receive the client message
            if((recv_size = recv(new_socket, recv_buf, recv_buf_len, 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
            }
            puts("Reply received\n");

            //Add a NULL terminating character to make it a proper string before printing
            recv_buf[recv_size] = '\0';
            puts(recv_buf);

            // Process the received message to determine the client's given command
            this->process_received_message(recv_buf);

            //Reply to the client
            message = "Hello Client , I have received your connection. But I have to go now, bye\n";
            send(new_socket , message , strlen(message) , 0);
        }

        if (new_socket == INVALID_SOCKET)
        {
            printf("accept failed with error code : %d" , WSAGetLastError());
        }

        closesocket(s);
        WSACleanup();
    }

    void execute_shutdown_command(){
        // -s is used for shutdown, -f is used to force shutdown,
        // preventing the computer from getting stuck from background applications.
        //system("shutdown -s -f");
        cout << "Diag: Shutdown would be executed here!";
    }

    void execute_sleep_timer(TimeObject time_data){
        // executes the sleep timer that puts the application in a hold
        // for a requested amount of time.

        cout << "get_msecs: " << time_data.get_msecs() << "\n";
        Sleep(time_data.get_msecs());
        this->execute_shutdown_command();
    }

public:

    App() {
        run();
    }

    void run(){
        //this->execute_sleep_timer(TimeObject(0,0,5,0));
        this->remote_server();
    }

};



int main() {

    App MainApp = App();


}