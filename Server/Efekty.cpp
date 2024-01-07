//
// Created by matus on 7.1.2024.
//

#include "Efekty.h"
#include <random>

Efekty::Efekty(int pMaxPocet) : maxPocet(pMaxPocet) {

}


bool Efekty::tryGeneryjPushEfekt(int efekt) {

    if (this->efekty.size() < this->maxPocet) {
        this->efekty.push_back(efekt);
        return true;
    }
    return false;
}

bool Efekty::tryOdoberEfekt(int *efekt) {
    if (this->efekty.size() > 0) {
        *efekt = this->efekty[this->efekty.size() - 1];
        this->efekty.pop_back();
        return true;
    }
    return false;
}

std::size_t Efekty::getEfektySize() {
    return this->efekty.size();
}

bool Efekty::tryAplikujEfekt(Bojovnik* bojovnik, int efekt) {
    if (bojovnik != nullptr) {
        switch (efekt) {
            case 0:
                bojovnik->setZivoty(bojovnik->getZivoty() * 2);
                std::cout << "\033[1;35m🌟 " << bojovnik->getMeno() << " dostal dvojnásobok životov 🌟\033[0m" << std::endl;
                return true;
            case 1:
                bojovnik->setPoskodenie(bojovnik->getPoskodenie() * 2);
                std::cout << "\033[1;33m💥 " << bojovnik->getMeno() << " dostal dvojnásobné poškodenie 💥\033[0m" << std::endl;
                return true;
            case 2:
                bojovnik->setBrnenie(bojovnik->getBrnenie() * 2);
                std::cout << "\033[1;34m🛡️ " << bojovnik->getMeno() << " dostal dvojnásobné brnenie 🛡️\033[0m" << std::endl;
                return true;
        }
    }
    return false;
}


