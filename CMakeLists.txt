cmake_minimum_required(VERSION 3.10)
project(EzRemote_Project)

set(CMAKE_CXX_STANDARD 11)

link_libraries(ws2_32 wsock32)

add_executable(EzRemote_Project main.cpp)