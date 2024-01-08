//
// Created by matus on 6.1.2024.
//

#include <cstring>
#include <csignal>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Server.h"
#include "ServerSpracovanie.h"
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#import <netinet/in.h>
#include <sys/time.h>
#define TRUE   1
#define FALSE  0

Server::Server(char* pAdresa, short pPort, int pPocetHracov) : adresa(pAdresa), port(pPort), pocetHracov(pPocetHracov) {
    this->spravaTurnaja = new SpravaTurnaja;
    this->clientSockets = new int[pPocetHracov];

    for (int i = 0; i < this->pocetHracov; ++i) {
        this->clientSockets[i] = 0;
    }
}

Server::~Server() {
    delete[] this->clientSockets;
    this->clientSockets = nullptr;
    delete this->spravaTurnaja;
    this->spravaTurnaja = nullptr;

}


void Server::zapniServer() {
    srand(time(NULL));

    int opt = TRUE;
    int master_socket , new_socket , activity , sd;
    int max_sd;








    for (int i = 0; i < this->pocetHracov; i++)
    {
        this->clientSockets[i] = 0;
    }


    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons( this->port );

    if (bind(master_socket, (struct sockaddr *)&this->address, sizeof(this->address))<0)
    {
        perror("Bind sa nepodaril");
        exit(EXIT_FAILURE);
    }
    printf("Poslucha na adrese %s \n", this->adresa);
    printf("port: %d \n", this->port);



    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    this->addrlen = sizeof(this->address);
    std::string putsString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov");
    const char* putsChar = putsString.c_str();
    puts(putsChar);

    int clientNummes = 0;


    while (TRUE) {
        while(clientNummes < this->pocetHracov) {

            FD_ZERO(&this->readfds);


            FD_SET(master_socket, &this->readfds);
            max_sd = master_socket;


            for (int i = 0; i < this->pocetHracov; i++) {

                sd = this->clientSockets[i];


                if (sd > 0)
                    FD_SET(sd, &this->readfds);


                if (sd > max_sd)
                    max_sd = sd;
            }


            activity = select(max_sd + 1, &this->readfds, NULL, NULL, NULL);

            if ((activity < 0) && (errno != EINTR)) {
                printf("select error");
            }

            if (FD_ISSET(master_socket, &this->readfds)) {
                if ((new_socket = accept(master_socket, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen)) < 0) {
                    exit(EXIT_FAILURE);
                }


                printf("Hrac pripojeny , socket fd is %d , ip is : %s , port : %d \n ",
                       new_socket, inet_ntoa(this->address.sin_addr), ntohs(this->address.sin_port));


                std::string messageString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov kym sa zacne cela hra \n");
                strcpy(this->buffer, messageString.c_str());
                send(new_socket, this->buffer, strlen(this->buffer), 0);


                puts("Hrac bol uspesne privitany: ");


                for (int i = 0; i < this->pocetHracov; i++) {

                    if (this->clientSockets[i] == 0) {
                        this->clientSockets[i] = new_socket;
                        ++clientNummes;
                        printf("Pocet pripojenych hracov: %d\n", clientNummes);
                        std::string sprava = "treba este tolkoto hracov " + std::to_string(this->pocetHracov - clientNummes) + "\n";
                        this->posli(&sprava);

                        if ((this->pocetHracov - clientNummes) == 0) {
                            printf("Je pripojeny dostatocny pocet hracov ");
                        } else {
                            printf("Caka sa na tolkoto hracov %d\n", (this->pocetHracov - clientNummes) );
                        }



                        sd = this->clientSockets[i];
                        this->valread = read( sd , this->buffer, 1024);
                        std::string pMeno;
                        std::string pVolby;
                        ServerSpracovanie serverSpracovanie;
                        serverSpracovanie.deserializuj(this->buffer, pMeno, pVolby);
                        this->spravaTurnaja->pridajHraca(new HracServer(pVolby, pMeno));
                        this->buffer[this->valread] = '\0';

                        if (this->clientSockets[i] != 0) {
                            send(sd , this->buffer , strlen(this->buffer) + 1, 0 );
                        }


                        break;
                    }
                }
            }


        }
        std::string endMessage = "Hra sa skoncila ";
        std::string spravyZBoja;

        if (!this->spravaTurnaja->isUkonceny()) {
            std::function<void(const std::string&)> mojaFunkcia = [this](const std::string& sprava) {
                this->posli(&sprava);
            };


            this->spravaTurnaja->prevedBoje(mojaFunkcia, spravyZBoja);
            std::string vyhodnotenie = this->spravaTurnaja->vyhodnotTurnaj();
            this->posli(&vyhodnotenie);
            std::string opakovanie = "Hra skoncila, pokracuje este dalsie kolo";
            std::cout << "Posiela sa opakovanie\n";
            sleep(5);
            this->posli(&opakovanie);

            std::string pMeno;
            std::string pVolby;
            ServerSpracovanie serverSpracovanie;

            int pocetVolieb = 0;
            int prejdeny = 0;
            while (pocetVolieb <= this->pocetHracov) {

                if (pocetVolieb == this->pocetHracov) {
                    break;
                }
                for (int i = 0; i < this->pocetHracov; ++i) {
                    std::cout << pocetVolieb << std::endl;
                    sd = this->clientSockets[i];
                    if (sd != prejdeny) {
                        prejdeny = sd;
                        std::cout << pocetVolieb << std::endl;
                        if (pocetVolieb == this->pocetHracov) {
                            break;
                        }
                        this->valread = read( sd , this->buffer, 1024);
                        serverSpracovanie.deserializuj(this->buffer, pMeno, pVolby);
                        this->buffer[this->valread] = '\0';
                        this->spravaTurnaja->dajHracaNaIndexe(i)->setVolby(pVolby);
                        ++pocetVolieb;
                        std::cout << "precitane: " << this->buffer << "zo socket descriptora " << sd << std::endl;
                        std::string potvrdenie = "Prijali sme tvoje vstupy";
                        sleep(1);
                        this->posli(&potvrdenie);
                        sleep(1);
                        break;

                    }

                }

            }



            this->spravaTurnaja->prevedBoje(mojaFunkcia, spravyZBoja);
            vyhodnotenie = this->spravaTurnaja->vyhodnotTurnaj();
            std::cout << "Posiela sa vyhodnotenie " << std::endl;
            sleep(3);
            this->posli(&vyhodnotenie);

            sleep(3);
            std::cout << "Posli endmessage " << std::endl;
            this->posli(&endMessage);
            this->skontrolujOdpojenie();
            break;

        }

        for (int i = 0; i < this->pocetHracov; ++i) {
            if (this->clientSockets[i] > 0) {
                close(this->clientSockets[i]);
                this->clientSockets[i] = 0;
            }
        }

        close(master_socket);
    }
}
void Server::posli(const std::string *pVypis) {
    int sd = 0;
    for (int j = 0; j < this->pocetHracov; ++j) {
        sleep(1);
        if (this->clientSockets[j] != 0 && pVypis != nullptr) {
            strcpy(this->buffer,pVypis->c_str());
            sd = this->clientSockets[j];
            this->buffer[strlen(this->buffer)] = '\0';
            send(sd , this->buffer , strlen(this->buffer) + 1, 0 );
        }

    }

}

void Server::skontrolujOdpojenie() {
    for (int i = 0; i < this->pocetHracov; i++)
    {
        int sd = this->clientSockets[i];


        if (FD_ISSET( sd , &readfds))
        {

            if ((valread = read( sd , this->buffer, 1024)) == 0)
            {
                getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&this->addrlen);
                printf("Hrac odpojeny , ip %s , port %d \n" ,
                       inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                close( sd );
                this->clientSockets[i] = 0;
            }

        }
    }
}


