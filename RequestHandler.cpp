//
// Created by Sierra Kilo on 09-Mar-19.
//

#include "RequestHandler.h"
#include "JSON.h"

#include <cstdio>
#include <mutex>
#include <iostream>
#include <thread>

//#include "ConnectionHandler.h"

RequestHandler::RequestHandler(SOCKET clientSocket):messageAnalysis(&terminateRequestListener) {
    this->clientSocket = clientSocket;
    this->terminateRequestListener = false;
}

void RequestHandler::start() {
    std::thread requestListenerThread = std::thread(&RequestHandler::requestListener, this);
    requestListenerThread.detach();
}

void RequestHandler::requestListener() {

    #define DEFAULT_BUFLEN 1000

    int recv_size;
    char recv_buf[DEFAULT_BUFLEN] = {0};   // Initialises all elements to null.
    int recv_buf_len = DEFAULT_BUFLEN;

    bool terminate_server = false;

    while (true) {
        printf("****** Listen LOOP *********\n");

        // 0 means INVALID_SOCKET in WinSock

        if((recv_size = Recv(recv_buf, recv_buf_len)) == -1) {
            // -1 means SOCKET_ERROR in WinSock
            puts("Receive failed");

//            #ifdef _WIN32
//
//            // Uh oh!  Something bad happened.  Let's
//            // get the error code...
//            int errCode = WSAGetLastError();
//
//            // ..and the human readable error string!!
//            // Interesting:  Also retrievable by net helpmsg 10060
//            LPSTR errString = NULL;  // will be allocated and filled by FormatMessage
//
//            int size = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
//                                      FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
//                                      0,       // 0 since source is internal message table
//                                      errCode, // this is the error code returned by WSAGetLastError()
//                    // Could just as well have been an error code from generic
//                    // Windows errors from GetLastError()
//                                      0,       // auto-determine language to use
//                                      (LPSTR)&errString, // this is WHERE we want FormatMessage
//                    // to plunk the error string.  Note the
//                    // peculiar pass format:  Even though
//                    // errString is already a pointer, we
//                    // pass &errString (which is really type LPSTR* now)
//                    // and then CAST IT to (LPSTR).  This is a really weird
//                    // trip up.. but its how they do it on msdn:
//                    // http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
//                                      0,                 // min size for buffer
//                                      0 );               // 0, since getting message from system tables
//            printf( "Error code %d:  %s\n\nMessage was %d bytes, in case you cared to know this.\n\n", errCode, errString, size ) ;
//
//            LocalFree( errString ) ; // if you don't do this, you will get an
//            // ever so slight memory leak, since we asked
//            // FormatMessage to FORMAT_MESSAGE_ALLOCATE_BUFFER,
//            // and it does so using LocalAlloc
//            // Gotcha!  I guess.
//
//            #endif

        } else {
            // receive was successful
            std::string s_received_msg = recv_buf;



            // Create a thread to process the received message and determine the client's given command
            // The thread is created by the MessageAnalysis Object, during its construction.
            printf("================ Ftiaxnw thread gia message analysis ========================\n");

//            // https://en.cppreference.com/w/cpp/container/vector/emplace_back?fbclid=IwAR3ndX0Q_Ar04zBdiaXJizIvjO6drKG1nxJ1EnIgyC5P35HJl15BW5L424U
//            messageAnalysis.run_thread(s_received_msg);

//            std::thread requestHandler = std::thread(&ConnectionHandler::handleRequestAndReply, s_received_msg);
//            requestHandler.detach();

            handleRequestAndReply(s_received_msg);

            if (this->terminateRequestListener) {
                break;
            }
        }
    }

    ConnectionHandler::sockClose(this->clientSocket);
}



std::mutex recv_buffer_mutex;

int RequestHandler::Recv(char *recv_buf, int recv_buf_size) {

    // empty the recv_buf buffer by filling it with 0 (null)
    *recv_buf = {0};

    // For the client - server communication, "\0" (null) is used as delimiter. Since strlen("\0) is 0,
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

        n = recv(this->clientSocket, temp_buf, temp_buf_size, 0);
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
        recv_buffer_mutex.lock();
        strcpy(recv_buf, s_recv_buf.c_str());
        recv_buffer_mutex.unlock();

    } while(strlen(temp_buf) == n);

    printf("------------------------------ I return from Recv... -----------------------------------------\n");

    return total_size;
}


void RequestHandler::handleRequestAndReply(std::string receivedMsg) {

    // converts the json data from outbound_json_buffer to a string,
    // then converts the string to const char* and assigns it to outbound_msg
    //
    // ATTENTION!
    // c_str() returns the contents of the string as a const char*
    // and the pointer it returns is valid as long as the given string object exists.

    std::string temp_s = JSON::convertJsonToString(this->messageAnalysis.processReceivedMessage(receivedMsg));

    const char *outbound_msg = temp_s.c_str();

//    cout << "***********************strlen(outbound_msg): " << strlen(outbound_msg) << endl;
    std::cout << "server outbound_msg is: " << std::endl;

    for (int i=0; i<strlen(outbound_msg); i++) {
        std::cout << outbound_msg[i];
    }

    send(this->clientSocket , outbound_msg, strlen(outbound_msg) , 0);

    std::cout << "\n\n";

//    cout << "Sending a message with size: " << strlen(outbound_msg) << endl;
    std::cout << "(((((((((((((((((((((((((( SERVER REPLIED!";
}
