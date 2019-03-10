//
// Created by Sierra Kilo on 10-Mar-19.
//

#ifndef EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
#define EZREMOTE_PROJECT_HANDSHAKEHANDLER_H

class ConnectionHandler;

class RemoteServer;

class HandshakeHandler:ConnectionHandler {

private:
    RemoteServer* remoteServerPtr = nullptr;

    void handshakeListener();

    bool stopHandshakeListener;

public:
    HandshakeHandler(RemoteServer* remoteServerPtr);

    ~HandshakeHandler();
};


#endif //EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
