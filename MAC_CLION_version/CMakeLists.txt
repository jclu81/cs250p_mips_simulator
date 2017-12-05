cmake_minimum_required(VERSION 3.8)
project(pipelineSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        Solution.cpp
        Solution.h)
add_executable(pipelineSimulator ${SOURCE_FILES})