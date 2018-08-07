//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "App.h"
#include <iostream>
#include "nlohmann/json.hpp"

using namespace std;

App::App() {
    in_connection = false;
    server = new RemoteServer(this);
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