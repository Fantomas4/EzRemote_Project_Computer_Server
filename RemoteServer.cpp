//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "RemoteServer.h"

#include <thread>
#include <mutex>

std::mutex recv_buffer_mutex;

RemoteServer::RemoteServer(App *app_obj) {
    this->app_ptr = app_obj;
    run();
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
    string s_recv_buf;

    int n = 0, total_size = 0;

    do {
//        cout << "MPIKA" << "\n\n";
//        n = recv(this->new_socket, buf+total_size, buf_size-total_size-1, 0);
        n = recv(this->new_socket, temp_buf, temp_buf_size, 0);
        total_size += n;

        // *** new addition
        if (n == 0) {
            break;
        }

//        cout << "n is: " << n << "\n\n";
//        cout << "total_size is: " << total_size << "\n\n";
//        cout << "temp_buf is: " << temp_buf << "\n\n";

        // create a temporary string to store the recv_buf char array as a string.
        s_recv_buf = recv_buf;
        // add the new message part received to the string of the whole message
        s_recv_buf += temp_buf;

        // convert string to char array and copy it to the original recv_buf
        recv_buffer_mutex.lock();
        strcpy(recv_buf, s_recv_buf.c_str());
        recv_buffer_mutex.unlock();

//        cout << "strlen(temp_buf) is: " << strlen(temp_buf) << "\n\n";

    } while(strlen(temp_buf) == n);

    //buf[total] = 0;

    cout << "------------------------------ I return from Recv... -----------------------------------------" << "\n\n";

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

    // *** WARNING *** accept() should not be used like this when accepting a connection
    // from an already existing client socket, otherwise the program execution will get
    // stuck here.

    new_socket = accept(s , (struct sockaddr *)&client, &c);

//    while ( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != 0 ) {
    while (true) {
        cout << "****** Listen LOOP *********" << "\n\n";

        // 0 means INVALID_SOCKET in WinSock

//        puts("Connection accepted");

//        cout << "\n\nTEST BUFFER BEFORE RECV IS: " << recv_buf << "\n\n";

        if((recv_size = Recv(recv_buf, recv_buf_len)) == -1) {
            // -1 means SOCKET_ERROR in WinSock
            puts("Receive failed");
        }

//        cout << "recv_size is1: " << recv_size << "\n\n";
//        cout << "TEST BUFFER IS1: " << recv_buf << "\n\n";


        //Add a NULL terminating character to make it a proper string before printing
        //recv_buf[recv_size] = '\0';
        //puts(recv_buf);

        cout << "RemoteServer.cpp : recv_buf is: " << recv_buf << endl;

        string s_received_msg = recv_buf;

        cout << "s_received_msg before sending it to func is: " << s_received_msg << endl;

        // Create a thread to process the received message and determine the client's given command
        // The thread is created by the MessageAnalysis Object, during its construction.
        cout << "================ Ftiaxnw thread gia message analysis ========================" << endl;
        msg_analysis_threads.emplace_back(MessageAnalysis(app_ptr, s_received_msg));

//        sleep(1);

        if (terminate_server) {
            break;
        }

    }

    cout << "============================================-2";

    if (new_socket == 0) {
        // 0 means INVALID_SOCKET in WinSock
        printf("accept failed!");
    }



    sockClose(s);
    sockQuit();
}

void RemoteServer::run() {
    // listen_thread() will be executed as the main thread.
    listen_thread();

}

void RemoteServer::server_reply(nlohmann::json json_msg) {

    using namespace nlohmann;

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

    send(new_socket , outbound_msg, strlen(outbound_msg) , 0);

    cout << "\n\n";

//    cout << "Sending a message with size: " << strlen(outbound_msg) << endl;
    cout << "(((((((((((((((((((((((((( SERVER REPLIED!";
}

