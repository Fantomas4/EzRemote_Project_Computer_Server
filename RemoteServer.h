//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H

#include "App.h"
#include "MessageAnalysis.h"
#include "nlohmann/json.hpp"
#include <iostream>

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
#define DEFAULT_BUFLEN 10000

using namespace std;

// forward declaration
class App;
class MessageAnalysis;

class RemoteServer {

private:
    // sets up a server used to listen for and accept commands from remote clients

    App *app_ptr;

    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    socklen_t c;
    string final_message;
    nlohmann::json json_message;
    unsigned short PORT = 7789;
    int recv_size;
    char recv_buf[DEFAULT_BUFLEN];
    int recv_buf_len = DEFAULT_BUFLEN;
    vector<MessageAnalysis> msg_analysis_threads;

    int sockInit();

    int sockClose(SOCKET sock);

    int sockQuit();

    void listen_thread();

    void run();

public:
    RemoteServer(App *app_obj);

    void server_reply(nlohmann::json json_msg);


};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
