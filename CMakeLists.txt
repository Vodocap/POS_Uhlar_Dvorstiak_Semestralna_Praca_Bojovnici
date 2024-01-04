cmake_minimum_required(VERSION 3.18)
project(Client)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici_Server
        Server/Bojovnik.h
        Server/Bojovnik.cpp
        Server/HracServer.h
        Server/HracServer.cpp
        Server/mainServer.cpp
        Server/Obchod.cpp
        Server/Obchod.h
        Server/SimulujBoj.cpp
        Server/SimulujBoj.h
        Server/SpravaTurnaja.cpp
        Server/SpravaTurnaja.h
        Server/Statistiky.cpp
        Server/Statistiky.h
        Server/Team.cpp
        Server/Team.h
        Server/ThreadData.cpp
        Server/ThreadData.h
)
add_executable(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici_Client
        Client/HracKlient.cpp
        Client/HracKlient.h
        Client/mainClient.cpp
        Server/Obchod.h
        Server/Obchod.cpp
        Server/Statistiky.h
        Server/Statistiky.cpp
)

target_link_libraries(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici_Server PRIVATE Threads::Threads)