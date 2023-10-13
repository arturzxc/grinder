#pragma once
struct Movement {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    Player* target = nullptr;

    Movement(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void tapStrafe() {
        // if (!localPlayer->inJump) return;
        // printf("JUMPING\n");
        // display->spacebarClick();
    }
};