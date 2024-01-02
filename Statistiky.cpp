//
// Created by dange on 2. 1. 2024.
//

#include "Statistiky.h"


double Statistiky::dajZivotyHodnota(int uroven, int hranica) {
    if (hranica == 0) {
        switch (uroven) {
            case 0:
                return 3;
            case 1:
                return 5;
            case 2:
                return 7;
        }
    } else {
        return 10;
    }
    return 0;
}

double Statistiky::dajBrnenieHodnota(int uroven, int hranica) {
    if (hranica == 0) {
        switch (uroven) {
            case 0:
                return 0;
            case 1:
                return 0.5;
            case 2:
                return 1;
        }
    } else {
        return 2;
    }
    return 0;
}

double Statistiky::dajPoskodenieHodnota(int uroven, int hranica) {
    if (hranica == 0) {
        switch (uroven) {
            case 0:
                return 2.5;
            case 1:
                return 3;
            case 2:
                return 4;
        }
    } else {
        return 6;
    }
    return 0;
}

double Statistiky::dajUnikHodnota(int uroven, int hranica) {
    if (hranica == 0) {
        switch (uroven) {
            case 0:
                return 0;
            case 1:
                return 0.1;
            case 2:
                return 0.15;
        }
    } else {
        return 0.4;
    }
    return 0;
}

double Statistiky::dajRychlostUtokuHodnota(int uroven, int hranica) {
    if (hranica == 1) {
        switch (uroven) {
            case 0:
                return 2.5;
            case 1:
                return 1.0;
            case 2:
                return 0.5;
        }
    } else {
        return 0;
    }
    return 0;
}

int Statistiky::dajPocetBojovnikov(int uroven, int hranica) {
    if (hranica == 0) {
        switch (uroven) {
            case 0:
                return 2;
            case 1:
                return 3;
            case 2:
                return 4;
        }
    } else {
        return 5;
    }
    return 0;
}

void Statistiky::vypisStatistiky(int statistika, int uroven) {
    switch (statistika) {
        case 0:
            std::cout << uroven << ") Zivoty v intervale " << this->dajZivotyHodnota(uroven, 0) << " - " << this->dajZivotyHodnota(uroven, 1) << std::endl;
            break;
        case 1:
            std::cout << uroven << ") Zivoty v intervale " << this->dajBrnenieHodnota(uroven, 0) << " - " << this->dajBrnenieHodnota(uroven, 1) << std::endl;
            break;
        case 2:
            std::cout << uroven << ") Zivoty v intervale " << this->dajPoskodenieHodnota(uroven, 0) << " - " << this->dajPoskodenieHodnota(uroven, 1) << std::endl;
            break;
        case 3:
            std::cout << uroven << ") Zivoty v intervale " << this->dajUnikHodnota(uroven, 0) << " - " << this->dajUnikHodnota(uroven, 1) << std::endl;
            break;
        case 4:
            std::cout << uroven << ") Zivoty v intervale " << this->dajRychlostUtokuHodnota(uroven, 0) << " - " << this->dajRychlostUtokuHodnota(uroven, 1) << std::endl;
            break;
        case 5:
            std::cout << uroven << ") Zivoty v intervale " << this->dajPocetBojovnikov(uroven, 0) << " - " << this->dajPocetBojovnikov(uroven, 1) << std::endl;
            break;
    }

}
