//
// Created by matus on 2.1.2024.
//

#include "SimulujBoj.h"
#include "Team.h"

void SimulujBoj::simulujBoj(void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;

    if (threadData->getTeam1()->getVelkostTeamu() > 0 && threadData->getTeam2()->getVelkostTeamu() > 0) {

        Team* prvyTeam = threadData->getTeam1();
        Team* druhyTeam = threadData->getTeam2();
        if ((rand() % 2) == 1) {
            std::cout << "Zacina team hraca " << threadData->getTeam2()->getMeno();
            prvyTeam = threadData->getTeam2();
            druhyTeam = threadData->getTeam1();
        }

        std::thread thUtoc1(utocPrvy, std::ref(threadData));
        std::thread thUtoc2(utocDruhy, std::ref(threadData));
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
    while (threadData->getTeam1()->getVelkostTeamu() != 0 || !threadData->isKonec()) {

        std::cout << "Bojovnik sa pripravuje na utok " << std::endl;
        std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku())));
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam1()->vymazMrtvychBojovnikov();
        while (!threadData->getTeam1()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam2()->dajBojovnikaNaBoj())) {
            std::cout << "Je konec " << std::endl;
            threadData->getMozeutocit().wait(lock);
        }
        threadData->getNemozeUtocit().notify_one();

        lock.unlock();
        if (threadData->isKonec()) {
            break;
        }
    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();


}

void SimulujBoj::utocDruhy(void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (threadData->getTeam2()->getVelkostTeamu() != 0 || !threadData->isKonec()) {

        std::cout << "Bojovnik sa pripravuje na utok " << std::endl;
        std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku())));
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam2()->vymazMrtvychBojovnikov();
        while (!threadData->getTeam2()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam1()->dajBojovnikaNaBoj())) {
            std::cout << "Je konec " << std::endl;
            threadData->getMozeutocit().wait(lock);
        }
        threadData->getNemozeUtocit().notify_one();
        lock.unlock();
        if (threadData->isKonec()) {
            break;
        }
    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();

}




