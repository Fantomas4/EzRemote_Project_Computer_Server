//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "App.h"
#include <iostream>
#include "nlohmann/json.hpp"


using namespace std;

App::App() {

    command_exec = CommandExec();
    in_connection = false;
};

void App:initialize_server() {
    remote_server = RemoteServer(this);
};

RemoteServer* App::get_remoteserver_obj_ptr() {
    return &remote_server;
}

CommandExec* App::get_commandexec_obj_ptr() {
    return &command_exec;
}

bool App::is_in_connection() {
    return in_connection;
}

string App::get_ip_bond_address() {
    return ip_bond;
}

void App::set_in_connection_to_true() {
    in_connection = true;
}

nlohmann::json App::generate_json_msg(string msg_type, string msg_content, map<string, string> data) {
    // msg_type is "request" or "response
    // msg_content describes the data content of the message
    // for example, identification_info

    nlohmann::json json_msg;

    json_msg = {
            {"msg_type", msg_type},
            {"msg_content", msg_content},
            {"msg_data", data}
    };



    return json_msg;
}