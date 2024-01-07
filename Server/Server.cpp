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
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#import <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#define TRUE   1
#define FALSE  0

Server::Server(char* pAdresa, short pPort, int pPocetHracov) : adresa(pAdresa), port(pPort), pocetHracov(pPocetHracov) {
    this->spravaTurnaja = new SpravaTurnaja;
    this->client_socket = new int[pPocetHracov];
}


void Server::zapniServer() {
    srand(time(NULL));

    int opt = TRUE;
    int master_socket , new_socket , activity , sd;
    int max_sd;





      //data buffer of 1K

    //initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < this->pocetHracov; i++)
    {
        this->client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created


    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons( this->port );

    if (bind(master_socket, (struct sockaddr *)&this->address, sizeof(this->address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Poslucha na adrese %s \n", this->adresa);
    printf("port: %d \n", this->port);


    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    this->addrlen = sizeof(this->address);
    std::string putsString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov");
    const char* putsChar = putsString.c_str();
    puts(putsChar);

    int clientNummes = 0;


    while (TRUE) {
        while(clientNummes < 2) {
            //clear the socket set
            FD_ZERO(&this->readfds);

            //add master socket to set
            FD_SET(master_socket, &this->readfds);
            max_sd = master_socket;

            //add child sockets to set
            for (int i = 0; i < this->pocetHracov; i++) {
                //socket descriptor
                sd = this->client_socket[i];

                //if valid socket descriptor then add to read list
                if (sd > 0)
                    FD_SET(sd, &this->readfds);

                //highest file descriptor number, need it for the select function
                if (sd > max_sd)
                    max_sd = sd;
            }

            //wait for an activity on one of the sockets , timeout is NULL ,
            //so wait indefinitely
            activity = select(max_sd + 1, &this->readfds, NULL, NULL, NULL);

            if ((activity < 0) && (errno != EINTR)) {
                printf("select error");
            }

            //If something happened on the master socket ,
            //then its an incoming connection

            if (FD_ISSET(master_socket, &this->readfds)) {
                if ((new_socket = accept(master_socket, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen)) < 0) {
                    exit(EXIT_FAILURE);
                }

                // inform user of socket number - used in send and receive commands
                printf("Hrac pripojeny , socket fd is %d , ip is : %s , port : %d \n ",
                       new_socket, inet_ntoa(this->address.sin_addr), ntohs(this->address.sin_port));

                // Send a welcome message to the newly connected client


                std::string messageString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov kym sa zacne cela hra ");
                strcpy(this->buffer, messageString.c_str());
                send(new_socket, this->buffer, strlen(this->buffer), 0);


                puts("Hrac bol uspesne privitany: ");

                //add new socket to array of sockets
                for (int i = 0; i < this->pocetHracov; i++) {
                    //if position is empty
                    if (this->client_socket[i] == 0) {
                        this->client_socket[i] = new_socket;
                        ++clientNummes;
                        printf("Pocet pripojenych hracov: %d\n", clientNummes);
                        std::string sprava = " , treba este tolkoto hracov " + std::to_string(this->pocetHracov - clientNummes) + "\n";
                        this->posli(&sprava);

                        if ((this->pocetHracov - clientNummes) == 0) {
                            printf("Je pripojeny dostatocny pocet hracov ");
                        } else {
                            printf("Caka sa na tolkoto hracov %d\n", (this->pocetHracov - clientNummes) );
                        }



                        sd = this->client_socket[i];
                        this->valread = read( sd , this->buffer, 1024);
                        std::string pMeno;
                        std::string pVolby;
                        ServerSpracovanie serverSpracovanie;
                        serverSpracovanie.deserializuj(this->buffer, pMeno, pVolby);
                        this->spravaTurnaja->pridajHraca(new HracServer(pVolby, pMeno));
                        this->buffer[this->valread] = '\0';

                        if (this->client_socket[i] != 0) {
                            send(sd , this->buffer , strlen(this->buffer) + 1, 0 );
                        }


                        break;
                    }
                }
            }


        }
        std::string endMessage = "Hra sa skoncila ";
        this->posli(&endMessage);

        if (!this->spravaTurnaja->isUkonceny()) {
            this->spravaTurnaja->prevedBoje();
            std::string vyhodnotenie = this->spravaTurnaja->vyhodnotTurnaj();
            this->skontrolujOdpojenie();
            this->posli(&vyhodnotenie);
            this->posli(&endMessage);


        }








    }
}
void Server::posli(std::string *pVypis) {
    int sd;
    for (int j = 0; j < this->pocetHracov; ++j) {
        if (this->client_socket[j] != 0) {
            strcpy(this->buffer,pVypis->c_str());
            sd = this->client_socket[j];
            this->buffer[sizeof(this->buffer) - 1] = '\0';
            send(sd , this->buffer , strlen(this->buffer) + 1, 0 );
        }

    }

}

void Server::skontrolujOdpojenie() {
    for (int i = 0; i < this->pocetHracov; i++)
    {
        int sd = this->client_socket[i];


        if (FD_ISSET( sd , &readfds))
        {
            //Check if it was for closing , and also read the
            //incoming message
            if ((valread = read( sd , this->buffer, 1024)) == 0)
            {
                //Somebody disconnected , get his details and print
                getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&this->addrlen);
                printf("Hrac odpojeny , ip %s , port %d \n" ,
                       inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                //Close the socket and mark as 0 in list for reuse
                close( sd );
                this->client_socket[i] = 0;
            }

        }
    }
}


