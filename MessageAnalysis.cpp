//
// Created by Sierra Kilo on 07-Aug-18.
//

#include <iostream>

#include "MessageAnalysis.h"
#include "nlohmann/json.hpp"
#include "TimeObject.h"
#include "JSON.h"

using namespace std;

// https://stackoverflow.com/questions/6077143/disable-copy-constructor?fbclid=IwAR22A0BtOyMnyDpXwWNi2HVt3rGfQ4MpmvZxe4BmOXjmcRPuVxUVrYaYW6g
// Deleted copy constructor as a preemptive measure.
//MessageAnalysis::MessageAnalysis(const MessageAnalysis&) = delete;

MessageAnalysis::MessageAnalysis(bool* terminateRequestListener) {
    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
    // To call a member function, the first argument to std::bind must be a pointer, reference, or
    // shared pointer to an object of the appropriate type
    commandExec = CommandExec();
    this->terminateRequestListener = terminateRequestListener;

}

//void MessageAnalysis::run_thread(std::string received_msg) {
//    std::thread analysisThread = thread(&MessageAnalysis::process_received_message, received_msg);
//    analysisThread.detach();
//}



    if (request == "INITIALIZE_NEW_CONNECTION") {
        cout << "--------------VRIKA INITIALIZE_NEW_CONNECTION ---------" << endl;
        // check whether the application is already connected to a client
        if (!app_ptr->is_in_connection()) {
            // server accepts the connection
            app_ptr->set_in_connection_to_true();

            nlohmann::json msg_data = json_msg["data"];
            app_ptr->set_ip_bond_address(msg_data["client_ip"]);

    nlohmann::json jsonReplyMsg;

            nlohmann::json json_msg = app_ptr->generate_json_msg("SUCCESS", data);

    string request = jsonReceivedMsg["request"];


        }

    } else if (request == "EXECUTE_SHUTDOWN_COMMAND") {

        // extract string data from the json message
        nlohmann::json msgData = jsonReceivedMsg["data"];

        string s_hrs = msgData["hours"];
        string s_mns = msgData["mins"];
        string s_secs = msgData["secs"];
        string s_msecs = msgData["msecs"];

        // stoul converts the string from the temp variables above to the wanted unsigned integer type.
        unsigned int hours = std::stoul(s_hrs);
        unsigned int mins = std::stoul(s_mns);
        unsigned int secs = std::stoul(s_secs);
        unsigned int msecs = std::stoul(s_msecs);

        // prepare the response to the client
        map<string, string> data;

        jsonReplyMsg = JSON::prepareJsonReply("success", data);

        commandExec.getShutdownCommandObjPtr()->startShutdownTimerThread(TimeObject(hours, mins, secs, msecs));

    } else if (request == "CANCEL_SHUTDOWN_COMMAND") {

        commandExec.getShutdownCommandObjPtr()->cancelShutdownTimer();

        if (commandExec.getShutdownCommandObjPtr()->getTerminateTimerFlagValue()) {
            // prepare the response to the client
            map<string, string> data;


            nlohmann::json json_msg = app_ptr->generate_json_msg("SUCCESS", data);

            // send the response to the client
            app_ptr->get_remoteserver_obj_ptr()->server_reply(json_msg);
        }
    }

    return jsonReplyMsg;
}
