//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "RemoteServer.h"

#include <thread>
#include <mutex>

std::mutex recv_buffer_mutex;

RemoteServer::RemoteServer() {
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ DEFAULT CONSTRUCTOR *******************" << std::endl;
}

//RemoteServer::RemoteServer(App *app_obj) {
//
//    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ CUSTOM CONSTRUCTOR *******************" << std::endl;
//
//    this->app_ptr = app_obj;
//
//    this->final_message = "CUSTOM CONSTRUCTOR";
//
//}

RemoteServer& RemoteServer::getInstance() {
    static RemoteServer instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
    return instance;
}

int RemoteServer::sockInit() {
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
#else
    return 0;
#endif
}

/* Note: For POSIX, typedef SOCKET as an int. */

int RemoteServer::sockClose(SOCKET sock) {

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

int RemoteServer::sockQuit() {
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

////////////////// TEST TEST TEST ///////////////////////////////////////////////

int RemoteServer::Recv(char *recv_buf, int recv_buf_size) {

    // empty the recv_buf buffer by filling it with 0 (null)
    *recv_buf = {0};

    // For the client - server communication, "\0" (null) is used as delimiter. Since strlen("\0) is 0,
    // the message part that contains the delimiter (last message part) will cause the recv() function to
    // return an integer representing the actual number of chars received (example: "ty\0" returns 4), while
    // strlen() that ignores the null character will return an amount smaller than the chars actually received (for our example,
    // it would return 2).

    // temp_buf temporarily holds the last string message the recv() function has received from the client
    int temp_buf_size = 1000;
    char temp_buf[temp_buf_size];
    std::string s_recv_buf;

    int n = 0, total_size = 0;

    do {

        n = recv(this->new_socket, temp_buf, temp_buf_size, 0);
        total_size += n;

        // *** new addition
        if (n == 0) {
            break;
        }

        // create a temporary string to store the recv_buf char array as a string.
        s_recv_buf = recv_buf;
        // add the new message part received to the string of the whole message
        s_recv_buf += temp_buf;

        // convert string to char array and copy it to the original recv_buf
        recv_buffer_mutex.lock();
        strcpy(recv_buf, s_recv_buf.c_str());
        recv_buffer_mutex.unlock();

    } while(strlen(temp_buf) == n);

    std::cout << "------------------------------ I return from Recv... -----------------------------------------" << "\n\n";

    return total_size;
}

////////////////// TEST TEST TEST ///////////////////////////////////////////////

void RemoteServer::listen_thread() {

    printf("\nInitialising socket...");
    if (sockInit() != 0) {
        printf("Socket initialization failed.");
    }
    printf("Socket initialised!\n");

    //Create a socket
    if((this->s = socket(AF_INET , SOCK_STREAM , 0 )) == 0) {
        // 0 means INVALID_SOCKET in WinSock
        printf("Error. Could not create socket.");
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);



//    // ******* Start - Part used to reuse socket. Useful when application crashes during testing,
//    // causing the port to remain locked *******
//    int yes=1;
//    //char yes='1'; // Solaris people use this
//
//    // lose the pesky "Address already in use" error message
//    if (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
//        perror("setsockopt");
//        exit(1);
//    }
//    // ******* End *******




    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == -1) {
        printf("Socket bind failed.");
        exit(EXIT_FAILURE);
    }
    puts("Socket bind done");


//    // ************************************************************* TEST *************************************************************
//    // set options to new_socket
//    int val = 1;
//
//    // After creating the socket
//    if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char *)&val, sizeof(val))){
//        fprintf(stderr, "setsockopt failure : %d", errno);
//    }
//    // ************************************************************* TEST *************************************************************




    //Listen to incoming connections
    listen(s , 3);

    //Accept an incoming connection
    puts("Waiting for incoming connections...");

    this->c = sizeof(struct sockaddr_in);

    this->new_socket = accept(s , (struct sockaddr *)&client, &c);

    while (true) {
        std::cout << "****** Listen LOOP *********" << "\n\n";

        // 0 means INVALID_SOCKET in WinSock

        if((this->recv_size = Recv(recv_buf, recv_buf_len)) == -1) {
            // -1 means SOCKET_ERROR in WinSock
            puts("Receive failed");



            #ifdef _WIN32

            // Uh oh!  Something bad happened.  Let's
            // get the error code...
            int errCode = WSAGetLastError();

            // ..and the human readable error string!!
            // Interesting:  Also retrievable by net helpmsg 10060
            LPSTR errString = NULL;  // will be allocated and filled by FormatMessage

            int size = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                      FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
                                      0,       // 0 since source is internal message table
                                      errCode, // this is the error code returned by WSAGetLastError()
                    // Could just as well have been an error code from generic
                    // Windows errors from GetLastError()
                                      0,       // auto-determine language to use
                                      (LPSTR)&errString, // this is WHERE we want FormatMessage
                    // to plunk the error string.  Note the
                    // peculiar pass format:  Even though
                    // errString is already a pointer, we
                    // pass &errString (which is really type LPSTR* now)
                    // and then CAST IT to (LPSTR).  This is a really weird
                    // trip up.. but its how they do it on msdn:
                    // http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
                                      0,                 // min size for buffer
                                      0 );               // 0, since getting message from system tables
            printf( "Error code %d:  %s\n\nMessage was %d bytes, in case you cared to know this.\n\n", errCode, errString, size ) ;

            LocalFree( errString ) ; // if you don't do this, you will get an
            // ever so slight memory leak, since we asked
            // FormatMessage to FORMAT_MESSAGE_ALLOCATE_BUFFER,
            // and it does so using LocalAlloc
            // Gotcha!  I guess.

            #endif



        } else {
            // receive was successful
            std::cout << "RemoteServer.cpp : recv_buf is: " << this->recv_buf << std::endl;

            std::string s_received_msg = this->recv_buf;

            std::cout << "s_received_msg before sending it to func is: " << s_received_msg << std::endl;

            // Create a thread to process the received message and determine the client's given command
            // The thread is created by the MessageAnalysis Object, during its construction.
            std::cout << "================ Ftiaxnw thread gia message analysis ========================" << std::endl;

            // https://en.cppreference.com/w/cpp/container/vector/emplace_back?fbclid=IwAR3ndX0Q_Ar04zBdiaXJizIvjO6drKG1nxJ1EnIgyC5P35HJl15BW5L424U
            msg_analysis_threads.emplace_back(s_received_msg);

            if (terminate_server) {
                break;
            }
        }
    }

    std::cout << "============================================-2";

    if (new_socket == 0) {
        // 0 means INVALID_SOCKET in WinSock
        printf("accept failed!");
    }



    sockClose(s);
    sockQuit();
}

