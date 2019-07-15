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
#include "RemoteServer.h"

class RequestHandler:RemoteServer {

private:

    SOCKET clientSocket;

    MessageAnalysis messageAnalysis;

    std::atomic<bool> terminateRequestHandler;

    void requestListener();

    void sendMessage(const char *outbound_msg);

    void handleRequestAndReply(std::string receivedMsg);

public:

    RequestHandler(SOCKET clientSocket);

    void start();

    void stop();
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
