cmake_minimum_required(VERSION 3.26)
project(2nd)

set(CMAKE_CXX_STANDARD 17)

add_executable(2nd main.cpp
)

set(CMAKE_EXE_LINKER_FLAGS "-static")