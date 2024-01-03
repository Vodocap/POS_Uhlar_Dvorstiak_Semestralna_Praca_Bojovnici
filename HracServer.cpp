//
// Created by matus on 2.1.2024.
//

#include "HracServer.h"

HracServer::HracServer(std::string volby) {


}

Team *HracServer::dajTeam() {
    return this->team;
}

std::vector<int> HracServer::spracujStringNaCisla(std::string pVolba) {
    std::vector<int> volby;
    for (int i = 0; i < pVolba.length(); ++i) {
        std::string vybrane = pVolba.substr(i,1);
        volby.push_back(std::stoi(vybrane));
    }
    return volby;

}

//TODO treba spravit aby sa robil tym,

