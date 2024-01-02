//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
#include "Team.h"

class SimulujBoj {

public:
    void simulujBoj(Team* team1, Team* team2);

private:
    void vyhodnotVitaza(Team* team1, Team* team2);
    std::string vitaz;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SIMULUJBOJ_H
