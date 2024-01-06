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
    void posli(std::string *pVypis);

private:
    char* adresa;
    short port;
    int pocetHracov;
    SpravaTurnaja* spravaTurnaja;
    char buffer[1025];
    int* client_socket;
    std::string endMessage = ":end";
};


#endif //CLIENT_SERVER_H
