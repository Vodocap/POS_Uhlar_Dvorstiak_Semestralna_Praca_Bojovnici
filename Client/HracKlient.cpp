//
// Created by matus on 2.1.2024.
//

#include <csignal>
#include <cstring>
#include "HracKlient.h"
#include "../Server/Obchod.h"
#include "../Server/Statistiky.h"

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

void HracKlient::pripojSaNaServer(std::string adresa, short port) {
    SocketClient* tempSocket = SocketClient::createConnection(adresa, port);
    this->socketClient = tempSocket;
}

void HracKlient::posliUdaje() {
    std::string output;
    this->socketClient->serializuj(output, this->getMeno(), this->getVolba());
    this->socketClient->posliData(output);
}

void HracKlient::citajSpravy() {

    while (true) {
        char buffer[1025];
        int valread = read(socketClient->getNapojSocket(), buffer, 1024);

        if (valread > 0) {
            buffer[valread] = '\0';
            std::cout << "Sprava od servera: " << buffer << std::endl;
            if (strcmp(buffer, ":end") == 0) {
                std::cout << "Prijata sprava ':end'. Ukoncovani cyklu." << std::endl;
                break;
            }
        }
    }

}
