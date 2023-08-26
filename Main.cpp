#include "includes.hpp"

int main() {
    if (getuid()) std::invalid_argument("You must start the program as SUDO!");
    if (mem::GetPID() == 0) std::invalid_argument("Open the game!");
    Level* level = new Level();
    LocalPlayer* localPlayer = new LocalPlayer();
    std::vector<Player*>* players = new std::vector<Player*>;
    for (int i = 0; i < 70; i++) players->push_back(new Player(i, localPlayer));
    std::vector<Player*>* dummies = new std::vector<Player*>;
    for (int i = 0; i < 15000; i++) dummies->push_back(new Player(i, localPlayer));
    Sense* sense = new Sense(level, localPlayer, players, dummies);
    NoRecoil* norecoil = new NoRecoil(localPlayer);
    TriggerBot* triggerBot = new TriggerBot(localPlayer, players, dummies);

    printf("Starting the main loop... \n");
    int counter = 0;
    while (1) {
        long long startTime = util::currentEpochMillis();
        try {
            level->update();
            if (level->playable) {
                localPlayer->update();
                if (level->trainingArea)
                    for (int i = 0; i < dummies->size(); i++)
                        dummies->at(i)->update();
                if (!level->trainingArea)
                    for (int i = 0; i < players->size(); i++)
                        players->at(i)->update();

                triggerBot->update();
                norecoil->update();
                sense->update(counter);
            }
            else {
                printf("Waiting for a playable level! Sleeping 10 seconds... \n");
                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            }
        }
        catch (...) {
            printf("Error. Sleeping 10 seconds... \n");
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }

        //check how fast we completed all processing and if we have time left to sleep
        int processingTime = static_cast<int>(util::currentEpochMillis() - startTime);
        int goalSleepTime = 16; // 16.67ms=60HZ | 6.97ms=144HZ
        int timeLeftToSleep = std::max(0, goalSleepTime - processingTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeLeftToSleep));
        if (counter < 1000) counter++;
        else counter = 0;
        printf("| LOOP[%04d] OK | Processing time: %02dms | Time left to sleep: %02dms |\n", counter, processingTime, timeLeftToSleep);
    }
}



