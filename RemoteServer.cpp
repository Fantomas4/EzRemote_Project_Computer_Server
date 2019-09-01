//
// Created by Sierra Kilo on 06-Aug-18.
//

#include <thread>
#include "RemoteServer.h"


//https://stackoverflow.com/questions/12927169/how-can-i-initialize-c-object-member-variables-in-the-constructor
RemoteServer::RemoteServer(int port, AppState& appState):handshakeHandler(appState) {
    this->port = port;
    this->appState = appState;
    this->start();
}

void RemoteServer::start() {


    std::thread handshakeListenerThread = std::thread(&HandshakeHandler::handshakeListener, handshakeHandler);
    handshakeListenerThread.join();

}

void RemoteServer::stop() {

}




