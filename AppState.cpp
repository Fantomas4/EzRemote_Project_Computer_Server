//
// Created by Sierra Kilo on 31-Aug-19.
//

#include <iostream>
#include "AppState.h"

AppState::AppState(int port) {
    this->port = port;
    this->in_connection = false;
    this->ip_bond = "";
}

bool AppState::isInConnection() {
    return in_connection;
}

std::string AppState::getIpBondAddress() {
    return ip_bond;
}

void AppState::setIpBondAddress(std::string ip) {
    ip_bond = ip;
}

void AppState::setInConnectionValue(bool value) {
    in_connection = true;
}

void AppState::setPort(int port) {
    this->port = port;
}

int AppState::getPort() {
    return port;
}

