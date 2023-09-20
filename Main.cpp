#include <sstream>
#include <sys/uio.h>
#include <math.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <random>
#include "Offsets.cpp"
#include "Util.cpp"
#include "XDisplay.cpp"
#include "FloatVector2D.cpp"
#include "FloatVector3D.cpp"
#include "GlowMode.cpp"
#include "Color.cpp"
#include "Memory.cpp" 
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Item.cpp"
#include "Sense.cpp"
#include "NoRecoil.cpp"
#include "TriggerBot.cpp"
#include "AimBot.cpp"

int main() {
    //checks
    if (getuid()) { std::cout << "RUN AS SUDO!\n"; return -1; }
    if (mem::GetPID() == 0) { std::cout << "OPEN THE GAME FIRST!\n"; return -1; }
    //declare main structs
    XDisplay display;
    Level level;
    LocalPlayer localPlayer;
    std::vector<Player*> humanPlayers;
    std::vector<Player*> dummyPlayers;
    std::vector<Item*> items;
    //fill players & dummies lists
    for (int i = 0; i < 70; i++) humanPlayers.push_back(new Player(i, &localPlayer));
    for (int i = 0; i < 15000; i++) dummyPlayers.push_back(new Player(i, &localPlayer));
    for (int i = 0; i < 50000; i++) items.push_back(new Item(i));
    //start main loop
    int counter = 0;
    while (1) {
        long long startTime = util::currentEpochMillis();
        try {
            level.readMemory();
            if (level.playable) {
                localPlayer.readMemory();
                std::vector<Player*>* players = (level.trainingArea) ? &dummyPlayers : &humanPlayers;
                for (int i = 0; i < players->size(); i++) players->at(i)->readMemory();
                triggerBotUpdate(&display, &level, &localPlayer, players);
                // glowPlayers(players);
                if (display.keyDown(XK_R)) {
                    for (int i = 0; i < items.size(); i++) items.at(i)->readMemory();
                    // glowItems(&items);
                }
            }
            else {
                printf("Waiting for a playable level! Sleeping 10 seconds... \n");
                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error. Sleeping 30 seconds. Error msg: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(30000));
        }
        //check how fast we completed all the processing and if we still have time left to sleep
        int processingTime = static_cast<int>(util::currentEpochMillis() - startTime);
        int goalSleepTime = 6; // 16.67ms=60HZ | 6.97ms=144HZ
        int timeLeftToSleep = std::max(0, goalSleepTime - processingTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeLeftToSleep));
        if (counter < 1000) counter++;
        else counter = 0;
        printf("| LOOP[%04d] OK | Processing time: %02dms | Time left to sleep: %02dms |\n",
            counter, processingTime, timeLeftToSleep);
    }


}



