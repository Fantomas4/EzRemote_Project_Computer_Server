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
    return this->in_connection;
}

std::string AppState::getIpBondAddress() {
    return this->ip_bond;
}

void AppState::setIpBondAddress(std::string ip) {
    this->ip_bond = ip;
}

void AppState::setInConnectionValue(bool value) {
    this->in_connection = value;
}

void AppState::setPort(int port) {
    this->port = port;
}

int AppState::getPort() {
    return this->port;
}




