//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRAC_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRAC_H
#include "Team.h"
class Hrac {

public:
    Hrac(std::string paMeno, int peniaze);
    void vypisStav();
    int getPeniaze() const;
    void setPeniaze(int peniaze);
    void vyziadajMeno();
    void vyziadajVolby();

private:
    int peniaze;
    int volbaZivoty;
    int volbaPoskodenie;
    int volbaBrnenie;
    int volbaUnik;
    std::string meno;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRAC_H
