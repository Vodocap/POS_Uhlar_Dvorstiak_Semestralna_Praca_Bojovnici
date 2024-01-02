//
// Created by dange on 2. 1. 2024.
//

#include "Obchod.h"
#include "Statistiky.h"
void Obchod::ukazObchod(int pStatistika) {
    Statistiky stats;
    for (int i = 0; i < 3; ++i) {
        stats.vypisStatistiky(pStatistika, i);
    }
}

