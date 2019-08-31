//
// Created by Sierra Kilo on 06-Aug-18.
//


#ifndef EZREMOTE_PROJECT_CONNECTIONHANDLER_H
#define EZREMOTE_PROJECT_CONNECTIONHANDLER_H


#include "HandshakeHandler.h"

class RemoteServer {

private:
    HandshakeHandler handshakeHandler;

protected:

    int port;

    // states whether the server is currently connected to a client.
    bool in_connection;
    // holds the ip of the client that the application is currently bonded to.
    std::string ip_bond;

public:

    explicit RemoteServer(int port);

    virtual void start();

    virtual void stop();

    void setInConnectionValue(bool value);

    bool isInConnection();

    void setIpBondAddress(std::string ip);

    std::string getIpBondAddress();

};


#endif //EZREMOTE_PROJECT_CONNECTIONHANDLER_H
