//
// Created by matus on 4.1.2024.
//
#include <csignal>
#include "HracKlient.h"
#include "SocketClient.h"

int main() {

        HracKlient hracKlient(18);
        hracKlient.pripojSaNaServer("127.0.0.1", 8080);
        hracKlient.vyziadajMeno();
        hracKlient.vyziadajVolby();
        hracKlient.posliUdaje();
        hracKlient.citajSpravy();


    return 0;

}