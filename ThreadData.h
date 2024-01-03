//
// Created by matus on 3.1.2024.
//

#ifndef POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
#define POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
#include "Team.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class ThreadData {
public:
    ThreadData(Team* pTeam1, Team* pTeam2);
    Team* getTeam1();
    Team* getTeam2();
    std::mutex& getMutex();
    std::condition_variable& getMozeutocit();
    std::condition_variable& getNemozeUtocit();


private:
    bool konec;
public:
    bool isKonec() const;

    void setKonec(bool konec);

private:
    Team* team1;
    Team* team2;
    std::mutex mutex;
    std::condition_variable mozeUtocit;
    std::condition_variable nemozeUtocit;

};


#endif //POS_UHLAR_DVORSTIAK_SEMESTRALNA_PRACA_BOJOVNICI_THREADDATA_H
