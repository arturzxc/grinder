#pragma once
struct AimBot {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    Player* target = nullptr;

    AimBot(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void update() {
        //validations
        if (!localPlayer->isCombatReady()) { target = nullptr; return; };
        if (!display->keyDown(XK_Shift_L)) { target = nullptr; return; };
        //try to find a target
        if (target == nullptr) assignTarget();
        if (target == nullptr) return;

        printf("LP YAW: %.4f \t", localPlayer->viewAngles.y);
        printf("P[%d] YAW: %.4f YAW_SMOOTHED: %.4f AIMED_AT:%d\n",
            target->index, target->aimbotDesiredAngles.y, target->aimbotDesiredAnglesSmoothed.y, target->aimedAt);
        // printf("PLAYER[%d] with score:%f \n", target->index, target->aimbotScore);

        if (target->aimedAt) return;
        localPlayer->lookAt(target->aimbotDesiredAnglesSmoothed);
    }

    void assignTarget() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady())continue;
            if (!p->visible) continue;
            // if (p->index != 8709) continue; //debug only. test specific dummie
            if (target == nullptr || p->aimbotScore > target->aimbotScore) target = p;
        }
    }

};