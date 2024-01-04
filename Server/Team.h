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
    Bojovnik* dajBojovnikaNaBoj();
    void vymazMrtvychBojovnikov();
    void vytvorBojovnikov(double paDolnaHranicaZivoty, double paDolnaHranicaPoskodenie, double paDolnaHranicaBrnenie, double paDolnaHranicaUnik,double paDolnaHranicaRychlostUtoku,
                          double paHornaHranicaZivoty, double paHornaHranicaPoskodenie, double paHornaHranicaBrnenie, double paHornaHranicaUnik,double paHornaHranicaRychlostUtoku);
    double dajNahodneCisloZIntervalu(double zaciatok, double koniec);
    void prirpavTeamNaDalsiBoj();
    const std::string &getMeno() const;



private:
    std::string meno;
    std::vector<Bojovnik*> teamBojovnikov;
    int pocet;
    double dolnaHranicaZivoty;
    double dolnaHranicaPoskodenie;
    double dolnaHranicaBrnenie;
    double dolnaHranicaUnik;
    double dolnaHranicaRychlostUtoku;
    double hornaHranicaZivoty;
    double hornaHranicaPoskodenie;
    double hornaHranicaBrnenie;
    double hornaHranicaUnik;
    double hornaHranicaRychlostUtoku;




};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_TEAM_H
