//
// Created by matus on 6.1.2024.
//

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H


#include <string>
#include "SpravaTurnaja.h"
class Server {
public:
    Server(char* pAdresa, short pPort, int pPocetHracov);
    void zapniServer();

private:
    char* adresa;
    short port;
    int pocetHracov;
    SpravaTurnaja* spravaTurnaja;
};


#endif //CLIENT_SERVER_H
