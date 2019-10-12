//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H


#include <string>
#include <thread>

#include "ConnectionHandler.h"
#include "CommandExec.h"
#include "JSON.h"
#include "AppState.h"


class RequestHandler:ConnectionHandler {

private:

    AppState* appState;

    SOCKET clientSocket;

    CommandExec commandExec;

    bool terminateRequestHandler;

    void sendMessage(const char *outbound_msg);

    void handleRequestAndReply(std::string receivedMsg);

    nlohmann::json processReceivedMessage(std::string received_msg);

public:

    // delete default constructor
    RequestHandler() = delete;

    RequestHandler(AppState* appState, SOCKET clientSocket);

//    //Delete the copy constructor
//    RequestHandler(const RequestHandler&) = delete;
//
//    //Delete the Assignment operator
//    RequestHandler& operator=(const RequestHandler&) = delete;
//
//    // Move Constructor
//    RequestHandler(RequestHandler&& obj);
//
//    //Move Assignment Operator
//    RequestHandler& operator=(RequestHandler&& obj);

    void requestListener();

    ~RequestHandler();
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
