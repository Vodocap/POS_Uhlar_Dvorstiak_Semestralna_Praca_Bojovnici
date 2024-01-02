//
// Created by matus on 2.1.2024.
//

#include "Hrac.h"

Hrac::Hrac(std::string paMeno, int peniaze) {
    this->meno = paMeno;
    this->peniaze = peniaze;
}

void Hrac::vypisStav() {
    std::cout << "Hrac " << this->meno << "ma tolkoto penazi: " <<std::endl;

}

int Hrac::getPeniaze() const {
    return peniaze;
}

void Hrac::setPeniaze(int peniaze) {
    Hrac::peniaze = peniaze;
}


