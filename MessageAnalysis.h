
//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H


#include "nlohmann/json.hpp"
#include "CommandExec.h"

class MessageAnalysis {

private:
    bool* terminateRequestListener;
    CommandExec commandExec;


public:
    MessageAnalysis(bool* terminateRequestListener);

    nlohmann::json processReceivedMessage(std::string received_msg);


};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H