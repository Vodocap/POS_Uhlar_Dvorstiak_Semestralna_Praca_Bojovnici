//
// Created by matus on 4.1.2024.
//
#include <csignal>
#include "HracKlient.h"
#include "SocketClient.h"

int main() {
    try {
        SocketClient* socketClient = SocketClient::createConnection("127.0.0.1", 8080);
        int odpovede = 0;

        HracKlient hracKlient(18);
        hracKlient.vyziadajMeno();
        hracKlient.vyziadajVolby();
        while (odpovede < 3) {
            char buffer[1025];
            int valread = read(socketClient->getNapojSocket(), buffer, 1024);

            std::string output;
            socketClient->serializuj(output,hracKlient.getMeno(), hracKlient.getVolba());
            socketClient->posliData(output);
            if (valread > 0) {
                buffer[valread] = '\0';
                std::cout << "Received: " << buffer << std::endl;
                ++odpovede;
            } else {
                std::cout << "No data received." << std::endl;
            }

        }


    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;

}