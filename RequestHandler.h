//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H

#include <string>
#include "MessageAnalysis.h"
#include "ConnectionHandler.h"

class RequestHandler:ConnectionHandler {

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
