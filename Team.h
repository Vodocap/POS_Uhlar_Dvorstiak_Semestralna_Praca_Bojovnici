//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_TEAM_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_TEAM_H
#include "Bojovnik.h"
#include <vector>

class Team {

public:
    Team(std::string paMeno, int paPocet);
    bool pridajBojovnika(Bojovnik* bojovnik);
    void odoberBojovnikaNaIndexe(int index);
    int getVelkostTeamu();
    void vymazMrtvychBojovnikov();
    void vytvorBojovnikov(double dolnaHranicaZivoty, double dolnaHranicaPoskodenie, double dolnaHranicaBrnenie, double dolnaHranicaUnik,
                          double hornaHranicaZivoty, double hornaHranicaPoskodenie, double hornaHranicaBrnenie, double hornaHranicaUnik);
    double dajNahodneCisloZIntervalu(double zaciatok, double koniec);



private:
    std::string meno;
    std::vector<Bojovnik*> teamBojovnikov;
    int pocet;




};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_TEAM_H
