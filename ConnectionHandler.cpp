//
// Created by Sierra Kilo on 06-Aug-18.
//

#include <iostream>
#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler() {
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ DEFAULT CONSTRUCTOR *******************" << std::endl;
}


//ConnectionHandler::ConnectionHandler(App *app_obj) {
//
//    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ CUSTOM CONSTRUCTOR *******************" << std::endl;
//
//    this->app_ptr = app_obj;
//
//    this->final_message = "CUSTOM CONSTRUCTOR";
//
//}

//ConnectionHandler& ConnectionHandler::getInstance() {
//    static ConnectionHandler instance; // Guaranteed to be destroyed.
//                                  // Instantiated on first use.
//    return instance;
//}

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







