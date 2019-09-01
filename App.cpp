//
// Created by Sierra Kilo on 06-Aug-18.
//

#include "App.h"

App::App():remoteServer(7890, appState) {
    appState = AppState();
    remoteServer.start();
};

