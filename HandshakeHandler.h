//
// Created by Sierra Kilo on 10-Mar-19.
//

#ifndef EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
#define EZREMOTE_PROJECT_HANDSHAKEHANDLER_H


#include "ConnectionHandler.h"

class RemoteServer;

class RequestHandler;

class HandshakeHandler:ConnectionHandler {

private:
    RemoteServer* remoteServerPtr;

    void handshakeListener();

    void rejectNewConnection(SOCKET rejSocket);

    bool stopHandshakeListener;

    RequestHandler* requestHandler;

public:
    HandshakeHandler(RemoteServer* remoteServerPtr);

    ~HandshakeHandler();
};


#endif //EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
