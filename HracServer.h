//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H


#include <string>
#include "Team.h"

class HracServer {

public:
    HracServer(int paVolbaZivoty, int paVolbaPoskodenie, int paVolbaBrnenie, int paVolbaUnik);
    Team* dajTeam();

private:
    std::vector<int> volby;
    std::string meno;
    Team* team;

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H
