//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H

//#include <thread>
//#include "ConnectionHandler.h"
//#include "JSON.h"
//#include "CommandExec.h"

//class ConnectionHandler;

class MessageAnalysis {

private:
    CommandExec commandExec;


public:
    MessageAnalysis();
//    void run_thread(std::string);

    nlohmann::json processReceivedMessage(std::string received_msg);


};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H
