//
// Created by matus on 2.1.2024.
//

#include <random>
#include <csignal>
#include <unistd.h>
#include "SimulujBoj.h"
#include "Team.h"

SimulujBoj::SimulujBoj(const std::function<void(const std::string&)>& spravyFunc) : spravy(spravyFunc) {

}

void SimulujBoj::simulujBoj(void* sharedData, std::string sprava) {
    ThreadData* threadData = (ThreadData*) sharedData;


    if (threadData->getTeam1()->getVelkostTeamu() > 0 && threadData->getTeam2()->getVelkostTeamu() > 0) {


        Team* prvyTeam = threadData->getTeam1();
        Team* druhyTeam = threadData->getTeam2();

        std::cout << "------------------------" << std::endl;
        std::cout << "Tím " << threadData->getTeam1()->getMeno() << " vs. Tím " << threadData->getTeam2()->getMeno() << std::endl;
        std::cout << "------------------------" << std::endl;
        sprava = "------------------------\n Tím " + threadData->getTeam1()->getMeno() + " vs. Tím " + threadData->getTeam2()->getMeno() + "\n"
                + "------------------------\n";
        this->dajStringUtoku(this->spravy, sprava);

        std::thread thUtoc1(utocPrvy, this, std::ref(threadData));
        std::thread thUtoc2(utocDruhy, this ,std::ref(threadData));
        std::thread thEfektyGen(generujEfekty, this, std::ref(threadData));
        std::thread thEfektyApl(aplikujEfekty, this, std::ref(threadData));
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

void SimulujBoj::utocPrvy(SimulujBoj* simulujBoj ,void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;


    //simulujBoj->dajStringUtoku(simulujBoj->spravy, "Jano\n");
    while (threadData->getTeam1()->getVelkostTeamu() != 0 || !threadData->isKonec()) {
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        threadData->getOddychuje().notify_all();
        threadData->setOddychujuci(0);
        std::this_thread::sleep_for(
                std::chrono::duration<double>(threadData->getTeam1()->dajBojovnikaNaBoj()->getRychlostUtoku()));
        threadData->getUtoci().notify_all();
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam1()->vymazMrtvychBojovnikov();
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        std::string messaz;

        if (threadData->getTeam1()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam2()->dajBojovnikaNaBoj(), messaz)) {
            simulujBoj->dajStringUtoku(simulujBoj->spravy, messaz);
        }
        threadData->getOddychuje().notify_all();
        threadData->setOddychujuci(0);
        lock.unlock();
        if (!threadData->getTeam1()->dajBojovnikaNaBoj()->getMrtvy()){

            std::cout << "------------------------" << std::endl;
            std::cout << "Tím " << threadData->getTeam1()->getMeno() << " má " << threadData->getTeam1()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "Tím " << threadData->getTeam2()->getMeno() << " má " << threadData->getTeam2()->getVelkostTeamu() << " bojovníkov." << std::endl;
            std::cout << "------------------------" << std::endl;

        }

    }

    std::cout << "Bojovanie 1 skoncilo " << std::endl;
    threadData->getOddychuje().notify_all();
    threadData->setKonec(true);



}

void SimulujBoj::utocDruhy(SimulujBoj* simulujBoj,void *sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (threadData->getTeam2()->getVelkostTeamu() != 0 || !threadData->isKonec()) {
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        threadData->getOddychuje().notify_all();
        threadData->setOddychujuci(1);
        std::this_thread::sleep_for(std::chrono::duration<double>(threadData->getTeam2()->dajBojovnikaNaBoj()->getRychlostUtoku()));
        threadData->getUtoci().notify_all();
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        threadData->getTeam2()->vymazMrtvychBojovnikov();
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam2()->getVelkostTeamu() == 0) {
            threadData->setKonec(true);
            break;
        }
        if (threadData->getTeam2()->dajBojovnikaNaBoj()->zautoc(threadData->getTeam1()->dajBojovnikaNaBoj(), simulujBoj->sprava)) {
            simulujBoj->dajStringUtoku(simulujBoj->spravy, simulujBoj->sprava);
        }

        threadData->getOddychuje().notify_all();
        threadData->setOddychujuci(1);
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

    threadData->getOddychuje().notify_all();
    threadData->setKonec(true);
    std::cout << "Bojovanie 2 skoncilo " << std::endl;

}

void SimulujBoj::generujEfekty(SimulujBoj* simulujBoj, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (true) {
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        }

        std::cout << "Caka sa 5 sekund kym sa vygeneruje efekt " << std::endl;
        sleep(5);
        std::unique_lock<std::mutex> lock(threadData->getMutex());

        while (!threadData->getEfekty()->tryGeneryjPushEfekt(threadData->getTeam1()->dajNahodneCisloZIntervalu(0,3))) {
            std::cout << "Caka sa kym budu efekty prazdne " << std::endl;
            if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
                break;
            }
            threadData->getPrazdneEfekty().wait(lock);
        }
        lock.unlock();
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        }
        threadData->getPlneEfekty().notify_all();

    }
    std::cout << "Generovanie skoncilo " << std::endl;
    threadData->getOddychuje().notify_all();
    threadData->getPlneEfekty().notify_all();
    threadData->setKonec(true);
}

void SimulujBoj::aplikujEfekty(SimulujBoj* simulujBoj, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    while (true) {
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        }

        int efekt = 0;
        std::unique_lock<std::mutex> lock(threadData->getMutex());
        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        }
        while (!threadData->getEfekty()->tryOdoberEfekt(&efekt)) {
            if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
                break;
            }
            std::cout<<("Caka sa kym sa efekty naplnia")<<std::endl;
            threadData->getPlneEfekty().wait(lock);
        }

        threadData->getPrazdneEfekty().notify_all();
        lock.unlock();


        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        }
        lock.lock();

        if (threadData->getTeam1()->getVelkostTeamu() == 0 || threadData->getTeam1()->getVelkostTeamu() == 1 || threadData->isKonec()) {
            break;
        } else {
            std::cout<<("Caka sa kym bude daky bojovnik oddychovat")<<std::endl;
            threadData->getOddychuje().wait(lock);
        }

        std::string spravaOEfekte;
        if (threadData->getOddychujuci() == 0) {
            threadData->getEfekty()->tryAplikujEfekt(threadData->getTeam1()->dajBojovnikaNaBoj(), efekt, spravaOEfekte);
        } else {
            threadData->getEfekty()->tryAplikujEfekt(threadData->getTeam2()->dajBojovnikaNaBoj(), efekt, spravaOEfekte);
        }
        simulujBoj->dajStringUtoku(simulujBoj->spravy, spravaOEfekte);
        threadData->getPrazdneEfekty().notify_all();
        lock.unlock();
    }
    threadData->getPrazdneEfekty().notify_all();
    threadData->setKonec(true);
    std::cout << "Aplikovanie skoncilo " << std::endl;
}

void SimulujBoj::dajStringUtoku(std::function<void(const std::string &)> posliSpravu, const std::string &sprava) {
    posliSpravu(sprava);
}


