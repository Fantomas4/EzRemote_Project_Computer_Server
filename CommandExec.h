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
#include "ShutdownCommand.h"

using namespace std;


class CommandExec {

private:
    ShutdownCommand shutdown_command;


public:
    CommandExec();

    ShutdownCommand* getShutdownCommandObjPtr() ;

//    map<string, string> static get_identification_info();

};


#endif //EZREMOTE_PROJECT_COMMANDEXEC_H
