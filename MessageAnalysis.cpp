//
// Created by Sierra Kilo on 07-Aug-18.
//

#include "App.h"
#include "MessageAnalysis.h"
#include "RemoteServer.h"
#include "CommandExec.h"

#include "nlohmann/json.hpp"

MessageAnalysis::MessageAnalysis(App *app_ptr, RemoteServer *server_ptr, CommandExec *command_exec_ptr, string received_msg) {
    this->app_ptr = app_ptr;
    this->server_ptr = server_ptr;
    this->command_exec_ptr = command_exec_ptr;
    this->received_msg = received_msg;

    cout << "received_msg inside constructor of MessageAnalysis is: " << this->received_msg << endl;

    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
    // To call a member function, the first argument to std::bind must be a pointer, reference, or
    // shared pointer to an object of the appropriate type
    this->msg_analysis_thread = thread(&MessageAnalysis::process_received_message, this);


}

void MessageAnalysis::process_received_message(){

    using namespace nlohmann;

    cout << "\n\ns_msg inside process_received_message() is : " << received_msg << endl;

    json json_msg = json::parse(received_msg);

    string msg_type = json_msg["msg_type"];

    string msg_content = json_msg["msg_content"];

    json msg_data = json_msg["msg_data"];

    if (msg_type == "request"){

        cout << "\n\n-----------VRIKA REQUEST ------------" << endl;

        if (msg_content == "make_connection") {
            cout << "--------------VRIKA make_connection ---------" << endl;
            // check whether the application is already connected to a client
            if(!app_ptr->in_connection) {
                // server accepts the connection
                app_ptr->in_connection = true;

                app_ptr->ip_bond = msg_data["ip"];

                // prepare the response to the client
                map<string, string> data;
                data["connection_request_status"] = "accepted";

                nlohmann::json json_msg = app_ptr->generate_json_msg("response", "connection_request_status", data);

                cout << "Message Analysis is preparing to send reply to client..." <<endl;
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

        } else if (msg_content == "execute_command") {
            cout << "-------- VRIKA execute_command ---------------------------" << endl;
            string command_type = msg_data["type"];

            if (command_type == "shutdown_system") {

                // extract string data from the json message
                string s_hrs = msg_data["hours"];
                string s_mns = msg_data["mins"];
                string s_secs = msg_data["secs"];
                string s_msecs = msg_data["msecs"];

                // stoul converts the string from the temp variables above to the wanted unsigned integer type.
                unsigned int hours = std::stoul(s_hrs);
                unsigned int mins = std::stoul(s_mns);
                unsigned int secs = std::stoul(s_secs);
                unsigned int msecs = std::stoul(s_msecs);

//                // call static method from class CommandExec
//                // and execute it in a new, detached thread
//                std::thread shutdown_command_thread = thread(&CommandExec::execute_shutdown_command, TimeObject(hours, mins, secs, msecs));
//                shutdown_command_thread.detach();


                command_exec_ptr->execute_shutdown_timer_thread(TimeObject(hours, mins, secs, msecs));

                // prepare the response to the client
                map<string, string> data;
                data["command_request_status"] = "accepted";

                nlohmann::json json_msg = app_ptr->generate_json_msg("response", "command_request_status", data);

                // send the response to the client
                server_ptr->server_reply(json_msg);

            } else if (command_type == "cancel_system_shutdown") {

            }
        }

    } else if (msg_type == "response") {
        // Under Construction
    }




}

