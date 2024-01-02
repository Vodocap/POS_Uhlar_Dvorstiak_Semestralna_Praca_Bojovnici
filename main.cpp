//
// Created by matus on 30.12.2023.
//

#include "Bojovnik.h"


int main() {
    Bojovnik bojovnik1(10, 5, 2, 0.1);
    Bojovnik bojovnik2(8, 6, 3, 0.5);

    bojovnik1.vypisStav();
    bojovnik2.vypisStav();
    bojovnik1.zautoc(&bojovnik2);
    bojovnik2.zautoc(&bojovnik1);


    return 0;
}