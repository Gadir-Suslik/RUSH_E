cmake_minimum_required(VERSION 3.20)

project(RUSHE)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${RUSHE_SOURCE_DIR})

add_executable(rush src/rush.cpp)