//
// Created by Sierra Kilo on 10-Mar-19.
//

#include "HandshakeHandler.h"
#include "RequestHandler.h"

#ifdef _WIN32

#include <ws2tcpip.h>

#else

#endif

#include <cstdio>


HandshakeHandler::HandshakeHandler(RemoteServer* remoteServerPtr) {
    this->remoteServerPtr = remoteServerPtr;
    this->stopHandshakeListener = false;

}

HandshakeHandler::~HandshakeHandler() {
    delete this->requestHandler;
}


void HandshakeHandler::acceptNewConnection(SOCKET newSocket, nlohmann::json inMsgData) {
    printf("A new connection has been accepted!\n");

    // set the inConnection status and ip bond at the RemoteServer
    this->remoteServer.setInConnectionValue(true);
    this->remoteServer.setIpBondAddress(inMsgData["client_ip"]);

    // send a success response to the client to inform him that the
    // make_connection request has been accepted
    std::map<string, string> msgData;

    std::string temp_s = JSON::convertJsonToString(JSON::prepareJsonReply("SUCCESS", msgData));
    const char *outboundMsg = temp_s.c_str();

    ConnectionHandler::sendMsg(newSocket, outboundMsg);

    // start the request handler for the accepted client
    this->requestHandler = new RequestHandler(newSocket);
    this->requestHandler->start();
}

void HandshakeHandler::rejectNewConnection(SOCKET rejSocket) {

    // reply to the client by sending an error response with the appropriate message
    std::map<string, string> msgData;
    msgData["fail_message"] = "Connection Denied! Server is already in a connection with a client.";

    std::string temp_s = JSON::convertJsonToString(JSON::prepareJsonReply("FAIL", msgData));
    const char *outboundMsg = temp_s.c_str();

    ConnectionHandler::sendMsg(rejSocket, outboundMsg);
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


        // receive the first message the client sends after accept(),
        // which by protocol is the "make_connection" request
        #define DEFAULT_BUFLEN 1000

        int recv_size;
        char recv_buf[DEFAULT_BUFLEN] = {0};

        recv_size = ConnectionHandler::recvMsg(newSocket, recv_buf);

        if (recv_size == -1) {
            // -1 means SOCKET_ERROR in WinSock
            puts("Receive failed");
        } else {
            // receive was successful

            nlohmann::json jsonReceivedMsg = nlohmann::json::parse(recv_buf);

            string request = jsonReceivedMsg["request"];

            if (request == "INITIALIZE_NEW_CONNECTION") {

                // if the server is not already dedicated to a connection with a client
                if (!this->remoteServer.isInConnection()) {
                    std::thread acceptNewConnectionThread(&HandshakeHandler::acceptNewConnection, this, newSocket, jsonReceivedMsg["data"]);
                    acceptNewConnectionThread.detach();
                } else {
                    // if the server is already in a connection with a client,
                    // reject the connection request
                    std::thread rejectNewConnectionThread(&HandshakeHandler::rejectNewConnection, this, newSocket);
                    rejectNewConnectionThread.detach();
                }
            } else {
                cout << "*** ERROR: The client has broken the defined protocol! ***" << endl;
            }
        }
    }
}