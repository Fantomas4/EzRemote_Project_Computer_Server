//
// Created by Sierra Kilo on 06-Aug-18.
//

#include <iostream>
#include "App.h"

// initializer list
App::App(): appState(7890), handshakeHandler(&appState) {
    handshakeListenerThread = std::thread(&HandshakeHandler::handshakeListener, &this->handshakeHandler);

}

App::~App() {
    if (this->handshakeListenerThread.joinable()) {
        this->handshakeListenerThread.join();
    }
    std::cout << "==========> App DESTRUCTOR!" << std::endl;
};

