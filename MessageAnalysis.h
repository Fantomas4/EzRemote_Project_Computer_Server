//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H

#include <thread>
#include "RemoteServer.h"
#include "JSON.h"

class MessageAnalysis {

private:
    std::string process_received_message(std::string received_msg);


public:

//    MessageAnalysis(std::string received_msg);


    std::string analyze_message(std::string received_msg);
};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H
