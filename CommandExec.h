//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_COMMANDEXEC_H
#define EZREMOTE_PROJECT_COMMANDEXEC_H

#include <map>
#include "TimeObject.h"

using namespace std;


class CommandExec {

public:
    map<string, string> static get_identification_info();

    void static execute_shutdown_command(TimeObject time_data);

};


#endif //EZREMOTE_PROJECT_COMMANDEXEC_H
