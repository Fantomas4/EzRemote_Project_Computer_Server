//
// Created by Sierra Kilo on 22-Feb-19.
//

#ifndef EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H
#define EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

using namespace std;


class ShutdownCommand {

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
    ShutdownCommand();

    void execute_shutdown_timer_thread(TimeObject time_data);

    void terminate_shutdown_timer_thread();

    bool get_terminate_timer_flag_value();

};

#endif //EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

