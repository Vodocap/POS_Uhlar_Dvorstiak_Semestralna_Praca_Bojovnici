//
// Created by matus on 2.1.2024.
//

#include "HracServer.h"

HracServer::HracServer(std::string volby, std::string paMeno) {
    this->meno = paMeno;
    this->team = new Team(paMeno, team->dajNahodneCisloZIntervalu(this->statistiky.dajPocetBojovnikov(stoi(volby.substr(5,1)), 0), this->statistiky.dajPocetBojovnikov(stoi(volby.substr(5,1)), 1)));
    this->team->vytvorBojovnikov(this->statistiky.dajZivotyHodnota(stoi(volby.substr(0,1)), 0), this->statistiky.dajPoskodenieHodnota(stoi(volby.substr(1,1)), 0),
                                 this->statistiky.dajBrnenieHodnota(stoi(volby.substr(2,1)), 0), this->statistiky.dajUnikHodnota(stoi(volby.substr(3,1)), 0),
                                 this->statistiky.dajRychlostUtokuHodnota(stoi(volby.substr(4,1)), 0), this->statistiky.dajZivotyHodnota(stoi(volby.substr(0,1)), 1),
                                 this->statistiky.dajPoskodenieHodnota(stoi(volby.substr(1,1)), 1), this->statistiky.dajBrnenieHodnota(stoi(volby.substr(2,1)), 1),
                                 this->statistiky.dajUnikHodnota(stoi(volby.substr(3,1)), 1), this->statistiky.dajRychlostUtokuHodnota(stoi(volby.substr(4,1)), 1));

}

Team *HracServer::dajTeam() {
    return this->team;
}




