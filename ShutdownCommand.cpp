//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "CommandExec.h"
#include <iostream>

#ifdef __WIN32
#include <synchapi.h>
#else
#include <unistd.h>
#endif


using namespace std;

ShutdownCommand::ShutdownCommand() {
//    std::atomic_init(&terminate_timer, false);

    // use unique lock for the asynchronous operation of changing the
    // value for the terminate_timer_flag
    mu_terminate_timer_flag = new std::mutex();
    std::unique_lock<mutex> locker1(*mu_terminate_timer_flag);
    terminate_timer_flag = false;
    locker1.unlock();
}

void ShutdownCommand::startShutdownTimerThread(TimeObject time_data) {
    this->timerThread = std::thread(&ShutdownCommand::startShutdownTimer, this, time_data);
}

bool ShutdownCommand::getTerminateTimerFlagValue() {
    return terminate_timer_flag;
}

void ShutdownCommand::cancelShutdownTimer() {
    std::unique_lock<mutex> locker1(*mu_terminate_timer_flag);
    terminate_timer_flag = true;
    locker1.unlock();
}

void ShutdownCommand::startShutdownTimer(TimeObject time_data) {

    std::unique_lock<mutex> locker1(*mu_terminate_timer_flag);
    terminate_timer_flag = false;
    locker1.unlock();

    long long int t_target = time_data.get_msecs();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds delay(100);

    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto t_now = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - t_start);

        long long int elapsed_ms = elapsed.count();

        if (terminate_timer_flag) {
            cout << "\n\n" << "&&&&&&&&&&&&&&&&&&&&&& AKIROSI TIMER" << endl;
            break;
        } else if (elapsed_ms >= t_target) {
            cout << "\n\n" << "&&&&&&&&&&&&&&&&&&&&&& TELOS TIMER" << endl;
#ifdef _WIN32
            // -s is used for shutdown, -f is used to force shutdown,
            // preventing the computer from getting stuck from background applications.
            //system("shutdown -s -f");
            cout << "\n\n---------------------Diag: Shutdown would be executed here!" << endl << endl;
#else
            //                system("shutdown -P now");
                cout << "\n\n---------------------Diag: Shutdown would be executed here!" << endl << endl;
#endif
            break;
        }
    }

}



void ShutdownCommand::executeShutdown(){
#ifdef _WIN32


    // -s is used for shutdown, -f is used to force shutdown,
    // preventing the computer from getting stuck from background applications.
    //system("shutdown -s -f");
    cout << "\n\n---------------------Diag: Shutdown would be executed here!" << endl << endl;
#else
    // usleep takes sleep time in us (1 millionth of a second)
//    usleep(time_data.get_msecs() * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif


}

ShutdownCommand::~ShutdownCommand() {
    if (this->timerThread.joinable()) {
        this->timerThread.join();
    }
}

ShutdownCommand::ShutdownCommand(ShutdownCommand &&obj) : timerThread(std::move(obj.timerThread)){
    std::cout << "Move Constructor is called" << std::endl;

}

ShutdownCommand &ShutdownCommand::operator=(ShutdownCommand &&obj) {
    std::cout << "Move Assignment is called" << std::endl;
    if (timerThread.joinable()) {
        timerThread.join();
    }
    timerThread = std::move(obj.timerThread);

    return *this;
}
