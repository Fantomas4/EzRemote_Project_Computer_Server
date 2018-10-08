//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_APP_H
#define EZREMOTE_PROJECT_APP_H

#include <iostream>
#include "nlohmann/json.hpp"

using namespace std;

#include "RemoteServer.h"
#include "CommandExec.h"

class App {

private:

    RemoteServer remote_server;
    CommandExec command_exec;
    // states whether the server is currently connected to a client.
    bool in_connection;
    // holds the ip of the client that the application is currently bonded to.
    string ip_bond;

public:
    App();

    void initialize_server();

    RemoteServer* get_remoteserver_obj_ptr();

    CommandExec* get_commandexec_obj_ptr() ;

    bool is_in_connection();

    string get_ip_bond_address() ;

    void set_in_connection_to_true();

    nlohmann::json generate_json_msg(string msg_type, string msg_content, map<string, string> data);



};


#endif //EZREMOTE_PROJECT_APP_H
