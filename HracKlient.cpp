//
// Created by matus on 2.1.2024.
//

#include "HracKlient.h"
#include "Obchod.h"
#include "Statistiky.h"

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
    std::string hodnota;
    Obchod obchod;
    Statistiky statistiky;

    int i = 0;

    while (i < 6) {
        obchod.ukazObchod(i);
        do {
            std::cout << "Mas " <<peniaze <<" penazi" <<std::endl;
            std::cout << "Zadajte hodnotu (0-2): ";

            std::cin >> hodnota;


            if (hodnota == "0" || hodnota == "1" || hodnota == "2") {
                int cislo = std::stoi(hodnota);

                if(statistiky.getCenaUrovne(cislo) > getPeniaze()){
                    cislo = 0;
                    std::cout << "Nemate peniaze :( , dava sa defaultna hodnota "<< std::endl;
                }
                setPeniaze(peniaze - statistiky.getCenaUrovne(cislo));
                volby.push_back(cislo);
                i++;
                break;
            } else {
                std::cout << "Nesprávna hodnota. Zadajte prosím hodnotu od 0 do 2." << std::endl;
                obchod.ukazObchod(i);

            }
        } while (true);
    }
}



const std::string &HracKlient::getMeno() const {
    return meno;
}

std::string HracKlient::getVolba() {
    std::string volba;
    for (int i = 0; i < this->volby.size(); ++i) {
        volba += std::to_string(this->volby[i]);
    }
    return volba;
}