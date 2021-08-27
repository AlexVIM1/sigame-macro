cmake_minimum_required(VERSION 3.17)
project(sigame_macro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl")

add_executable(sigame_macro main.cpp client/client.cpp client/client.h error/error.cpp error/error.h)
