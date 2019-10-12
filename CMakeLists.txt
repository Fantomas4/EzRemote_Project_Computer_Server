cmake_minimum_required(VERSION 3.10)
project(EzRemote_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(EzRemote_Project App.cpp App.h AppState.cpp AppState.h HandshakeHandler.cpp HandshakeHandler.h RequestHandler.cpp RequestHandler.h JSON.cpp JSON.h CommandExec.cpp CommandExec.h ShutdownCommand.cpp ShutdownCommand.h TimeObject.cpp TimeObject.h ConnectionHandler.cpp ConnectionHandler.h)

if(WIN32)
    target_link_libraries(EzRemote_Project wsock32 ws2_32)
else()
    target_link_libraries(EzRemote_Project pthread)
endif()