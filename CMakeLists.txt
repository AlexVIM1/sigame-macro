cmake_minimum_required(VERSION 3.17)
project(sigame_macro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_executable(sigame_macro main.cpp client/client.cpp client/client.h result/result.cpp result/result.h commandLine/commandLine.cpp commandLine/commandLine.h)
