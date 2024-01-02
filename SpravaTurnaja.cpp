//
// Created by matus on 2.1.2024.
//

#include "SpravaTurnaja.h"

void SpravaTurnaja::prevedBoje() {
    // Postupne sa spravi simuluj boj kazdeho hraca s kazdym. Bude bodovanie a na konci sa vyhodnoti ktory hrac vyhral cely turnaj
}

void SpravaTurnaja::pridajHraca(HracServer* hracServer) {
    this->hraci.push_back(hracServer);
}
