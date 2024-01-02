//
// Created by matus on 2.1.2024.
//

#include "HracKlient.h"
#include "Obchod.h"

HracKlient::HracKlient(int peniaze) {
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
    } while (pytaneMeno.empty());
    this->meno = pytaneMeno;
}

void HracKlient::vyziadajVolby() {
    int hodnota;
    Obchod obchod;
    int i = 0;

    while (i < 6) {
        obchod.ukazObchod(i);
        do {
            std::cout << "Zadajte hodnotu (0-2): ";
            std::cin >> hodnota;

            if (hodnota >= 0 && hodnota <= 2) {
                volby.push_back(hodnota);
                i++;
                break;  // Ukazuje, že správna hodnota bola zadaná, môžeme pokračovať v ďalšom cykle
            } else {
                std::cout << "Nesprávna hodnota. Zadajte prosím hodnotu od 0 do 2." << std::endl;
            }
        } while (true);
    }
}


    //TODO vyziiadaj od hraca ciselka od 0 - 2 styri krat po sebe a uloz ich do atributov
    //    volieb
    // cez volaky do while a cin


const std::string &HracKlient::getMeno() const {
    return meno;
}


