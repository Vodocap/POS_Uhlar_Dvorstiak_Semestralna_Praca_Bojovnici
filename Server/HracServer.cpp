//
// Created by matus on 2.1.2024.
//

#include "HracServer.h"

HracServer::HracServer(std::string pVolby, std::string paMeno) {
    this->meno = paMeno;
    this->volby = pVolby;
    this->team = new Team(paMeno, team->dajNahodneCisloZIntervalu(this->statistiky.dajPocetBojovnikov(stoi(volby.substr(5,1)), 0), this->statistiky.dajPocetBojovnikov(stoi(volby.substr(5,1)), 1)));
    this->vytvorPodlaVolieb();
}

Team *HracServer::dajTeam() {
    return this->team;
}

int HracServer::getSkore() const {
    return skore;
}

void HracServer::setSkore(int skore) {
    HracServer::skore = skore;
}

const std::string &HracServer::getMeno() const {
    return meno;
}

int HracServer::getCisloSocketu() const {
    return cisloSocketu;
}

void HracServer::setCisloSocketu(int cisloSocketu) {
    HracServer::cisloSocketu = cisloSocketu;
}

void HracServer::setVolby(std::string &volby) {
    HracServer::volby = volby;
    this->vytvorPodlaVolieb();
}

void HracServer::vytvorPodlaVolieb() {
    this->team->vytvorBojovnikov(this->statistiky.dajZivotyHodnota(stoi(volby.substr(0,1)), 0), this->statistiky.dajPoskodenieHodnota(stoi(volby.substr(1,1)), 0),
                                 this->statistiky.dajBrnenieHodnota(stoi(volby.substr(2,1)), 0), this->statistiky.dajUnikHodnota(stoi(volby.substr(3,1)), 0),
                                 this->statistiky.dajRychlostUtokuHodnota(stoi(volby.substr(4,1)), 0), this->statistiky.dajZivotyHodnota(stoi(volby.substr(0,1)), 1),
                                 this->statistiky.dajPoskodenieHodnota(stoi(volby.substr(1,1)), 1), this->statistiky.dajBrnenieHodnota(stoi(volby.substr(2,1)), 1),
                                 this->statistiky.dajUnikHodnota(stoi(volby.substr(3,1)), 1), this->statistiky.dajRychlostUtokuHodnota(stoi(volby.substr(4,1)), 1));
}




