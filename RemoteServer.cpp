//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "RemoteServer.h"
#include <thread>

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

        // Create a thread to process the received message and determine the client's given command
        // The thread is created by the MessageAnalysis Object, during its construction.
        msg_analysis_threads.emplace_back(MessageAnalysis(app_ptr, this, recv_buf));



        //Reply to the client
//                message = "Hello Client , I have received your connection. But I have to go now, bye\n";

//                json_message = generate_json_msg("response", "id_info", CommandExec().get_identification_info());
//                final_message = json_message.dump(4);
//
//                cout << json_message.dump(4) << "\n";

        //send(new_socket , (const char *)&message , sizeof(message) , 0);

//
//                // c_str() returns the contents of the string as a const char*
//                // and the pointer it returns is valid as long as the given string object exists.
//                send(new_socket , final_message.c_str(), final_message.size() , 0);
//                cout << "============================================-1";
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

void RemoteServer::server_reply() {

    using namespace nlohmann;

    // converts the json data from outbound_json_buffer to a string,
    // then converts the string to const char* and assigns it to outbound_msg
    //
    // ATTENTION!
    // c_str() returns the contents of the string as a const char*
    // and the pointer it returns is valid as long as the given string object exists.
    const char *outbound_msg = outbound_json_buffer.dump(4).c_str();

    send(new_socket , outbound_msg, sizeof(outbound_msg) , 0);
}

RemoteServer::RemoteServer(App *app_obj) {
    this->app_ptr = app_obj;
    run();
}