//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#include "Team.h"
#include "ThreadData.h"
#include <iostream>
#include <functional>

class SimulujBoj {

public:
    SimulujBoj(const std::function<void(const std::string&)>& spravyFunc);
    void simulujBoj(void* sharedData, std::string sprava);
    static void utocPrvy(SimulujBoj* simulujBoj, void* sharedData);
    static void utocDruhy(SimulujBoj* simulujBoj, void* sharedData);
    static void generujEfekty(void* sharedData);
    static void aplikujEfekty(void* sharedData);
    void dajStringUtoku(std::function<void(const std::string&)> posliSpravu, const std::string& sprava);



private:
    void vyhodnotVitaza(Team* team1, Team* team2);
    std::string vitaz;
    std::string sprava;
    std::function<void(const std::string&)> spravy;


public:
    const std::string &getVitaz() const;

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
