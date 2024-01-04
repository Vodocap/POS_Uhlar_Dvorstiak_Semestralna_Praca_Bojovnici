//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"
#include "Team.h"
#include "SimulujBoj.h"
#include "../Client/HracKlient.h"
#include "HracServer.h"
#include "SpravaTurnaja.h"
#include "ThreadData.h"



int main() {

    srand(time(NULL));


    HracServer hracServer1("010101", "Misko");
    HracServer hracServer2("010101", "josko");
    HracServer hracServer3("010101", "petko");
    SpravaTurnaja turnaj;

    turnaj.pridajHraca(&hracServer1);
    turnaj.pridajHraca(&hracServer2);
    turnaj.pridajHraca(&hracServer3);

    turnaj.prevedBoje();
    turnaj.vyhodnotTurnaj();








    return 0;
}