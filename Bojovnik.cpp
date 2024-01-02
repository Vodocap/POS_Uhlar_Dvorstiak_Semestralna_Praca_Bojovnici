//
// Created by matus on 2.1.2024.
//


#include "Bojovnik.h"


Bojovnik::Bojovnik(double pZivoty, double pPoskodenie, double pBrnenie, double pUnik) {
    this->zivoty = pZivoty;
    this->brnenie = pBrnenie;
    this->poskodenie = pPoskodenie;
    this->unik = pUnik;

}

bool Bojovnik::zautoc(Bojovnik *bojovnik) {
    if (bojovnik == nullptr) {
        return false;
    }
    double nahodneCislo = ((double)std::rand() / RAND_MAX);
    std::cout << "cislo: " << nahodneCislo << std::endl;
    if (nahodneCislo < bojovnik->getUnik()) {
        std::cout << "Bojovnik na ktoreho bolo utocene sa vyhol utoku" << std::endl;
        return true;
    }
    if ((bojovnik->getZivoty() - (this->poskodenie - bojovnik->getBrnenie()) <= 0) {

    }
    bojovnik->setZivoty(bojovnik->getZivoty() - (this->poskodenie - bojovnik->getBrnenie()));
    this->vypisStav();
    bojovnik->vypisStav();
}

void Bojovnik::setZivoty(double hodnota) {
    this->zivoty = hodnota;
}

double Bojovnik::getZivoty() {
    return this->zivoty;
}

void Bojovnik::setPoskodenie(double hodnota) {
    this->poskodenie = hodnota;
}

double Bojovnik::getPoskodenie() {
    return this->poskodenie;
}

void Bojovnik::setBrnenie(double hodnota) {
    this->brnenie = hodnota;
}

double Bojovnik::getBrnenie() {
    return this->brnenie;
}

void Bojovnik::setUnik(double hodnota) {
    this->unik = hodnota;
}

double Bojovnik::getUnik() {
    return this->unik;
}

void Bojovnik::vypisStav() {
    std::cout << "Životy: " << this->zivoty << std::endl;
    std::cout << "Brnenie: " << this->brnenie << std::endl;
    std::cout << "Poškodenie: " << this->poskodenie << std::endl;
    std::cout << "Šanca na únik: " << (this->unik * 100) << "%" << std::endl;

}

bool Bojovnik::getMrtvy() {
    return this->mrtvy;
}

void Bojovnik::setMrtvy(bool hodnota) {

}
