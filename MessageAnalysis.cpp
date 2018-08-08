//
// Created by Sierra Kilo on 07-Aug-18.
//

#include "MessageAnalysis.h"

void MessageAnalysis::process_received_message(){

    using namespace nlohmann;

    // convert recv_msg to string
    string s_msg = recv_msg;

    json json_msg = json::parse(s_msg);

    string msg_type = json_msg["msg_type"];

    string msg_content = json_msg["msg_content"];

    json msg_data = json_msg["msg_data"];

    if (msg_type == "request"){

        cout << "VRIKA REQUEST ---------------------------------";

        if (msg_content == "make_connection") {
            cout << "VRIKA make_connection ---------------------------------";
            // check whether the application is already connected to a client
            if(!app_ptr->in_connection) {
                // server accepts the connection
                app_ptr->in_connection = true;
                app_ptr->ip_bond = msg_data["ip"];

                // prepare the response to the client
                map<string, string> data;
                data["connection_request_status"] = "accepted";

                nlohmann::json json_msg = app_ptr->generate_json_msg("response", "connection_request_status", data);

                // send the response to the client
                server_ptr->server_reply(json_msg);

            } else {
                // server declines the connection because it is already bonded to a client

                // prepare the response to the client
                map<string, string> data;
                data["connection_request_status"] = "accepted";

                nlohmann::json json_msg = app_ptr->generate_json_msg("response", "connection_request_status", data);

                // send the response to the client
                server_ptr->server_reply(json_msg);

            }

        } else if (msg_content == "identify") {

        }

    } else if (msg_type == "response") {
        // Under Construction
    }




}

MessageAnalysis::MessageAnalysis(App *app_ptr, RemoteServer *server_ptr, char *recv_buf) {
    this->app_ptr = app_ptr;
    this->server_ptr = server_ptr;
    recv_msg = recv_buf;

    this->msg_analysis_thread = thread(process_received_message, this);


}