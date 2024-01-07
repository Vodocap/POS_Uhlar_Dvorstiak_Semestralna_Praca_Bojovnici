//
// Created by matus on 30.12.2023.
//


#include "ServerSpracovanie.h"
#include "Server.h"


int main() {


    //Server server("frios2.fri.uniza.sk", 12385, 2);
    Server server("127.0.0.1", 8080, 2);
    server.zapniServer();
    srand(time(NULL));









}