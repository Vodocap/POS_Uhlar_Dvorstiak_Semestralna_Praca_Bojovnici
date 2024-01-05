//
// Created by matus on 5.1.2024.
//

#ifndef CLIENT_SOCKETCLIENT_H
#define CLIENT_SOCKETCLIENT_H
#include <iostream>
#include <string>

class SocketClient {

public:
    static SocketClient* createConnection(std::string servName, short port);
    ~SocketClient();
    void posliData(const std::string& data);
    std::string serializuj(std::string& output, std::string meno, std::string volby);
    void posliKoniec();
protected:
    SocketClient(int socket);

private:
    static const char * endMessage;
    int napojSocket;
};


#endif //CLIENT_SOCKETCLIENT_H
