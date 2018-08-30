//
// Created by Sierra Kilo on 07-Aug-18.
//

#include "MessageAnalysis.h"
#include "CommandExec.h"

void MessageAnalysis::process_received_message(){

    using namespace nlohmann;

    // convert recv_msg to string
    string s_msg = recv_msg;

    json json_msg = json::parse(s_msg);

    string msg_type = json_msg["msg_type"];

    string msg_content = json_msg["msg_content"];

    json msg_data = json_msg["msg_data"];

    if (msg_type == "request"){

        cout << "\n\nVRIKA REQUEST ---------------------------------";

        if (msg_content == "make_connection") {
            cout << "VRIKA make_connection ---------------------------------";
            // check whether the application is already connected to a client
            if(!app_ptr->in_connection) {
                // server accepts the connection
                app_ptr->in_connection = true;
                cout<<"\nEFTASA 000" << endl;
                app_ptr->ip_bond = msg_data["ip"];

                cout<<"\nEFTASA 111" << endl;

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
            cout << "\n\nVRIKA execute_command ---------------------------------";
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

                // call of static method from class CommandExec.
                CommandExec::execute_shutdown_command(TimeObject(hours, mins, secs, msecs));


                // prepare the response to the client
                map<string, string> data;
                data["command_request_status"] = "accepted";

                nlohmann::json json_msg = app_ptr->generate_json_msg("response", "command_request_status", data);

                // send the response to the client
                server_ptr->server_reply(json_msg);
            }
        }

    } else if (msg_type == "response") {
        // Under Construction
    }




}

MessageAnalysis::MessageAnalysis(App *app_ptr, RemoteServer *server_ptr, char *recv_buf) {
    this->app_ptr = app_ptr;
    this->server_ptr = server_ptr;
    recv_msg = recv_buf;

    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
    // To call a member function, the first argument to std::bind must be a pointer, reference, or
    // shared pointer to an object of the appropriate type
    this->msg_analysis_thread = thread(&MessageAnalysis::process_received_message, this);


}