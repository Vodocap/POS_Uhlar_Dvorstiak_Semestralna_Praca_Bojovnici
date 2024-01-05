//
// Created by matus on 5.1.2024.
//

#include "SocketClient.h"

#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define SOCKET_TERMINATE_CHAR '\0'

const char* SocketClient::endMessage = ":end";  // modify as needed

SocketClient* SocketClient::createConnection(std::string hostName, short port) {
    struct addrinfo hints, *result = NULL;
    int iResult;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // Resolve the server address and port
    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }

    // Create a SOCKET for connecting to server
    int connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == -1) {
        freeaddrinfo(result);
        throw std::runtime_error("socket failed\n");
    }

    // Connect to server
    iResult = connect(connectSocket, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
    if (iResult == -1) {
        close(connectSocket);
        throw std::runtime_error("Unable to connect to server\n");
    }

    return new SocketClient(connectSocket);
}

SocketClient::SocketClient(int socket) :
        napojSocket(socket) {

}

SocketClient::~SocketClient() {
    if (this->napojSocket != -1) {
        close(this->napojSocket);
        this->napojSocket = -1;
    }
}


void SocketClient::posliData(const std::string &data) {
    size_t data_length = data.length();
    char* buffer = (char*)calloc(data_length + 1, sizeof(char));
    memcpy(buffer, data.c_str(), data_length);
    buffer[data_length] = SOCKET_TERMINATE_CHAR;

    int iResult = send(napojSocket, buffer, data_length + 1, 0);
    free(buffer);
    if (iResult == -1) {
        throw std::runtime_error("send failed\n");
    }
}

void SocketClient::posliKoniec() {
    this->posliData(this->endMessage);
}

std::string SocketClient::serializuj(std::string &output, std::string meno, std::string volby) {
    output += meno + ";" + volby;
    return output;
}

#undef SOCKET_TERMINATE_CHAR
