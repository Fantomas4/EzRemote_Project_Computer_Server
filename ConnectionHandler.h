//
// Created by Sierra Kilo on 06-Aug-18.
//


#ifndef EZREMOTE_PROJECT_CONNECTIONHANDLER_H
#define EZREMOTE_PROJECT_CONNECTIONHANDLER_H



#ifdef _WIN32

#include <winsock2.h>

#else

/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include <thread>

typedef int SOCKET;

#endif

class ConnectionHandler {

protected:

    int recvMsg(SOCKET recvSocket, char *recv_buf);

    void sendMsg(SOCKET sendSocket, const char* outboundMsg);

    int sockInit();

    int sockClose(SOCKET sock);

    int serverQuit();

public:

    ConnectionHandler();

};


#endif //EZREMOTE_PROJECT_CONNECTIONHANDLER_H
