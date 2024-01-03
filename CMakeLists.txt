cmake_minimum_required(VERSION 3.18)
project(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici
        main.cpp
        Bojovnik.h
        Bojovnik.cpp
        Team.h
        Team.cpp
        HracKlient.h
        HracKlient.cpp
        SimulujBoj.h
        SimulujBoj.cpp
        HracServer.h
        SpravaTurnaja.h
        SpravaTurnaja.cpp
        HracServer.cpp
        Statistiky.cpp
        Statistiky.h
        Obchod.cpp
        Obchod.h
        ThreadData.h
        ThreadData.cpp

)

target_link_libraries(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici PRIVATE Threads::Threads)
