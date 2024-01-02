//
// Created by matus on 2.1.2024.
//


#include "Bojovnik.h"


Bojovnik::Bojovnik(double pZivoty, double pPoskodenie, double pBrnenie, double pUnik,double pRychlostUtoku,std::string pMeno) {
    this->zivoty = pZivoty;
    this->brnenie = pBrnenie;
    this->poskodenie = pPoskodenie;
    this->unik = pUnik;
    this->mrtvy = false;
    this->rychlostUtoku = pRychlostUtoku;
    this->meno = pMeno;

}

bool Bojovnik::zautoc(Bojovnik *bojovnik) {
    if (this->mrtvy) {
        return false;
    }
    std::cout << this->meno << " utoci na " << bojovnik->getMeno() << std::endl;
    double nahodneCislo = ((double)std::rand() / RAND_MAX);
    if (nahodneCislo < bojovnik->getUnik()) {
        std::cout << bojovnik->getMeno() <<" sa vyhol utoku" << std::endl;
        return true;
    }
    bojovnik->setZivoty(bojovnik->getZivoty() - (this->poskodenie - bojovnik->getBrnenie()));
    this->vypisStav();
    if (bojovnik->getMrtvy()) {
        std::cout << bojovnik->getMeno() <<" zomrel" << std::endl;
        return true;
    }
    bojovnik->vypisStav();

}

void Bojovnik::setZivoty(double hodnota) {
    this->zivoty = hodnota;
    if (this->zivoty <= 0) {
        this->mrtvy = true;
    }

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
    if (this->mrtvy) {
        std::cout << "Mrtvy bojovnik" << std::endl;
        return;
    }
    std::cout << this->meno << std::endl;
    std::cout << "Životy: " << this->zivoty << std::endl;
    std::cout << "Brnenie: " << this->brnenie << std::endl;
    std::cout << "Poškodenie: " << this->poskodenie << std::endl;
    std::cout << "Šanca na únik: " << (this->unik * 100) << "%" << std::endl;

}

bool Bojovnik::getMrtvy() {
    return this->mrtvy;
}

void Bojovnik::setMrtvy(bool hodnota) {
    this->mrtvy = hodnota;
}

std::string Bojovnik::getMeno() {
    return this->meno;
}

double Bojovnik::getRychlostUtoku() const {
    return rychlostUtoku;
}

void Bojovnik::setRychlostUtoku(double rychlostUtoku) {
    Bojovnik::rychlostUtoku = rychlostUtoku;
}


//TODO pridat atribut rychlost utoku