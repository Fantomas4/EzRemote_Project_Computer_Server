//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H

#include <string>

#include "HandshakeHandler.h"

class RemoteServer {

private:
    // states whether the server is currently connected to a client.
    bool in_connection;
    // holds the ip of the client that the application is currently bonded to.
    std::string ip_bond;

    HandshakeHandler handshakeHandler;


public:
    RemoteServer();

    void setInConnectionValue(bool value);

    bool isInConnection();

    void setIpBondAddress(std::string ip);

    std::string getIpBondAddress();
};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
