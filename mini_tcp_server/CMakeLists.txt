cmake_minimum_required(VERSION 2.8.12)
project(asio_minimum_tcp_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

include_directories(../thirdparty/asio)

add_executable(server mini_tcp_server.cpp)