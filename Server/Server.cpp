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
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#define TRUE   1
#define FALSE  0

Server::Server(char* pAdresa, short pPort, int pPocetHracov) : adresa(pAdresa), port(pPort), pocetHracov(pPocetHracov) {
    this->spravaTurnaja = new SpravaTurnaja;

}


void Server::zapniServer() {
    srand(time(NULL));

    int opt = TRUE;
    int master_socket , addrlen , new_socket , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;




    char buffer[1025];  //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;


    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < this->pocetHracov; i++)
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


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( this->port );

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
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
    addrlen = sizeof(address);
    std::string putsString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov");
    const char* putsChar = putsString.c_str();
    puts(putsChar);

    int clientNummes = 0;


    while (TRUE) {
        while(clientNummes < 2) {
            //clear the socket set
            FD_ZERO(&readfds);

            //add master socket to set
            FD_SET(master_socket, &readfds);
            max_sd = master_socket;

            //add child sockets to set
            for (i = 0; i < this->pocetHracov; i++) {
                //socket descriptor
                sd = this->client_socket[i];

                //if valid socket descriptor then add to read list
                if (sd > 0)
                    FD_SET(sd, &readfds);

                //highest file descriptor number, need it for the select function
                if (sd > max_sd)
                    max_sd = sd;
            }

            //wait for an activity on one of the sockets , timeout is NULL ,
            //so wait indefinitely
            activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

            if ((activity < 0) && (errno != EINTR)) {
                printf("select error");
            }

            //If something happened on the master socket ,
            //then its an incoming connection

            if (FD_ISSET(master_socket, &readfds)) {
                if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                    exit(EXIT_FAILURE);
                }

                // inform user of socket number - used in send and receive commands
                printf("Hrac pripojeny , socket fd is %d , ip is : %s , port : %d \n ",
                       new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                // Send a welcome message to the newly connected client

                std::string messageString = ("caka sa na " + std::to_string(this->pocetHracov) + " hracov");
                strcpy(buffer, messageString.c_str());
                send(new_socket, buffer, strlen(buffer), 0);


                puts("Hrac bol uspesne privitany");

                //add new socket to array of sockets
                for (i = 0; i < this->pocetHracov; i++) {
                    //if position is empty
                    if (this->client_socket[i] == 0) {
                        this->client_socket[i] = new_socket;
                        ++clientNummes;
                        printf("Pocet pripojenych hracov: %d\n", clientNummes);
                        printf("Caka sa na tolkoto hracov %d\n", (this->pocetHracov - clientNummes) );
                        sd = this->client_socket[i];
                        valread = read( sd , buffer, 1024);
                        std::string pMeno;
                        std::string pVolby;
                        ServerSpracovanie serverSpracovanie;
                        serverSpracovanie.deserializuj(buffer, pMeno, pVolby);
                        this->spravaTurnaja->pridajHraca(new HracServer(pVolby, pMeno));
                        buffer[valread] = '\0';
                        send(sd , buffer , strlen(buffer) + 1, 0 );

                        break;
                    }
                }
            }


        }
        std::string endMessage = ":end";
        std::string endMessage1 = ":GENO";
        this->posli(&endMessage1);

        if (!this->spravaTurnaja->isUkonceny()) {
            this->spravaTurnaja->prevedBoje();
            this->spravaTurnaja->vyhodnotTurnaj();
            strcpy(buffer, this->spravaTurnaja->vyhodnotTurnaj().c_str());
            strcpy(buffer, endMessage.c_str());
            for (int j = 0; j < this->pocetHracov; ++j) {
                if (this->client_socket[j] != 0) {
                    sd = this->client_socket[j];
                    buffer[sizeof(buffer) - 1] = '\0';
                    send(sd , buffer , strlen(buffer) + 1, 0 );
                }

            }

        }




        //else its some IO operation on some other socket
        for (i = 0; i < this->pocetHracov; i++)
        {
            sd = this->client_socket[i];


            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);
                    printf("Hrac odpojeny , ip %s , port %d \n" ,
                           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    this->client_socket[i] = 0;
                }

            }
        }


    }
}
void Server::posli(std::string *pVypis) {
    int sd = 0;
    for (int j = 0; j < this->pocetHracov; ++j) {
        if (this->client_socket[j] != 0) {
            strcpy(buffer,pVypis->c_str());
            sd = this->client_socket[j];
            buffer[sizeof(buffer) - 1] = '\0';
            send(sd , buffer , strlen(buffer) + 1, 0 );
        }

    }

}


