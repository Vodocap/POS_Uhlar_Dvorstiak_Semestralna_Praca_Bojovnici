//
// Created by dange on 2. 1. 2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H


class Statistiky {

public:
    int dajZivotyHodnota(int uroven, int hranica);
    int dajBrnenieHodnota(int uroven, int hranica);
    int dajPoskodenieHodnota(int uroven, int hranica);
    int dajUnikHodnota(int uroven, int hranica);
    int dajRychlostUtokuHodnota(int uroven, int hranica);
    int dajPocetBojovnikov(int uroven, int hranica);
    void vypisStatistiky(int statistika , int uroven);

};

//TODO -5 pismen od hraca
#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_STATISTIKY_H
