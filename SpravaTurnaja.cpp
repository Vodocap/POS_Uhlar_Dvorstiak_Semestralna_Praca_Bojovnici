//
// Created by matus on 2.1.2024.
//

#include "SpravaTurnaja.h"


void SpravaTurnaja::prevedBoje() {
    SimulujBoj boj;
    for (int i = 0; i < this->hraci.size(); ++i) {
        for (int j = 0; j < this->hraci.size() && i != j; ++j) {
            ThreadData threadData(this->hraci[i]->dajTeam(), this->hraci[j]->dajTeam());
            boj.simulujBoj(&threadData);

            if (boj.getVitaz() == this->hraci[i]->getMeno()){
                this->hraci[i]->setSkore(this->hraci[i]->getSkore()+1);
            } else{
                this->hraci[j]->setSkore(this->hraci[j]->getSkore()+1);
            }
            hraci[i]->dajTeam()->prirpavTeamNaDalsiBoj();
            hraci[j]->dajTeam()->prirpavTeamNaDalsiBoj();
        }

    }
}

void SpravaTurnaja::pridajHraca(HracServer* hracServer) {
    this->hraci.push_back(hracServer);
}

void SpravaTurnaja::vyhodnotTurnaj() {
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < this->hraci.size(); ++i) {
        if (this->hraci[i]->getSkore() > max) {
            max = this->hraci[i]->getSkore();
            maxIndex = i;
        }
    }

    std::cout<<"VITAZOM TURNAJA SA STAVA :  "<<hraci[maxIndex]->getMeno()<<std::endl;

}
