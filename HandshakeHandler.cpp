//
// Created by Sierra Kilo on 10-Mar-19.
//

#include "HandshakeHandler.h"
#include "ConnectionHandler.h"
#include "RemoteServer.h"

#ifdef _WIN32

#include <ws2tcpip.h>

#else

#endif

#include <cstdio>

HandshakeHandler::HandshakeHandler(RemoteServer* remoteServerPtr) {
    this->remoteServerPtr = remoteServerPtr;
    this->stopHandshakeListener = false;

    this->handshakeListener();
}

void HandshakeHandler::handshakeListener() {

    SOCKET s;
    struct sockaddr_in server , client;
    socklen_t c;
    unsigned short PORT = 7890;

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

    c = sizeof(struct sockaddr_in);

    while (!this->stopHandshakeListener) {
        SOCKET newSocket = accept(s , (struct sockaddr *)&client, &c);

        printf("A new connection has been accepted!\n");

        // set the inConnection status and ip bond at the RemoteServer
        this->remoteServerPtr->setInConnectionValue(true);

        if (newSocket == 0) {
            // 0 means INVALID_SOCKET in WinSock
            printf("accept failed!");
        }

//        std::thread requestListenerThread = std::thread(RequestHandler(), new_socket);
//        requestListenerThread.detach();

    }
}