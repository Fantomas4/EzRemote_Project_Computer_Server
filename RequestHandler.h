//
// Created by Sierra Kilo on 09-Mar-19.
//

#ifndef EZREMOTE_PROJECT_REQUESTHANDLER_H
#define EZREMOTE_PROJECT_REQUESTHANDLER_H


#include <winsock2.h>
#include <string>

class ConnectionHandler;

class RequestHandler:ConnectionHandler {

private:

    SOCKET clientSocket;

    void requestListener();

    int Recv(char* recv_buf, int recv_buf_size);

    void handleRequestAndReply(std::string receivedMsg);

public:

    RequestHandler(SOCKET clientSocket);
};


#endif //EZREMOTE_PROJECT_REQUESTHANDLER_H
