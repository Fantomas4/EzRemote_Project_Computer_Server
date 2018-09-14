//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include <iostream>
#include "nlohmann/json.hpp"
#include "RemoteServer.h"
#include "CommandExec.h"

using namespace std;

// forward declaration
class RemoteServer;

class App {

private:
    RemoteServer *server;
    CommandExec command_exec;

public:
    // states whether the server is currently connected to a client.
    bool in_connection;
    // holds the ip of the client that the application is currently bonded to.
    string ip_bond;

    nlohmann::json generate_json_msg(string msg_type, string msg_content, map<string, string> data);

    App();

};


#endif //EZREMOTE_PROJECT_APP_H
