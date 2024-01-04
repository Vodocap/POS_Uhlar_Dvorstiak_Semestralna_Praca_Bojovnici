//
// Created by dange on 2. 1. 2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H
#include <iostream>

class Statistiky {

public:
    double dajZivotyHodnota(int uroven, int hranica);
    double dajBrnenieHodnota(int uroven, int hranica);
    double dajPoskodenieHodnota(int uroven, int hranica);
    double dajUnikHodnota(int uroven, int hranica);
    double dajRychlostUtokuHodnota(int uroven, int hranica);
    int dajPocetBojovnikov(int uroven, int hranica);
    void vypisStatistiky(int statistika , int uroven);
    int getCenaUrovne(int uroven);


};

#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H
