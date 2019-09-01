//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include "RemoteServer.h"


class App {

private:

    AppState appState;

    RemoteServer remoteServer;

public:
    App();

};

int main() {
    App app = App();
    return 0;
}


#endif //EZREMOTE_PROJECT_APP_H
