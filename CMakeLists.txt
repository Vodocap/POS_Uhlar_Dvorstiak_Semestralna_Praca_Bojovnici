cmake_minimum_required(VERSION 3.18)
project(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici)

set(CMAKE_CXX_STANDARD 14)

add_executable(POS_Uhlar_Dvorstiak_Semestralna_Praca_Bojovnici
        main.cpp
        Bojovnik.h
        Bojovnik.cpp
        Team.h
        Team.cpp
        Hrac.h
        Hrac.cpp
        SimulujBoj.h
        SimulujBoj.cpp)
