cmake_minimum_required(VERSION 3.18)
project(Client)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Server
        Bojovnik.h
        Bojovnik.cpp
        HracServer.h
        HracServer.cpp
        mainServer.cpp
        Obchod.cpp
        Obchod.h
        SimulujBoj.cpp
        SimulujBoj.h
        SpravaTurnaja.cpp
        SpravaTurnaja.h
        Statistiky.cpp
        Statistiky.h
        Team.cpp
        Team.h
        ThreadData.cpp
        ThreadData.h
)

target_link_libraries(Server PRIVATE Threads::Threads)