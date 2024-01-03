//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"
#include "Team.h"
#include "SimulujBoj.h"
#include "HracKlient.h"
#include "HracServer.h"
#include "SpravaTurnaja.h"
#include "ThreadData.h"



int main() {

    srand(time(NULL));
    HracKlient hrac1(18);
    HracKlient hrac2(18);
    HracKlient hrac3(18);

    hrac1.vyziadajMeno();
    hrac2.vyziadajMeno();
    hrac3.vyziadajMeno();

    hrac1.vyziadajVolby();
    hrac2.vyziadajVolby();
    hrac3.vyziadajVolby();


    HracServer hracServer1(hrac1.getVolba(), hrac1.getMeno());
    HracServer hracServer2(hrac2.getVolba(), hrac2.getMeno());
    HracServer hracServer3(hrac3.getVolba(), hrac3.getMeno());
    SpravaTurnaja turnaj;

    turnaj.pridajHraca(&hracServer1);
    turnaj.pridajHraca(&hracServer2);
    turnaj.pridajHraca(&hracServer3);

    turnaj.prevedBoje();
    turnaj.vyhodnotTurnaj();








    return 0;
}