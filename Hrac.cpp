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

void Hrac::vyziadajMeno() {
    std::string pytaneMeno;
    do {
        std::cout << "Napis svoje meno: " << std::endl;
        std::cin >> pytaneMeno;

    } while (!pytaneMeno.empty());
}

void Hrac::vyziadajVolby() {
    //TODO vyziiadaj od hraca ciselka od 0 - 2 styri krat po sebe a uloz ich do atributov
    //    int volbaZivoty;
    //    int volbaPoskodenie;
    //    int volbaBrnenie;
    //    int volbaUnik;
}


