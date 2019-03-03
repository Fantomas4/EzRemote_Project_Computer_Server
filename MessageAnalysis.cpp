//
// Created by Sierra Kilo on 07-Aug-18.
//

#include <iostream>
#include <future>
#include "MessageAnalysis.h"

#include "nlohmann/json.hpp"

using namespace std;

// https://stackoverflow.com/questions/6077143/disable-copy-constructor?fbclid=IwAR22A0BtOyMnyDpXwWNi2HVt3rGfQ4MpmvZxe4BmOXjmcRPuVxUVrYaYW6g
// Deleted copy constructor as a preemptive measure.
//MessageAnalysis::MessageAnalysis(const MessageAnalysis&) = delete;

//MessageAnalysis::MessageAnalysis(std::string received_msg) {
//
//    cout << "received_msg inside constructor of MessageAnalysis is: " << received_msg << endl;
//
//    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
//    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
//    // To call a member function, the first argument to std::bind must be a pointer, reference, or
//    // shared pointer to an object of the appropriate type
//    this->run_thread(std);
//
//}

std::string MessageAnalysis::analyze_message(std::string received_msg) {
    // create a thread for process_received_message() and receive the string it returns using future , move and promise
    std::promise<std::string> p;
    auto future = p.get_future();
    std::thread msg_analysis_thread(&MessageAnalysis::process_received_message, std::move(p));
    msg_analysis_thread.join();
    std::string analysis_response = future.get();

    return analysis_response;
}

std::string MessageAnalysis::process_received_message(std::string received_msg) {

    cout << "\n\ns_msg inside process_received_message() is : " << received_msg << endl;

    nlohmann::json json_msg = nlohmann::json::parse(received_msg);

    string request = json_msg["request"];

    if (request == "make_connection") {
        cout << "--------------VRIKA make_connection ---------" << endl;
        // check whether the application is already connected to a client
        if (!RemoteServer::is_in_connection()) {
            // server accepts the connection
            RemoteServer::set_in_connection_value(true);
            nlohmann::json msg_data = json_msg["data"];
            RemoteServer::set_ip_bond_address(msg_data["ip"]);

            // prepare the json response
            map<string, string> data;

            nlohmann::json json_msg = JSON::prepare_json_reply("success", data);

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
