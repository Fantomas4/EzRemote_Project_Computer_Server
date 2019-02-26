//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "App.h"
#include <iostream>
#include "nlohmann/json.hpp"



App::App() {
    remote_server = RemoteServer(this);
    remote_server.run();
};

