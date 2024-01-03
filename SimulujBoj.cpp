//
// Created by matus on 2.1.2024.
//

#include "SimulujBoj.h"
#include "Team.h"

void SimulujBoj::simulujBoj(Team* team1, Team* team2) {

    if (team1->getVelkostTeamu() > 0 && team2->getVelkostTeamu() > 0) {

        Team* prvyTeam = team1;
        Team* druhyTeam = team2;
        if ((rand() % 2) == 1) {
            std::cout << "Zacina team hraca " << team2->getMeno();
            prvyTeam = team2;
            druhyTeam = team1;
        }

        while (prvyTeam->getVelkostTeamu() != 0 || druhyTeam->getVelkostTeamu() != 0) {
            prvyTeam->dajBojovnikaNaBoj()->zautoc(druhyTeam->dajBojovnikaNaBoj());
            druhyTeam->dajBojovnikaNaBoj()->zautoc(prvyTeam->dajBojovnikaNaBoj());
            prvyTeam->vymazMrtvychBojovnikov();
            druhyTeam->vymazMrtvychBojovnikov();
            std::cout << prvyTeam->getVelkostTeamu() << std::endl;
            std::cout << druhyTeam->getVelkostTeamu() << std::endl;

            if (prvyTeam->getVelkostTeamu() == 0 || druhyTeam->getVelkostTeamu() == 0) {
                break;
            }

        }

        this->vyhodnotVitaza(prvyTeam, druhyTeam);
        std::cout << "Tento zapas vyhral " << this->vitaz << std::endl;

    }

    return;

}

void SimulujBoj::vyhodnotVitaza(Team *team1, Team *team2) {
    if (team1->getVelkostTeamu() > team2->getVelkostTeamu()) {
        this->vitaz = team1->getMeno();
    } else {
        this->vitaz = team2->getMeno();
    }


}

const std::string &SimulujBoj::getVitaz() const {
    return vitaz;
}




//TODO prerobit na dve vlakna, kazde bude utocit kym tým nie je prázdny
