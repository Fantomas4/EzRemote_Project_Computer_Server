//
// Created by Sierra Kilo on 06-Aug-18.
//

#include <iostream>
#include <cstring>
#include <thread>
#include "RemoteServer.h"


//https://stackoverflow.com/questions/12927169/how-can-i-initialize-c-object-member-variables-in-the-constructor
RemoteServer::RemoteServer(int port):handshakeHandler(this) {
    this->port = port;
    this->in_connection = false;
    this->start();
}

void RemoteServer::start() {


    std::thread handshakeListenerThread = std::thread(&HandshakeHandler::handshakeListener, handshakeHandler);
    handshakeListenerThread.join();

}

void RemoteServer::stop() {

}

bool RemoteServer::isInConnection() {
    return in_connection;
}

std::string RemoteServer::getIpBondAddress() {
    return ip_bond;
}

void RemoteServer::setIpBondAddress(std::string ip) {
    ip_bond = ip;
}

void RemoteServer::setInConnectionValue(bool value) {
    in_connection = true;
}


