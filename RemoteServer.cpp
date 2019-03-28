//
// Created by Sierra Kilo on 09-Mar-19.
//

#include "RemoteServer.h"

//https://stackoverflow.com/questions/12927169/how-can-i-initialize-c-object-member-variables-in-the-constructor
RemoteServer::RemoteServer():handshakeHandler(this) {

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