//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "CommandExec.h"
#include <iostream>
#include <synchapi.h>

using namespace std;

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

void CommandExec::execute_shutdown_command(TimeObject time_data){
    // executes the sleep timer that puts the application in a hold
    // for a requested amount of time.

#ifdef _WIN32
    cout << "get_msecs: " << time_data.get_msecs() << "\n";
    Sleep(time_data.get_msecs());

    // -s is used for shutdown, -f is used to force shutdown,
    // preventing the computer from getting stuck from background applications.
    //system("shutdown -s -f");
    cout << "Diag: Shutdown would be executed here!";
#else
    // usleep takes sleep time in us (1 millionth of a second)
    usleep(time_data.get_msecs() * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif


}