//
// Created by Sierra Kilo on 06-Aug-18.
//


#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H


#include <thread>
#include "HandshakeHandler.h"


class RemoteServer {

private:

    int port;

    AppState appState;

    HandshakeHandler handshakeHandler;

    std::thread handshakeListenerThread;

public:

    explicit RemoteServer(int port, AppState& appState);

    virtual void start();

    virtual void stop();

};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
