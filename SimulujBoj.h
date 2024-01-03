//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#include "Team.h"
#include "ThreadData.h"
#include <iostream>

class SimulujBoj {

public:
    void simulujBoj(void* sharedData);
    static void utocPrvy(void* sharedData);
    static void utocDruhy(void* sharedData);


private:
    void vyhodnotVitaza(Team* team1, Team* team2);
    std::string vitaz;
public:
    const std::string &getVitaz() const;

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
