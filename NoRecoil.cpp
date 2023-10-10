#pragma once
struct NoRecoil {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    NoRecoil(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void reduceRecoil(int counter) {
        if (counter % 2 != 0) return;
        if (!display->isLeftMouseButtonDown())  return;
        display->moveControllerAimStick(0, 1);
    }
};