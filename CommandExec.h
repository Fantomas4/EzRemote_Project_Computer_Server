//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_COMMANDEXEC_H
#define EZREMOTE_PROJECT_COMMANDEXEC_H

#include <map>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include "TimeObject.h"

using namespace std;


class CommandExec {

private:
        // flag used from the shutdown_timer function when running in its thread
        // to determine whether a cancel command was issued for the timer currently in use.
//        std::atomic_bool terminate_timer{false};
        bool terminate_timer_flag = false;
        std::mutex *mu_terminate_timer_flag;

//        std::atomic<bool> terminate_timer;


        void shutdown_timer(TimeObject time_data);
        void shutdown_command();

public:
    CommandExec();

    map<string, string> static get_identification_info();

    void execute_shutdown_timer_thread(TimeObject time_data);

    void terminate_shutdown_timer_thread();

    bool get_terminate_timer_flag_value();

    void reset_terminate_timer_flag();

};


#endif //EZREMOTE_PROJECT_COMMANDEXEC_H
