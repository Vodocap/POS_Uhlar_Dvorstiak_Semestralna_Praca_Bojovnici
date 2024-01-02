//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"
#include "Team.h"
#include "SimulujBoj.h"
#include "HracKlient.h"


int main() {

    srand(time(NULL));
    HracKlient hrac1(18);
    HracKlient hrac2(18);
    hrac1.vyziadajMeno();
    hrac2.vyziadajMeno();
    hrac1.vyziadajVolby();

    Team team1(hrac1.getMeno(),2);
    Team team2(hrac2.getMeno(),2);

    team1.vytvorBojovnikov(2,1,0,0,0.5,
                           10,5,2,0.6,1.2);
    team2.vytvorBojovnikov(2,1,0,0,0.5,
                           10,5,2,0.6,1.2);

    SimulujBoj simulujBoj;

    simulujBoj.simulujBoj(&team1, &team2);


    return 0;
}