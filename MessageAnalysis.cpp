//
// Created by Sierra Kilo on 07-Aug-18.
//

#include <iostream>

#include "MessageAnalysis.h"
#include "RequestHandler.h"
#include "nlohmann/json.hpp"
#include "TimeObject.h"
#include "JSON.h"

using namespace std;

// https://stackoverflow.com/questions/6077143/disable-copy-constructor?fbclid=IwAR22A0BtOyMnyDpXwWNi2HVt3rGfQ4MpmvZxe4BmOXjmcRPuVxUVrYaYW6g
// Deleted copy constructor as a preemptive measure.
//MessageAnalysis::MessageAnalysis(const MessageAnalysis&) = delete;

MessageAnalysis::MessageAnalysis(RequestHandler* requestHandler) {
    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    // The multi-argument version of the std::thread constructor works as if the arguments were passed to std::bind.
    // To call a member function, the first argument to std::bind must be a pointer, reference, or
    // shared pointer to an object of the appropriate type
    commandExec = CommandExec();
    this->requestHandler = requestHandler;

}

nlohmann::json MessageAnalysis::processReceivedMessage(std::string received_msg) {

    cout << "\n\ns_msg inside process_received_message() is : " << received_msg << endl;

    nlohmann::json jsonReplyMsg;

    nlohmann::json jsonReceivedMsg = nlohmann::json::parse(received_msg);

    string request = jsonReceivedMsg["request"];

    if (request == "EXECUTE_SHUTDOWN_COMMAND") {
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

        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);

        commandExec.getShutdownCommandObjPtr()->startShutdownTimerThread(TimeObject(hours, mins, secs, msecs));

    } else if (request == "CANCEL_SHUTDOWN_COMMAND") {

        commandExec.getShutdownCommandObjPtr()->cancelShutdownTimer();

        if (commandExec.getShutdownCommandObjPtr()->getTerminateTimerFlagValue()) {
            // prepare the response to the client
            map<string, string> data;
            jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);
        }

    } else if (request == "TERMINATE_CONNECTION") {
        requestHandler->stop();
        // prepare the response to the client
        map<string, string> data;
        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);

    } else if (request == "HEARTBEAT_CHECK") {
        // prepare the response to the client
        map<string, string> data;
        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);
    }

    return jsonReplyMsg;
}