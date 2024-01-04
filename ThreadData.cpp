//
// Created by matus on 3.1.2024.
//

#include "ThreadData.h"

ThreadData::ThreadData(Team *pTeam1, Team *pTeam2) : team1(pTeam1), team2(pTeam2), konec(false) {

}

Team* ThreadData::getTeam1() {
    return this->team1;
}

Team* ThreadData::getTeam2() {
    return this->team2;
}

std::mutex& ThreadData::getMutex() {
    return this->mutex;
}


bool ThreadData::isKonec() const {
    return konec;
}

void ThreadData::setKonec(bool konec) {
    ThreadData::konec = konec;
}
