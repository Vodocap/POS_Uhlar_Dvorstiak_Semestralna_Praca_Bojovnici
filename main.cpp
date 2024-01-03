//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"
#include "Team.h"
#include "SimulujBoj.h"
#include "HracKlient.h"
#include "HracServer.h"

#include "ThreadData.h"



int main() {

    srand(time(NULL));
    HracKlient hrac1(18);
    HracKlient hrac2(18);
  
    hrac1.vyziadajMeno();
    hrac2.vyziadajMeno();
   
    hrac1.vyziadajVolby();
    hrac2.vyziadajVolby();
    

    HracServer hracServer1(hrac1.getVolba(), hrac1.getMeno());
    HracServer hracServer2(hrac2.getVolba(), hrac2.getMeno());
    

    SimulujBoj simulujBoj;
    ThreadData threadData(hracServer1.dajTeam(), hracServer2.dajTeam());

    simulujBoj.simulujBoj(&threadData);





    return 0;
}