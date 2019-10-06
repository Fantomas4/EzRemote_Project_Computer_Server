//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include "AppState.h"
#include "HandshakeHandler.h"

class App {

private:

    AppState appState;

    HandshakeHandler handshakeHandler;

public:
    App();
    ~App();

};

int main() {
    App();
    return 0;
}


#endif //EZREMOTE_PROJECT_APP_H
