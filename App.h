//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include "RemoteServer.h"

class App {

private:
    RemoteServer remoteServer;

public:
    App();

    void runRemoteServer();

};


#endif //EZREMOTE_PROJECT_APP_H
