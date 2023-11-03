#include "includes.cpp"

int main() {
    //load config
    ConfigLoader* cl = new ConfigLoader();

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
    NoRecoil* noRecoil = new NoRecoil(cl, display, level, localPlayer);
    AimBot* aimBot = new AimBot(cl, display, level, localPlayer, players);
    TriggerBot* triggerBot = new TriggerBot(cl, display, level, localPlayer, players);
    Sense* sense = new Sense(cl, display, level, localPlayer, players);

    //begin main loop
    int counter = 0;
    while (1) {
        try {
            //record time so we know how long a single loop iteration takes
            long long startTime = util::currentEpochMillis();

            // will attempt to reload config if there have been any updates to it
            if (counter % 20 == 0) cl->reloadFile();

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

            //read players
            players->clear();
            if (level->trainingArea)
                for (int i = 0; i < dummyPlayers->size(); i++) {
                    Player* p = dummyPlayers->at(i);
                    p->readFromMemory();
                    if (p->isValid()) players->push_back(p);
                }
            else
                for (int i = 0; i < humanPlayers->size(); i++) {
                    Player* p = humanPlayers->at(i);
                    p->readFromMemory();
                    if (p->isValid()) players->push_back(p);
                }

            //run features       
            noRecoil->controlWeapon(counter);
            triggerBot->shootAtEnemy();
            aimBot->aimAssist(counter);
            sense->modifyHighlights();
            sense->glowPlayers();

            //check how fast we completed all the processing and if we still have time left to sleep
            int processingTime = static_cast<int>(util::currentEpochMillis() - startTime);
            int goalSleepTime = 6; // 16.67ms=60HZ | 6.97ms=144HZ
            int timeLeftToSleep = std::max(0, goalSleepTime - processingTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeLeftToSleep));

            //print loop info every now and then
            if (counter % 500 == 0)
                printf("| LOOP[%04d] OK | Processing time: %02dms | Time left to sleep: %02dms | Level: %s |\n",
                    counter, processingTime, timeLeftToSleep, level->name.c_str());

            //update counter
            counter = (counter < 1000) ? ++counter : counter = 0;
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



