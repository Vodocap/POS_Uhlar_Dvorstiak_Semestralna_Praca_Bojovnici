//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H


#include <vector>
#include "HracServer.h"
#include "SimulujBoj.h"
#include <string>
class SpravaTurnaja {

public:
    void prevedBoje(std::function<void(const std::string&)> pFunkcia, std::string mess);
    void pridajHraca(HracServer* hracServer);
    HracServer* dajHracaNaIndexe (int index);
    std::string vyhodnotTurnaj();
private:
    bool ukonceny = false;
public:
    bool isUkonceny() const;

private:
    std::vector<HracServer*> hraci;
    static std::function<void(const std::string&)> funkcia;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_SPRAVATURNAJA_H
