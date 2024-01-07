//
// Created by matus on 2.1.2024.
//

#include <random>
#include <csignal>
#include <unistd.h>
#include "SimulujBoj.h"
#include "Team.h"

void SimulujBoj::simulujBoj(void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;

    if (threadData->getTeam1()->getVelkostTeamu() > 0 && threadData->getTeam2()->getVelkostTeamu() > 0) {

        Team* prvyTeam = threadData->getTeam1();
        Team* druhyTeam = threadData->getTeam2();

        std::thread thUtoc1(utocPrvy, std::ref(threadData));
        std::thread thUtoc2(utocDruhy, std::ref(threadData));
        std::thread thEfektyGen(generujEfekty, std::ref(threadData));
        std::thread thEfektyApl(aplikujEfekty, std::ref(threadData));
        thEfektyGen.join();
        thEfektyApl.join();
        thUtoc1.join();
        thUtoc2.join();
        this->vyhodnotVitaza(prvyTeam, druhyTeam);
        std::cout << "Tento zapas vyhral " << this->vitaz << std::endl;

    }

    return;

}

void SimulujBoj::vyhodnotVitaza(Team *team1, Team *team2) {
    if (team1->getVelkostTeamu() > team2->getVelkostTeamu()) {
        this->vitaz = team1->getMeno();
    } else {
        this->vitaz = team2->getMeno();
    }


}

const std::string &SimulujBoj::getVitaz() const {
    return vitaz;
}

void SimulujBoj::utocPrvy(void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    std::cout << "------------------------" << std::endl;
    std::cout << "Tím " << threadData->getTeam1()->getMeno() << " vs. Tím " << threadData->getTeam2()->getMeno() << std::endl;
    std::cout << "------------------------" << std::endl;

    while (threadData->getTeam1()->getVelkostTeamu() != 0 || !threadData->isKonec()) {
        threadData->getOddychuje().notify_all();
        std::this_thread::sleep_for(std::chrono::duration<double>(threadData->getTeam1()->dajBojovnikaNaBoj()->getRychlostUtoku()));
        threadData->getUtoci().notify_all();
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam1()->vymazMrtvychBojovnikov();
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }

        threadData->getTeam1()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam2()->dajBojovnikaNaBoj());

        lock.unlock();
        if (!threadData->getTeam1()->dajBojovnikaNaBoj()->getMrtvy()){
            std::cout << "------------------------" << std::endl;
            std::cout << "Tím " << threadData->getTeam1()->getMeno() << " má " << threadData->getTeam1()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "Tím " << threadData->getTeam2()->getMeno() << " má " << threadData->getTeam2()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "------------------------" << std::endl;
        }

    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();


}

void SimulujBoj::utocDruhy(void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (threadData->getTeam2()->getVelkostTeamu() != 0 || !threadData->isKonec()) {
        threadData->getOddychuje().notify_all();
        std::this_thread::sleep_for(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku()));
        threadData->getUtoci().notify_all();
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam2()->vymazMrtvychBojovnikov();
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }

        threadData->getTeam2()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam1()->dajBojovnikaNaBoj());

        lock.unlock();
        if (!threadData->getTeam2()->dajBojovnikaNaBoj()->getMrtvy()) {
            std::cout << "------------------------" << std::endl;
            std::cout << "Tím " << threadData->getTeam1()->getMeno() << " má "
                      << threadData->getTeam1()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "Tím " << threadData->getTeam2()->getMeno() << " má "
                      << threadData->getTeam2()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();

}

void SimulujBoj::generujEfekty(void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (!threadData->isKonec()) {
        if (threadData->isKonec()) {
            break;
        }
        std::cout << "Caka sa 5 sekund kym sa vygeneruje efekt " << std::endl;
        sleep(5);
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        while (!threadData->getEfekty()->tryGeneryjPushEfekt(threadData->getTeam1()->dajNahodneCisloZIntervalu(0,3))) {
            std::cout << "Caka sa kym budu efekty prazdne " << std::endl;
            threadData->getPrazdneEfekty().wait(lock);
        }
        lock.unlock();
        threadData->getPlneEfekty().notify_all();




    }
}

void SimulujBoj::aplikujEfekty(void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (!threadData->isKonec()) {

        int efekt = 0;
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        while (!threadData->getEfekty()->tryOdoberEfekt(&efekt)) {
            threadData->getPlneEfekty().wait(lock);
        }
        lock.unlock();
        threadData->getPrazdneEfekty().notify_all();


        if (threadData->isKonec()) {
            break;
        }
        lock.lock();
        threadData->getOddychuje().wait(lock);
        if (threadData->getTeam1()->dajNahodneCisloZIntervalu(0.0, 1.0) > 0.5) {
            threadData->getEfekty()->tryAplikujEfekt(threadData->getTeam1()->dajBojovnikaNaBoj(), efekt);
        } else {
            threadData->getEfekty()->tryAplikujEfekt(threadData->getTeam2()->dajBojovnikaNaBoj(), efekt);
        }
        lock.unlock();



    }
}
