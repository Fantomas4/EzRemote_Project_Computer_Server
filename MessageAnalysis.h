
//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H


#include "JSON.h"
#include "CommandExec.h"

class RequestHandler;

class MessageAnalysis {

private:

    CommandExec commandExec;


public:

    MessageAnalysis();

    nlohmann::json processReceivedMessage(std::string received_msg);


};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H