//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H

#include "nlohmann/json.hpp"
#include <iostream>

// forward declaration
class CommandExec;

#ifdef _WIN32

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#include <windows.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>

#else

/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include <thread>

typedef int SOCKET;

#endif

//#define DEFAULT_BUFLEN 512
#define DEFAULT_BUFLEN 1000

#include "MessageAnalysis.h"

// forward declaration
class App;


class RemoteServer {

private:
    // sets up a server used to listen for and accept commands from remote clients

    App *app_ptr;

    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    socklen_t c;
    std::string final_message = "DEFAULT";
    unsigned short PORT = 7890;
    int recv_size;
    char recv_buf[DEFAULT_BUFLEN] = {0};   // Initialises all elements to null.
    int recv_buf_len = DEFAULT_BUFLEN;
    std::vector<MessageAnalysis*> msg_analysis_threads;

    bool terminate_server = false;

    int sockInit();

    int sockClose(SOCKET sock);

    int sockQuit();

    int Recv(char* recv_buf, int recv_buf_size);

    void listen_thread();



public:
    explicit RemoteServer(App *app_obj);

    RemoteServer();

    void run();

    void server_reply(nlohmann::json json_msg);


};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
