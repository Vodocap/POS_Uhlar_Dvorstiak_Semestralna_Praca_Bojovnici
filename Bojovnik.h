//
// Created by matus on 2.1.2024.
//
#include <cstdlib>
#include <iostream>
#include <string>
#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_BOJOVNIK_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_BOJOVNIK_H


class Bojovnik {
public:
    Bojovnik(double pZivoty, double pPoskodenie, double pBrnenie, double pUnik);
    void vypisStav();
    bool zautoc(Bojovnik* bojovnik);
    void setZivoty(double hodnota);
    double getZivoty();
    void setPoskodenie(double hodnota);
    double getPoskodenie();
    void setBrnenie(double hodnota);
    double getBrnenie();
    void setUnik(double hodnota);
    double getUnik();
    bool getMrtvy();
    void setMrtvy(bool hodnota);

private:
    double zivoty;
    double poskodenie;
    double brnenie;
    double unik;
    bool mrtvy;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_BOJOVNIK_H
