#include "includes.hpp"

int main() {
    //basic checks
    if (getuid()) { std::cout << "RUN AS SUDO!\n"; return -1; }
    if (mem::GetPID() == 0) { std::cout << "OPEN THE GAME FIRST!\n"; return -1; }

    //create base structs
    XDisplay* display = new XDisplay();
    Level* level = new Level();
    LocalPlayer* localPlayer = new LocalPlayer();
    std::vector<Player*>* humanPlayers = new std::vector<Player*>;
    std::vector<Player*>* dummyPlayers = new std::vector<Player*>;
    std::vector<Player*>* players = new std::vector<Player*>;
    std::vector<Item*>* items = new std::vector<Item*>;

    //fill player, dummy and item lists
    for (int i = 0; i < 100; i++) humanPlayers->push_back(new Player(i, localPlayer));
    for (int i = 0; i < 15000; i++) dummyPlayers->push_back(new Player(i, localPlayer));
    for (int i = 0; i < 50000; i++) items->push_back(new Item(i));

    //create features
    AimBot* aimBot = new AimBot(display, level, localPlayer, items, players);
    TriggerBot* triggerBot = new TriggerBot(display, level, localPlayer, items, players);
    Sense* sense = new Sense(display, level, localPlayer, items, players);

    //begin main loop
    int counter = 0;
    while (1) {
        long long startTime = util::currentEpochMillis();

        //read level and make sure it is playable
        level->readMemory();
        if (!level->playable) {
            printf("Waiting for a playable level! Sleeping 10 seconds... \n");
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            continue;
        }

        //read localPlayer and make sure he is valid
        localPlayer->readMemory();
        if (!localPlayer->isValid()) throw new std::invalid_argument("LocalPlayer invalid!");

        //populate players list with human players and dummies if in training range
        players->clear();
        for (int i = 0; i < humanPlayers->size(); i++)
            players->push_back(humanPlayers->at(i));
        if (level->trainingArea)
            for (int i = 0; i < dummyPlayers->size(); i++)
                players->push_back(dummyPlayers->at(i));

        //read players
        for (int i = 0; i < players->size(); i++)
            players->at(i)->readMemory();

        //read items on key press
        if (display->keyDown(XK_R))
            for (int i = 0; i < items->size(); i++)
                items->at(i)->readMemory();

        //run features                
        triggerBot->shootAtEnemy();
        aimBot->moveCrosshairs();
        sense->modifyHighlights();
        sense->glowPlayers();

        //check how fast we completed all the processing and if we still have time left to sleep
        int processingTime = static_cast<int>(util::currentEpochMillis() - startTime);
        int goalSleepTime = 6; // 16.67ms=60HZ | 6.97ms=144HZ
        int timeLeftToSleep = std::max(0, goalSleepTime - processingTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeLeftToSleep));

        //update counter
        counter = (counter < 1000) ? ++counter : counter = 0;

        //print loop info every now and then
        // if (counter == 1 || counter % 500 == 0)
        //     printf("| LOOP[%04d] OK | Processing time: %02dms | Time left to sleep: %02dms |\n",
        //         counter, processingTime, timeLeftToSleep);
    }



}



