//
// Created by Sierra Kilo on 10-Mar-19.
//

#ifndef EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
#define EZREMOTE_PROJECT_HANDSHAKEHANDLER_H



#include "AppState.h"
#include "ConnectionHandler.h"
#include "JSON.h"



class RequestHandler;

class HandshakeHandler:ConnectionHandler {

private:
    AppState appState;

    RequestHandler* requestHandler;

    void acceptNewConnection(SOCKET newSocket, nlohmann::json inMsgData);

    void rejectNewConnection(SOCKET rejSocket);

    bool stopHandshakeListener;



public:
    HandshakeHandler(AppState& appState);

    ~HandshakeHandler();

    void handshakeListener();
};


#endif //EZREMOTE_PROJECT_HANDSHAKEHANDLER_H
