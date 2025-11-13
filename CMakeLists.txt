cmake_minimum_required(VERSION 4.0)
project(cpp_parental_controller)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_parental_controller main.cpp
        src/scripts/ShutdownScript.cpp
        src/timer/timer.cpp
        src/timer/timer.h)
