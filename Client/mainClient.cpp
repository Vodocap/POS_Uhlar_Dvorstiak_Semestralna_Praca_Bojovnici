//
// Created by matus on 4.1.2024.
//
#include <csignal>
#include "HracKlient.h"
#include "SocketClient.h"

int main() {

        HracKlient hracKlient(18);
        hracKlient.pripojSaNaServer("frios2.fri.uniza.sk", 12385);
        hracKlient.vyziadajMeno();
        hracKlient.vyziadajVolby();
        hracKlient.posliUdaje();
        hracKlient.citajSpravy();


    return 0;

}