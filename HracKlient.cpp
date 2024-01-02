//
// Created by matus on 2.1.2024.
//

#include "HracKlient.h"

HracKlient::HracKlient(std::string paMeno, int peniaze) {
    this->meno = paMeno;
    this->peniaze = peniaze;
}

void HracKlient::vypisStav() {
    std::cout << "HracKlient " << this->meno << "ma tolkoto penazi: " <<std::endl;

}

int HracKlient::getPeniaze() const {
    return peniaze;
}

void HracKlient::setPeniaze(int peniaze) {
    HracKlient::peniaze = peniaze;
}

void HracKlient::vyziadajMeno() {
    std::string pytaneMeno;
    do {
        std::cout << "Napis svoje meno: " << std::endl;
        std::cin >> pytaneMeno;

    } while (!pytaneMeno.empty());
}

void HracKlient::vyziadajVolby() {
    //TODO vyziiadaj od hraca ciselka od 0 - 2 styri krat po sebe a uloz ich do atributov
    //    int volbaZivoty;
    //    int volbaPoskodenie;
    //    int volbaBrnenie;
    //    int volbaUnik;
}


