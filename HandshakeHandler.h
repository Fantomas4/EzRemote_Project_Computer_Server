//
// Created by Sierra Kilo on 10-Mar-19.
//

#ifndef EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
#define EZREMOTE_PROJECT_HANDSHAKEHANDLER_H

#ifdef _WIN32

#include <winsock2.h>

#else

/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include <thread>

typedef int SOCKET;

#endif

#include "JSON.h"
#include "RemoteServer.h"


class RequestHandler;

class HandshakeHandler:RemoteServer {

private:
    RemoteServer* remoteServerPtr;

    void acceptNewConnection(SOCKET newSocket, nlohmann::json inMsgData);

    void rejectNewConnection(SOCKET rejSocket);

    bool stopHandshakeListener;

    RequestHandler* requestHandler;

public:
    HandshakeHandler(RemoteServer* remoteServerPtr);

    ~HandshakeHandler();

    void handshakeListener();
};


#endif //EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