bool RemoteServer::isInConnection() {
    return in_connection;
}

std::string RemoteServer::getIpBondAddress() {
    return ip_bond;
}

void RemoteServer::setIpBondAddress(std::string ip) {
    ip_bond = ip;
}

void RemoteServer::setInConnectionValue(bool value) {
    in_connection = true;
}

void RemoteServer::run() {
    // listen_thread() will be executed as the main thread.
    listen_thread();

}

void RemoteServer::serverReply(nlohmann::json json_msg) {

    using namespace std;

    // converts the json data from outbound_json_buffer to a string,
    // then converts the string to const char* and assigns it to outbound_msg
    //
    // ATTENTION!
    // c_str() returns the contents of the string as a const char*
    // and the pointer it returns is valid as long as the given string object exists.

    std::string temp_s = json_msg.dump(4);

    const char *outbound_msg = temp_s.c_str();

//    cout << "***********************strlen(outbound_msg): " << strlen(outbound_msg) << endl;
    cout << "server outbound_msg is: " << endl;

    for (int i=0; i<strlen(outbound_msg); i++) {
        cout << outbound_msg[i];
    }

    send(this->new_socket , outbound_msg, strlen(outbound_msg) , 0);

    cout << "\n\n";

//    cout << "Sending a message with size: " << strlen(outbound_msg) << endl;
    cout << "(((((((((((((((((((((((((( SERVER REPLIED!";
}



