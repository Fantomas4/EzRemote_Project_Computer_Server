//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include <iostream>
#include "nlohmann/json.hpp"


#include "RemoteServer.h"
#include "CommandExec.h"

class App {

private:
    RemoteServer remote_server;

public:
    App();



};


#endif //EZREMOTE_PROJECT_APP_H
