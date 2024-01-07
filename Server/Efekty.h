//
// Created by matus on 7.1.2024.
//

#ifndef CLIENT_EFEKTY_H
#define CLIENT_EFEKTY_H

#include <vector>
#include "Bojovnik.h"

class Efekty {
private:
    int maxPocet;
    std::vector<int> efekty;
public:
    Efekty(int pMaxPocet);
    bool tryAplikujEfekt(Bojovnik* bojovnik, int efekt);
    std::size_t getEfektySize();
    bool tryGeneryjPushEfekt(int efekt);
    bool tryOdoberEfekt(int *efekt);
};


#endif //CLIENT_EFEKTY_H
