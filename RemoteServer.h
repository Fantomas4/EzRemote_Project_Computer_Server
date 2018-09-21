//
// Created by Sierra Kilo on 06-Aug-18.
//

#ifndef EZREMOTE_PROJECT_REMOTESERVER_H
#define EZREMOTE_PROJECT_REMOTESERVER_H

//#include "App.h"
//#include "CommandExec.h"
//#include "MessageAnalysis.h"
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

using namespace std;

// forward declaration
class App;
class MessageAnalysis;

class RemoteServer {

private:
    // sets up a server used to listen for and accept commands from remote clients

    App *app_ptr;
    CommandExec *command_exec_ptr;

    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    socklen_t c;
    string final_message;
    nlohmann::json json_message;
    unsigned short PORT = 3456;
    int recv_size;
    char recv_buf[DEFAULT_BUFLEN] = {0};   // Initialises all elements to null.
    int recv_buf_len = DEFAULT_BUFLEN;
    vector<MessageAnalysis> msg_analysis_threads;

    int sockInit();

    int sockClose(SOCKET sock);

    int sockQuit();

    int Recv(char* recv_buf, int recv_buf_size);

    void listen_thread();

    void run();

public:
    RemoteServer(App *app_obj, CommandExec *command_exec_obj);

    void server_reply(nlohmann::json json_msg);


};


#endif //EZREMOTE_PROJECT_REMOTESERVER_H
