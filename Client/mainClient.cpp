//
// Created by matus on 4.1.2024.
//
#include "HracKlient.h"
#include "SocketClient.h"

int main() {
    SocketClient* socketClient = SocketClient::createConnection("frios2.fri.uniza.sk", 10022);

    HracKlient hracKlient(18);
    hracKlient.vyziadajMeno();
    hracKlient.vyziadajVolby();
    std::string output;
    std::cout << socketClient->serializuj(output, hracKlient.getMeno(), hracKlient.getVolba()) << std::endl;
    socketClient->posliData(socketClient->serializuj(output, hracKlient.getMeno(), hracKlient.getVolba()));
    socketClient->posliKoniec();




    return 0;
}