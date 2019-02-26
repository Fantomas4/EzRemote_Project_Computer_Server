//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H

#include <thread>


// forward declaration
class App;



class MessageAnalysis {

private:
    void process_received_message(std::string received_msg);


public:

//    MessageAnalysis(std::string received_msg);

    static void run_thread(std::string received_msg);
};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H
