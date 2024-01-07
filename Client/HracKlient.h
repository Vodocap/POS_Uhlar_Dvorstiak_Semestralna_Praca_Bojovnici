//
// Created by matus on 2.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
#include "../Server/Team.h"
#include "SocketClient.h"
#include <iostream>
class HracKlient {

public:
    HracKlient(int peniaze);
    ~HracKlient();
    int getPeniaze() const;
    void setPeniaze(int peniaze);
    void vyziadajMeno();
    void vyziadajVolby();
    std::string getVolba();
    void pripojSaNaServer(std::string adresa, short port);
    void posliUdaje();
    void citajSpravy();

private:
    SocketClient* socketClient;
    int peniaze;
    std::vector<int> volby;
    std::string meno;
public:
    const std::string &getMeno() const;
};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_HRACKLIENT_H
