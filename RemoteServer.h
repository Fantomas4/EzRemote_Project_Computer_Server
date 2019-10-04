//
// Created by Sierra Kilo on 06-Aug-18.
//


#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H


#include <thread>
#include "HandshakeHandler.h"


class RemoteServer {

private:

    HandshakeHandler handshakeHandler;


public:

    // delete the default constructor
    RemoteServer() = delete;

    RemoteServer(AppState* appState);


};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
