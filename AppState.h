//
// Created by Sierra Kilo on 31-Aug-19.
//

#ifndef EZREMOTE_PROJECT_APPSTATE_H
#define EZREMOTE_PROJECT_APPSTATE_H


#include <string>
#include <atomic>

class AppState {

private:
    // states the port used by the server
    int port;
    // states whether the server is currently connected to a client.
    std::atomic<bool> in_connection;
    // holds the ip of the client that the application is currently bonded to.
    std::string ip_bond;

public:

    AppState(int port);

    void setPort(int port);

    int getPort();

    void setInConnectionValue(bool value);

    bool isInConnection();

    void setIpBondAddress(std::string ip);

    std::string getIpBondAddress();

};


#endif //EZREMOTE_PROJECT_APPSTATE_H
