//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "CommandExec.h"
#include "ShutdownCommand.h"
#include <iostream>

#ifdef __WIN32
    #include <synchapi.h>
#else
    #include <unistd.h>
#endif


using namespace std;

CommandExec::CommandExec() {

    shutdown_command = ShutdownCommand();

}

ShutdownCommand* CommandExec::get_shutdown_command_obj_ptr() {
    return &shutdown_command;
}

//map<string, string> CommandExec::get_identification_info() {
//    string id;
//    string ip;
//    string status;
//    map<string, string> info;
//
//    //get computer name
//    id = "test_computer_name";
//
//    //get computer ip
//    ip = "192.168.1.234";
//
//    //get computer readiness status
//    status = "Ready";
//
//    info["id"] = id;
//    info["ip"] = ip;
//    info["status"] = status;
//
//    return info;
//
//}

