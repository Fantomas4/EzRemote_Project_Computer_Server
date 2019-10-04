//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H


#include <string>

#include "ConnectionHandler.h"
#include "MessageAnalysis.h"


class RequestHandler:ConnectionHandler {

private:

    SOCKET clientSocket;

    std::thread requestListenerThread;

    MessageAnalysis messageAnalysis;

    std::atomic<bool> terminateRequestHandler;

    void requestListener();

    void sendMessage(const char *outbound_msg);

    void handleRequestAndReply(std::string receivedMsg);

public:

    // delete default constructor
    RequestHandler() = delete;

    RequestHandler(SOCKET clientSocket);

    //Delete the copy constructor
    RequestHandler(const RequestHandler&) = delete;

    //Delete the Assignment operator
    RequestHandler& operator=(const RequestHandler&) = delete;

    // Move Constructor
    RequestHandler(RequestHandler&& obj);

    //Move Assignment Operator
    RequestHandler& operator=(RequestHandler&& obj);

    void stop();

    ~RequestHandler();
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
