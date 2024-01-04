cmake_minimum_required(VERSION 3.18)
project(Client)
set(CMAKE_CXX_STANDARD 14)


add_executable(Client
        HracKlient.cpp
        HracKlient.h
        mainClient.cpp
        Obchod.h
        Obchod.cpp
        Statistiky.h
        Statistiky.cpp
        )
