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

CommandExec::CommandExec() {
    std::atomic_init(&terminate_timer, false);
//    terminate_timer = false;
}

map<string, string> CommandExec::get_identification_info() {
    string id;
    string ip;
    string status;
    map<string, string> info;

    //get computer name
    id = "test_computer_name";

    //get computer ip
    ip = "192.168.1.234";

    //get computer readiness status
    status = "Ready";

    info["id"] = id;
    info["ip"] = ip;
    info["status"] = status;

    return info;

}


void CommandExec::execute_shutdown_timer_thread(TimeObject time_data) {
    std::thread shutdown_command_thread = thread(&CommandExec::shutdown_timer, this, time_data);
    shutdown_command_thread.detach();
}

void CommandExec::terminate_shutdown_timer_thread() {
    this->terminate_timer = true;
}

void CommandExec::shutdown_timer(TimeObject time_data) {

    long long int t_target = time_data.get_msecs();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds delay(100);

    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto t_now = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - t_start);

        long long int elapsed_ms = elapsed.count();

        if (this->terminate_timer) {
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



void CommandExec::shutdown_command(){
#ifdef _WIN32


    // -s is used for shutdown, -f is used to force shutdown,
    // preventing the computer from getting stuck from background applications.
    //system("shutdown -s -f");
    cout << "\n\n---------------------Diag: Shutdown would be executed here!" << endl << endl;
#else
    // usleep takes sleep time in us (1 millionth of a second)
    usleep(time_data.get_msecs() * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif


}