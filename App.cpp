//
// Created by Sierra Kilo on 06-Aug-18.
//

#include <iostream>
#include "App.h"

// initializer list
App::App(): appState(7890), handshakeHandler(&appState) {

}

App::~App() {
    std::cout << "==========> App DESTRUCTOR!" << std::endl;
};

