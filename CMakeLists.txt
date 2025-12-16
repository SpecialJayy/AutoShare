cmake_minimum_required(VERSION 4.0)
project(AutoShare)

set(CMAKE_CXX_STANDARD 20)

add_executable(AutoShare main.cpp sqlite3.c
        DBM.cpp
        DBM.h
        clientManager.cpp
        clientManager.h
)
