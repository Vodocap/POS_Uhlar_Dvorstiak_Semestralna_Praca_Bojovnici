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
    std::string volby;
public:
    void setVolby(std::string &volby);

private:
    std::string meno;
    int cisloSocketu;
public:
    int getCisloSocketu() const;

    void setCisloSocketu(int cisloSocketu);

public:
    const std::string &getMeno() const;

private:
    Team* team;
    Statistiky statistiky;
    int skore;
public:
    int getSkore() const;

    void setSkore(int skore);

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACSERVER_H
