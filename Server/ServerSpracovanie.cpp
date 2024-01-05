//
// Created by matus on 5.1.2024.
//

#include "ServerSpracovanie.h"

void ServerSpracovanie::deserializuj(const std::string &vstup, std::string &meno, std::string &volby) {
    size_t poziciaDelimitera = vstup.find(';');

    if (poziciaDelimitera != std::string::npos) {
        meno = vstup.substr(0, poziciaDelimitera);
        volby = vstup.substr(poziciaDelimitera +1);

    }


}
