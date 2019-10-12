//
// Created by Sierra Kilo on 09-Mar-19.
//

#include "RequestHandler.h"
#include "TimeObject.h"

#include <mutex>
#include <iostream>


RequestHandler::RequestHandler(AppState* appState, SOCKET clientSocket) : commandExec() {
    this->appState = appState;
    this->clientSocket = clientSocket;
    this->terminateRequestHandler = false;

}

void RequestHandler::requestListener() {

    #define DEFAULT_BUFLEN 1000

    int recv_size;
    char recv_buf[DEFAULT_BUFLEN] = {0};   // Initialises all elements to null.
    int recv_buf_len = DEFAULT_BUFLEN;

    while (!terminateRequestHandler) {
        printf("****** Listen LOOP *********\n");

        // 0 means INVALID_SOCKET in WinSock
        recv_size = ConnectionHandler::recvMsg(this->clientSocket, recv_buf);
        if (recv_size == -1) {
            // -1 means SOCKET_ERROR in WinSock
            puts("Receive failed");

        #ifdef _WIN32

            // Uh oh!  Something bad happened.  Let's
            // get the error code...
            int errCode = WSAGetLastError();

            // ..and the human readable error string!!
            // Interesting:  Also retrievable by net helpmsg 10060
            LPSTR errString = NULL;  // will be allocated and filled by FormatMessage

            int size = static_cast<int>(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                                      FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
                                                      0,       // 0 since source is internal message table
                                                      static_cast<DWORD>(errCode), // this is the error code returned by WSAGetLastError()
                    // Could just as well have been an error code from generic
                    // Windows errors from GetLastError()
                                                      0,       // auto-determine language to use
                                                      (LPSTR) &errString, // this is WHERE we want FormatMessage
                    // to plunk the error string.  Note the
                    // peculiar pass format:  Even though
                    // errString is already a pointer, we
                    // pass &errString (which is really type LPSTR* now)
                    // and then CAST IT to (LPSTR).  This is a really weird
                    // trip up.. but its how they do it on msdn:
                    // http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
                                                      0,                 // min size for buffer
                                                      0));               // 0, since getting message from system tables
            printf("Error code %d:  %s\n\nMessage was %d bytes, in case you cared to know this.\n\n", errCode,
                   errString, size);

            LocalFree(errString); // if you don't do this, you will get an
            // ever so slight memory leak, since we asked
            // FormatMessage to FORMAT_MESSAGE_ALLOCATE_BUFFER,
            // and it does so using LocalAlloc
            // Gotcha!  I guess.

        #endif

        } else if (recv_size == 0) {
            // An empty message was received.
            // This (usually) means that the client has abruptly
            // dropped the connection

            // Terminate this Request Handler.
            terminateRequestHandler = true;

        } else {
            // receive was successful
            std::string s_received_msg = recv_buf;
            std::cout << "s_received_msg is: " << s_received_msg << std::endl;

            handleRequestAndReply(s_received_msg);
        }
    }

    ConnectionHandler::sockClose(this->clientSocket);
}

void RequestHandler::sendMessage(const char *outbound_msg) {
    std::cout << "server outbound_msg is: " << std::endl;

    for (int i = 0; i < strlen(outbound_msg); i++) {
        std::cout << outbound_msg[i];
    }

    // send the formatted message
    ConnectionHandler::sendMsg(this->clientSocket, outbound_msg);

    std::cout << "\n\n";

    // cout << "Sending a message with size: " << strlen(outbound_msg) << endl;
    std::cout << "(((((((((((((((((((((((((( SERVER REPLIED!";
}


void RequestHandler::handleRequestAndReply(std::string receivedMsg) {

    // converts the json data from outbound_json_buffer to a string,
    // then converts the string to const char* and assigns it to outbound_msg
    //
    // ATTENTION!
    // c_str() returns the contents of the string as a const char*
    // and the pointer it returns is valid as long as the given string object exists.

    std::string temp_s = JSON::convertJsonToString(processReceivedMessage(receivedMsg));
    const char *json_string = temp_s.c_str();

    sendMessage(json_string);

}

nlohmann::json RequestHandler::processReceivedMessage(std::string received_msg) {

    std::cout << "\n\ns_msg inside process_received_message() is : " << received_msg << std::endl;

    nlohmann::json jsonReplyMsg;

    nlohmann::json jsonReceivedMsg = nlohmann::json::parse(received_msg);

    std::string request = jsonReceivedMsg["request"];

    if (request == "EXECUTE_SHUTDOWN_COMMAND") {
        // extract string data from the json message
        nlohmann::json msgData = jsonReceivedMsg["data"];

        std::string s_hrs = msgData["hours"];
        std::string s_mns = msgData["mins"];
        std::string s_secs = msgData["secs"];
        std::string s_msecs = msgData["msecs"];

        // stoul converts the string from the temp variables above to the wanted unsigned integer type.
        unsigned int hours = std::stoul(s_hrs);
        unsigned int mins = std::stoul(s_mns);
        unsigned int secs = std::stoul(s_secs);
        unsigned int msecs = std::stoul(s_msecs);

        // prepare the response to the client
        std::map<std::string, std::string> data;

        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);

        commandExec.getShutdownCommandObjPtr()->startShutdownTimerThread(TimeObject(hours, mins, secs, msecs));

    } else if (request == "CANCEL_SHUTDOWN_COMMAND") {

        commandExec.getShutdownCommandObjPtr()->cancelShutdownTimer();

        if (commandExec.getShutdownCommandObjPtr()->getTerminateTimerFlagValue()) {
            // prepare the response to the client
            std::map<std::string, std::string> data;
            jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);
        }

    } else if (request == "TERMINATE_CONNECTION") {
        std::cout << "============> TERMINATE_CONNECTION request RECEIVED!" << std::endl;
        this->terminateRequestHandler = true;
        this->appState->setInConnectionValue(false);
        // prepare the response to the client
        std::map<std::string, std::string> data;
        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);


    } else if (request == "HEARTBEAT_CHECK") {
        // prepare the response to the client
        std::map<std::string, std::string> data;
        jsonReplyMsg = JSON::prepareJsonReply("SUCCESS", data);
    }

    return jsonReplyMsg;
}

RequestHandler::~RequestHandler() {
//    if (this->requestListenerThread.joinable()) {
//        this->requestListenerThread.join();
//    }

    std::cout << "==========> RequestHandler DESTRUCTOR!" << std::endl;

}

//RequestHandler::RequestHandler(RequestHandler &&obj) : requestListenerThread(std::move(obj.requestListenerThread)) {
//    std::cout << "Move Constructor is called" << std::endl;
//}
//
//RequestHandler &RequestHandler::operator=(RequestHandler &&obj) {
//    std::cout << "Move Assignment is called" << std::endl;
//    if (requestListenerThread.joinable()) {
//        requestListenerThread.join();
//    }
//    requestListenerThread = std::move(obj.requestListenerThread);
//
//
//    return *this;
//}

