//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H

#ifdef _WIN32
#include <winsock2.h>
#endif

#include <string>
#include "MessageAnalysis.h"
#include "ConnectionHandler.h"

class RequestHandler:ConnectionHandler {

private:

    SOCKET clientSocket;

    MessageAnalysis messageAnalysis;

    // passed by reference to message analysis in order to facilitate the exit request
    // (terminate listener request) from the client.
    std::atomic<bool> terminateRequestListener;

    void requestListener();

    void handleRequestAndReply(std::string receivedMsg);

public:

    RequestHandler(SOCKET clientSocket);

    void start();

    void stop();
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
