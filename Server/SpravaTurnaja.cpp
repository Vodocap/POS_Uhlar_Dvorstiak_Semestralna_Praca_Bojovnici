//
// Created by matus on 2.1.2024.
//

#include "SpravaTurnaja.h"


SpravaTurnaja::~SpravaTurnaja() {

    for (auto hrac : hraci) {
        delete hrac;
    }

    hraci.clear();
}

void SpravaTurnaja::prevedBoje(std::function<void(const std::string&)> pFunkcia, std::string mess) {
    SimulujBoj boj(pFunkcia);
    for (int i = 0; i < this->hraci.size(); ++i) {
        for (int j = i + 1; j < this->hraci.size(); ++j) {

                auto data = new ThreadData(this->hraci[i]->dajTeam(), this->hraci[j]->dajTeam(), new Efekty(2));

                boj.simulujBoj(data, mess);
                this->hraci[i]->dajTeam()->prirpavTeamNaDalsiBoj();
                this->hraci[j]->dajTeam()->prirpavTeamNaDalsiBoj();
                if (boj.getVitaz() == this->hraci[i]->getMeno()){
                    this->hraci[i]->setSkore(this->hraci[i]->getSkore()+1);
                } else{
                    this->hraci[j]->setSkore(this->hraci[j]->getSkore()+1);
                }


                delete data;
            }
        }



    this->ukonceny = true;
}

void SpravaTurnaja::pridajHraca(HracServer* hracServer) {
    this->hraci.push_back(hracServer);
}

std::string SpravaTurnaja::vyhodnotTurnaj() {
    int pocitadlo = 0;
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < this->hraci.size(); ++i) {
        if (this->hraci[i]->getSkore() > max) {
            max = this->hraci[i]->getSkore();
            maxIndex = i;
        }
    }
    for (int i = 0; i < hraci.size(); ++i) {

        if (max == hraci[i]->getSkore()){
            pocitadlo++;
        }
    }

    std::string vysledok;

    if (pocitadlo > 1){
        std::cout<<"Hra skoncila remizou"<<std::endl;
        vysledok += "Hra skoncila remizou\n";
    } else{
        std::cout<<"Vyhral "<<hraci[maxIndex]->getMeno()<<std::endl;
        vysledok += ("Vyhral " + hraci[maxIndex]->getMeno() + "\n");
    }

    vysledok += "Skóre Jednotlivých hráčov:\n";


    for (int i = 0; i < this->hraci.size(); ++i) {
        vysledok += ("Meno hraca: " + this->hraci[i]->getMeno() + "\n");
        vysledok += ("Skore: " + std::to_string(this->hraci[i]->getSkore()) + "\n");
    }


    return vysledok;

}

bool SpravaTurnaja::isUkonceny() const {
    return ukonceny;
}

HracServer *SpravaTurnaja::dajHracaNaIndexe(int i) {
    if (i < this->hraci.size()) {
        return this->hraci.at(i);
    }
    return nullptr;
}
