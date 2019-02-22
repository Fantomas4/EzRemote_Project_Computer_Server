//
// Created by Sierra Kilo on 07-Aug-18.
//

#include "App.h"




#include <iostream>
#include "MessageAnalysis.h"

#include "nlohmann/json.hpp"

using namespace std;

// https://stackoverflow.com/questions/6077143/disable-copy-constructor?fbclid=IwAR22A0BtOyMnyDpXwWNi2HVt3rGfQ4MpmvZxe4BmOXjmcRPuVxUVrYaYW6g
// Deleted copy constructor as a preemptive measure.
//MessageAnalysis::MessageAnalysis(const MessageAnalysis&) = delete;

MessageAnalysis::MessageAnalysis(App *app_ptr, std::string received_msg) {
    this->app_ptr = app_ptr;
    this->received_msg = received_msg;

    cout << "received_msg inside constructor of MessageAnalysis is: " << this->received_msg << endl;

    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
    // To call a member function, the first argument to std::bind must be a pointer, reference, or
    // shared pointer to an object of the appropriate type
    this->run_thread();

}

void MessageAnalysis::run_thread() {
    this->msg_analysis_thread = thread(&MessageAnalysis::process_received_message, this);
}

void MessageAnalysis::process_received_message() {

    cout << "\n\ns_msg inside process_received_message() is : " << received_msg << endl;

    nlohmann::json json_msg = nlohmann::json::parse(received_msg);

    string request = json_msg["request"];

    if (request == "make_connection") {
        cout << "--------------VRIKA make_connection ---------" << endl;
        // check whether the application is already connected to a client
        if (!app_ptr->is_in_connection()) {
            // server accepts the connection
            app_ptr->set_in_connection_to_true();

            nlohmann::json msg_data = json_msg["data"];
            app_ptr->set_ip_bond_address(msg_data["ip"]);

            // prepare the response to the client
            map<string, string> data;

            nlohmann::json json_msg = app_ptr->generate_json_msg("success", data);

            cout << "Message Analysis is preparing to send reply to client..." << endl;
            // send the response to the client
            app_ptr->get_remoteserver_obj_ptr()->server_reply(json_msg);

        }

    } else if (request == "execute_shutdown_system_command") {
        // extract string data from the json message
        nlohmann::json msg_data = json_msg["data"];

        string s_hrs = msg_data["hours"];
        string s_mns = msg_data["mins"];
        string s_secs = msg_data["secs"];
        string s_msecs = msg_data["msecs"];

        // stoul converts the string from the temp variables above to the wanted unsigned integer type.
        unsigned int hours = std::stoul(s_hrs);
        unsigned int mins = std::stoul(s_mns);
        unsigned int secs = std::stoul(s_secs);
        unsigned int msecs = std::stoul(s_msecs);

        // prepare the response to the client
        map<string, string> data;

        nlohmann::json json_msg = app_ptr->generate_json_msg("success", data);

        // send the response to the client
        app_ptr->get_remoteserver_obj_ptr()->server_reply(json_msg);

        app_ptr->get_commandexec_obj_ptr()->get_shutdown_command_obj_ptr()->start_shutdown_timer(TimeObject(hours, mins, secs, msecs));

    } else if (request == "cancel_shutdown_system_command") {

        app_ptr->get_commandexec_obj_ptr()->get_shutdown_command_obj_ptr()->cancel_shutdown_timer();

        if (app_ptr->get_commandexec_obj_ptr()->get_shutdown_command_obj_ptr()->get_terminate_timer_flag_value()) {
            // prepare the response to the client
            map<string, string> data;

            nlohmann::json json_msg = app_ptr->generate_json_msg("success", data);

            // send the response to the client
            app_ptr->get_remoteserver_obj_ptr()->server_reply(json_msg);
        }
    }
}
