//
// Created by Sierra Kilo on 22-Feb-19.
//

#ifndef EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H
#define EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

using namespace std;


class ShutdownCommand {

private:
    // flag used from the start_shutdown_timer function when running in its thread
    // to determine whether a cancel command was issued for the timer currently in use.
    bool terminate_timer_flag = false;
    std::mutex *mu_terminate_timer_flag;

    void shutdown_command();

public:
    ShutdownCommand();

    void start_shutdown_timer(TimeObject time_data);

    void cancel_shutdown_timer();

    bool get_terminate_timer_flag_value();

};

#endif //EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

