//
// Created by matus on 3.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
#include "Team.h"
#include "Efekty.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class ThreadData {
public:
    ThreadData(Team* pTeam1, Team* pTeam2, Efekty* pEfekty);
    Team* getTeam1();
    Team* getTeam2();
    std::mutex& getMutex();



private:
    bool konec;
public:
    bool isKonec() const;

    void setKonec(bool konec);

private:
    Team* team1;
    Team* team2;
    Efekty* efekty;
public:
    Efekty *getEfekty() const;

private:
    std::mutex mutex;
    std::condition_variable utoci;
    std::condition_variable oddychuje;
    std::condition_variable prazdneEfekty;
public:
    std::condition_variable &getPrazdneEfekty();

    std::condition_variable &getPlneEfekty();

private:
    std::condition_variable plneEfekty;

public:

    std::condition_variable& getUtoci();

    std::condition_variable& getOddychuje();



};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
