//
// Created by matus on 6.1.2024.
//

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H


#include <string>
#include "SpravaTurnaja.h"
#import <netinet/in.h>
class Server {
public:
    Server(char* pAdresa, short pPort, int pPocetHracov);
    ~Server();
    void zapniServer();
    void posli(const std::string *pVypis);
    void skontrolujOdpojenie();

private:
    int valread;
    fd_set readfds;
    char* adresa;
    int addrlen;
    struct sockaddr_in address;
    short port;
    int pocetHracov;
    SpravaTurnaja* spravaTurnaja;
    char buffer[1025];
    int* clientSockets;
    std::string endMessage = ":end";
};


#endif //CLIENT_SERVER_H
