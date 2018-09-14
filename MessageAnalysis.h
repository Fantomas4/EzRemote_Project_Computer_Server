//
// Created by Sierra Kilo on 07-Aug-18.
//

#ifndef EZREMOTE_PROJECT_MESSAGEANALYSIS_H
#define EZREMOTE_PROJECT_MESSAGEANALYSIS_H

#include "App.h"
#include "RemoteServer.h"
#include "CommandExec.h"
#include <thread>

// forward declaration
class App;
class RemoteServer;

class MessageAnalysis {

private:
    App *app_ptr;
    RemoteServer *server_ptr;
    CommandExec *command_exec_ptr;
    char *recv_msg;
    std::thread msg_analysis_thread;


    void process_received_message();

public:
    MessageAnalysis(App *app_ptr, RemoteServer *server_ptr, CommandExec *command_exec_ptr, char *recv_buf);

};


#endif //EZREMOTE_PROJECT_MESSAGEANALYSIS_H
