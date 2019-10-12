//
// Created by Sierra Kilo on 31-Aug-19.
//

#include "ConnectionHandler.h"

#include <string>
#include <iostream>
#include <cstring>

int ConnectionHandler::recvMsg(SOCKET recvSocket, char *recv_buf) {

    // empty the recv_buf buffer by filling it with 0 (null)
    *recv_buf = {0};

    // For the client - server communication, "\0" (null) is used as delimiter. Since strlen("\0") is 0,
    // the message part that contains the delimiter (last message part) will cause the recv() function to
    // return an integer representing the actual number of chars received (example: "ty\0" returns 4), while
    // strlen() that ignores the null character will return an amount smaller than the chars actually received (for our example,
    // it would return 2).

    // temp_buf temporarily holds the last string message the recv() function has received from the client
    int temp_buf_size = 1000;
    char temp_buf[temp_buf_size];
    std::string s_recv_buf;

    int n = 0, total_size = 0;

    do {

        n = recv(recvSocket, temp_buf, temp_buf_size, 0);
        total_size += n;

        // *** new addition
        if (n == 0) {
            break;
        }

        // create a temporary string to store the recv_buf char array as a string.
        s_recv_buf = recv_buf;
        // add the new message part received to the string of the whole message
        s_recv_buf += temp_buf;

        // convert string to char array and copy it to the original recv_buf
        strcpy(recv_buf, s_recv_buf.c_str());


    } while(strlen(temp_buf) == n);

    printf("------------------------------ I return from Recv... -----------------------------------------\n");

    return total_size;
}

void ConnectionHandler::sendMsg(SOCKET sendSocket, const char* outboundMsg) {

    std::cout << "ConnectionHandler outbound_msg is: " << std::endl;

    for (int i=0; i<strlen(outboundMsg); i++) {
        std::cout << outboundMsg[i];
    }
    send(sendSocket , outboundMsg, strlen(outboundMsg) , 0);
}

int ConnectionHandler::sockInit() {
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
#else
    return 0;
#endif
}

/* Note: For POSIX, typedef SOCKET as an int. */

int ConnectionHandler::sockClose(SOCKET sock) {

    int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) {
        status = closesocket(sock);
    }
#else
    status = shutdown(sock, SHUT_RDWR);
                if (status == 0) {
                    status = close(sock);
                }
#endif

    return status;

}

int ConnectionHandler::serverQuit() {
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}