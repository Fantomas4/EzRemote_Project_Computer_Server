//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H


#include <winsock2.h>
#include <string>
#include "MessageAnalysis.h"

class ConnectionHandler;

class RequestHandler:ConnectionHandler {

private:

    SOCKET clientSocket;

    MessageAnalysis messageAnalysis;

    // passed by reference to message analysis in order to facilitate the exit request
    // (terminate listener request) from the client.
    bool terminateRequestListener;

    void requestListener();

    int Recv(char* recv_buf, int recv_buf_size);

    void handleRequestAndReply(std::string receivedMsg);

public:

    RequestHandler(SOCKET clientSocket);

    void start();
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
