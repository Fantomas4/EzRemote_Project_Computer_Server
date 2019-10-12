//
// Created by Sierra Kilo on 10-Mar-19.
//

#ifndef EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
#define EZREMOTE_PROJECT_HANDSHAKEHANDLER_H


#include <thread>
#include "AppState.h"
#include "ConnectionHandler.h"
#include "JSON.h"



class RequestHandler;

class HandshakeHandler:ConnectionHandler {

private:
    AppState* appState;

    RequestHandler* requestHandler;

    void acceptNewConnection(SOCKET newSocket, nlohmann::json inMsgData);

    void rejectNewConnection(SOCKET rejSocket);

    bool stopHandshakeListener;

    std::thread requestListenerThread;

public:

    // delete default constructor
    HandshakeHandler() = delete;

    HandshakeHandler(AppState* appState);

    void handshakeListener();

    ~HandshakeHandler();

};


#endif //EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
