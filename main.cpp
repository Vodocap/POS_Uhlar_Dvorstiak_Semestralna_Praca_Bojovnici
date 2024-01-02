//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"
#include "Team.h"
#include "SimulujBoj.h"


int main() {

    srand(time(NULL));
    Team team1("Jozo",2);
    Team team2("Fero",2);

    team1.vytvorBojovnikov(2,1,0,0,10,5,2,0.6);
    team2.vytvorBojovnikov(2,1,0,0,10,5,2,0.6);

    SimulujBoj simulujBoj;

    simulujBoj.simulujBoj(&team1, &team2);


    return 0;
}