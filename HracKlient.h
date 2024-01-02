//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
#include "Team.h"
#include <iostream>
class HracKlient {

public:
    HracKlient(int peniaze);
    void vypisStav();
    int getPeniaze() const;
    void setPeniaze(int peniaze);
    void vyziadajMeno();
    void vyziadajVolby();


private:
    int peniaze;
    std::vector<int> volby;
    std::string meno;
public:
    const std::string &getMeno() const;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
