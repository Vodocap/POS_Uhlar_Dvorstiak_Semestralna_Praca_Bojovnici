//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"


int main() {
    Bojovnik bojovnik1(10, 5, 0, 0.8, "Bojovnik hraca jozo");
    Bojovnik bojovnik2(8, 6, 0, 0.5, "Bojovnik hraca fero");

    bojovnik1.zautoc(&bojovnik2);
    bojovnik2.zautoc(&bojovnik1);
    bojovnik1.zautoc(&bojovnik2);
    bojovnik2.zautoc(&bojovnik1);

    bojovnik1.vypisStav();
    bojovnik2.vypisStav();



    return 0;
}