//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_TIMEOBJECT_H
#define EZREMOTE_PROJECT_TIMEOBJECT_H


class TimeObject {
    // class used to save time data, such as hours, minutes, seconds, milliseconds

private:

    unsigned int hrs;
    unsigned int mins;
    unsigned int secs;
    unsigned int msecs;

public:

    unsigned int get_msecs();

    TimeObject();

    TimeObject(unsigned int hrs, unsigned int mins, unsigned int secs, unsigned int msecs);
};


#endif //EZREMOTE_PROJECT_TIMEOBJECT_H
