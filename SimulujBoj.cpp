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


        std::cout << "Bojovnik hraca " << threadData->getTeam1()->getMeno() << " sa pripravuje na utok " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        //std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku())));
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        threadData->getTeam1()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam2()->dajBojovnikaNaBoj());
        threadData->getTeam1()->vymazMrtvychBojovnikov();
        lock.unlock();
        std::cout << "Tim hraca " << threadData->getTeam1()->getMeno() << " Ma teraz tolkoto bojovnikov " << threadData->getTeam1()->getVelkostTeamu() << std::endl;
        std::cout << "Tim hraca " << threadData->getTeam2()->getMeno() << " Ma teraz tolkoto bojovnikov " << threadData->getTeam2()->getVelkostTeamu() << std::endl;

    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();


}

void SimulujBoj::utocDruhy(void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (threadData->getTeam2()->getVelkostTeamu() != 0 || !threadData->isKonec()) {

        std::cout << "Bojovnik hraca " << threadData->getTeam2()->getMeno() << " sa pripravuje na utok " << std::endl;
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(4));
        //std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku())));
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam2()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam1()->dajBojovnikaNaBoj());
        threadData->getTeam2()->vymazMrtvychBojovnikov();
        lock.unlock();
        std::cout << "Tim hraca " << threadData->getTeam1()->getMeno() << " Ma teraz tolkoto bojovnikov " << threadData->getTeam1()->getVelkostTeamu() << std::endl;
        std::cout << "Tim hraca " << threadData->getTeam2()->getMeno() << " Ma teraz tolkoto bojovnikov " << threadData->getTeam2()->getVelkostTeamu() << std::endl;
    }
    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->setKonec(true);
    lock.unlock();

}

//TODO spravit LEPSI VYPIS!