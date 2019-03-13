//
// Created by Sierra Kilo on 22-Feb-19.
//

#ifndef EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H
#define EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

using namespace std;


class ShutdownCommand {

private:
    // flag used from the startShutdownTimer function when running in its thread
    // to determine whether a cancel command was issued for the timer currently in use.
    bool terminate_timer_flag = false;
    std::mutex *mu_terminate_timer_flag;

    void startShutdownTimer(TimeObject time_data);

    void shutdownCommand();

public:
    ShutdownCommand();

    void startShutdownTimerThread(TimeObject time_data);

    void cancelShutdownTimer();

    bool getTerminateTimerFlagValue();

};

#endif //EZREMOTE_PROJECT_COMPUTER_SERVER_SHUTDOWNCOMMAND_H

