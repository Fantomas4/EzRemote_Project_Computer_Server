//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "App.h"
#include <iostream>
#include "nlohmann/json.hpp"



App::App() {
//    remote_server = ConnectionHandler(this);
//    remote_server.run();
    ConnectionHandler::getInstance().run();
};

