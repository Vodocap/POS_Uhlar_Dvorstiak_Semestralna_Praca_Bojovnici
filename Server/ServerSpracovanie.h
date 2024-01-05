//
// Created by matus on 5.1.2024.
//

#ifndef CLIENT_SERVERSPRACOVANIE_H
#define CLIENT_SERVERSPRACOVANIE_H


#include <string>

class ServerSpracovanie {
public:
    void deserializuj(const std::string& input, std::string& meno, std::string& volby);

};


#endif //CLIENT_SERVERSPRACOVANIE_H
