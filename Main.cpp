#include "includes.hpp"

int main() {
    //basic checks
    if (getuid()) { std::cout << "RUN AS SUDO!\n"; return -1; }
    if (mem::GetPID() == 0) { std::cout << "OPEN THE GAME FIRST!\n"; return -1; }

    //create basic objects
    XDisplay* display = new XDisplay();
    Level* level = new Level();
    LocalPlayer* localPlayer = new LocalPlayer();
    std::vector<Player*>* humanPlayers = new std::vector<Player*>;
    std::vector<Player*>* dummyPlayers = new std::vector<Player*>;
    std::vector<Player*>* players = new std::vector<Player*>;

    //fill in slots for players, dummies and items
    for (int i = 0; i < 70; i++) humanPlayers->push_back(new Player(i, localPlayer));
    for (int i = 0; i < 15000; i++) dummyPlayers->push_back(new Player(i, localPlayer));

    //create features
    // NoRecoil* noRecoil = new NoRecoil(display, level, localPlayer, players);
    AimBot* aimBot = new AimBot(display, level, localPlayer, players);
    TriggerBot* triggerBot = new TriggerBot(display, level, localPlayer, players);
    Sense* sense = new Sense(display, level, localPlayer, players);
    Movement* movement = new Movement(display, level, localPlayer, players);

    //begin main loop
    int counter = 0;
    while (1) {
        try {
            //record time so we know how long a single loop iteration takes
            long long startTime = util::currentEpochMillis();

            //read level and make sure it is playable
            level->readFromMemory();
            if (!level->playable) {
                printf("Waiting for a playable level! Sleeping 10 seconds... \n");
                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
                continue;
            }

            //read localPlayer and make sure he is valid
            localPlayer->readFromMemory();
            if (!localPlayer->isValid()) throw std::invalid_argument("LocalPlayer invalid!");

            players->clear();
            //read dummies
            if (level->trainingArea)
                for (int i = 0; i < dummyPlayers->size(); i++) {
                    Player* p = dummyPlayers->at(i);
                    p->readFromMemory();
                    if (p->isValid()) players->push_back(p);
                }
            //read players
            else
                for (int i = 0; i < humanPlayers->size(); i++) {
                    Player* p = humanPlayers->at(i);
                    p->readFromMemory();
                    if (p->isValid()) players->push_back(p);
                }

            // //run features                
            triggerBot->shootAtEnemy();
            aimBot->aimAssist(counter);
            sense->modifyHighlights();
            sense->glowPlayers();
            // movement->tapStrafe();

            //check how fast we completed all the processing and if we still have time left to sleep
            int processingTime = static_cast<int>(util::currentEpochMillis() - startTime);
            int goalSleepTime = 6; // 16.67ms=60HZ | 6.97ms=144HZ
            int timeLeftToSleep = std::max(0, goalSleepTime - processingTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeLeftToSleep));

            //update counter
            counter = (counter < 1000) ? ++counter : counter = 0;

            //print loop info every now and then
            if (counter == 1 || counter % 700 == 0)
                printf("| LOOP[%04d] OK | Processing time: %02dms | Time left to sleep: %02dms | Level: %s |\n",
                    counter, processingTime, timeLeftToSleep, level->name.c_str());
        }
        catch (std::invalid_argument& e) {
            printf("!!!ERROR!!! %s SLEEPING 10 SECONDS AND TRYING AGAIN! \n", e.what());
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        catch (...) {
            printf("!!!UNKNOWN ERROR!!! SLEEPING 10 SECONDS AND TRYING AGAIN! \n");
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }



}



