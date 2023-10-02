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
        if (!localPlayer->isCombatReady()) { target = nullptr; return; };
        if (!display->keyDown(XK_Shift_L)) { target = nullptr; return; };
        if (target == nullptr) assignTarget();
        if (target == nullptr) return;
        // if (target->aimedAt) return;
        localPlayer->lookAt(target->aimbotDesiredAnglesSmoothedNoRecoil);
    }

    void assignTarget() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady())continue;
            if (!p->enemy) continue;
            if (!p->visible) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.x) > 0.7) continue;//FOV check
            if (fabs(p->aimbotDesiredAnglesIncrement.y) > 0.7) continue;//FOV check            
            if (target == nullptr || p->aimbotScore > target->aimbotScore) target = p;
        }
    }

};