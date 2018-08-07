//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "TimeObject.h"

unsigned int TimeObject::get_msecs(){
    // returns the saved time data, after converting it to milliseconds

    return (hrs * 60 * 60 * 1000) + (mins * 60 * 1000) + (secs * 1000) + (msecs);
}

TimeObject::TimeObject(){
    this->hrs = 0;
    this->mins = 0;
    this->secs = 0;
    this->msecs = 0;
}

TimeObject::TimeObject(unsigned int hrs, unsigned int mins, unsigned int secs, unsigned int msecs){
    this->hrs = hrs;
    this->mins = mins;
    this->secs = secs;
    this->msecs = msecs;
}