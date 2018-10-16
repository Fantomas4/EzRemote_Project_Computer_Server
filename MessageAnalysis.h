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
    App *app_ptr;
    std::string received_msg;
    std::thread msg_analysis_thread;


    void process_received_message();

    void run_thread();

public:

    MessageAnalysis();

    MessageAnalysis(App *app_ptr, std::string received_msg);

};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H
