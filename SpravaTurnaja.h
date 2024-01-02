//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H


#include <vector>
#include "HracServer.h"

class SpravaTurnaja {

public:
    void prevedBoje();
    void pridajHraca(HracServer* hracServer);

private:
    std::vector<HracServer*> hraci;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H
