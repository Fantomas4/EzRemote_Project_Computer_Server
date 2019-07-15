cmake_minimum_required(VERSION 3.10)
project(EzRemote_Project)

set(CMAKE_CXX_STANDARD 11)

option (USE_WINDOWS_LIB
            "Use the libraries needed by Windows" OΝ)

if (USE_WINDOWS_LIB)
    link_libraries(ws2_32 wsock32)
else(USE_WINDOWS_LIB)
    # use the libraries needed by Linux
    link_libraries(pthread)
endif(USE_WINDOWS_LIB)

add_executable(EzRemote_Project main.cpp App.cpp App.h RemoteServer.cpp RemoteServer.h HandshakeHandler.cpp HandshakeHandler.h RequestHandler.cpp RequestHandler.h JSON.cpp JSON.h CommandExec.cpp CommandExec.h ShutdownCommand.cpp ShutdownCommand.h TimeObject.cpp TimeObject.h MessageAnalysis.cpp MessageAnalysis.h)