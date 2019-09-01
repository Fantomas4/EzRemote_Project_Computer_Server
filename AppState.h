//
// Created by Sierra Kilo on 31-Aug-19.
//

#ifndef EZREMOTE_PROJECT_APPSTATE_H
#define EZREMOTE_PROJECT_APPSTATE_H


#include <string>

class AppState {

private:
    // states whether the server is currently connected to a client.
    bool in_connection;
    // holds the ip of the client that the application is currently bonded to.
    std::string ip_bond;

public:

    AppState();

    void setInConnectionValue(bool value);

    bool isInConnection();

    void setIpBondAddress(std::string ip);

    std::string getIpBondAddress();

};


#endif //EZREMOTE_PROJECT_APPSTATE_H
