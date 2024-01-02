//
// Created by matus on 2.1.2024.
//

#include <random>
#include "Team.h"

Team::Team(std::string paMeno, int paPocet) {
    this->meno = paMeno;
    this->pocet = paPocet;

}

bool Team::pridajBojovnika(Bojovnik *bojovnik) {
    if (bojovnik == nullptr || bojovnik->getMrtvy()) {
        return false;
    }
    this->teamBojovnikov.push_back(bojovnik);
    return true;
}

void Team::odoberBojovnikaNaIndexe(int index) {
    this->teamBojovnikov.erase(this->teamBojovnikov.begin() + index);
}

int Team::getVelkostTeamu() {
    return this->teamBojovnikov.size();
}

void Team::vymazMrtvychBojovnikov() {
    for (int i = 0; i < this->teamBojovnikov.size(); ++i) {
        if (this->teamBojovnikov.at(i)->getMrtvy()) {
            this->odoberBojovnikaNaIndexe(i);
        }
    }
}



double Team::dajNahodneCisloZIntervalu(double zaciatok, double koniec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(zaciatok, koniec);
    return dis(gen);
}

void Team::vytvorBojovnikov(double dolnaHranicaZivoty, double dolnaHranicaPoskodenie, double dolnaHranicaBrnenie,
                            double dolnaHranicaUnik, double hornaHranicaZivoty, double hornaHranicaPoskodenie,
                            double hornaHranicaBrnenie, double hornaHranicaUnik) {

    for (int i = 0; i < this->pocet; ++i) {
        std::string nazov = "Bojovnik pouzivatela " + this->meno;
        this->pridajBojovnika(new Bojovnik(this->dajNahodneCisloZIntervalu(dolnaHranicaZivoty, hornaHranicaZivoty),
                                           this->dajNahodneCisloZIntervalu(dolnaHranicaPoskodenie, hornaHranicaPoskodenie),
                                           this->dajNahodneCisloZIntervalu(dolnaHranicaBrnenie, hornaHranicaBrnenie),
                                           this->dajNahodneCisloZIntervalu(dolnaHranicaUnik, hornaHranicaUnik), nazov));
    }

}

const std::string &Team::getMeno() const {
    return meno;
}

Bojovnik *Team::dajBojovnikaNaBoj() {
    return this->teamBojovnikov.at(0);
}
