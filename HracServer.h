//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H


#include <string>
#include "Team.h"
#include "Statistiky.h"

class HracServer {

public:
    HracServer(std::string volby, std::string paMeno);
    Team* dajTeam();


private:
    std::string meno;
    Team* team;
    Statistiky statistiky;

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H
