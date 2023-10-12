#pragma once
struct AimBot {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    Player* target = nullptr;

    const int STICK_SPEED = 20;
    const float MAX_FOV = 0.5;
    const int MAX_DISTANCE = util::metersToGameUnits(60);

    AimBot(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void aimAssist(int counter) {


        highlightTargetIfExists();
        if (!localPlayer->isCombatReady()) { target = nullptr; return; };
        if (!display->isLeftMouseButtonDown()) { target = nullptr; return; };
        if (target == nullptr) assignTarget();
        if (target == nullptr) return;
        if (!target->visible) return;
        if (target->distance2DToLocalPlayer > MAX_DISTANCE) { target = nullptr; return; };

        //No recoil
        FloatVector2D punchAnglesDiff = localPlayer->punchAnglesDiff;
        int nrPitchIncrement = floor(punchAnglesDiff.x * STICK_SPEED);
        int nrYawIncrement = floor(-punchAnglesDiff.y * STICK_SPEED);

        //Aimbot
        int aimYawIncrement = floor(target->aimbotDesiredAnglesIncrement.y * STICK_SPEED * -1);
        int aimPitchIncrement = floor(target->aimbotDesiredAnglesIncrement.x * STICK_SPEED * 1);

        //move stick
        display->moveControllerAimStick(
            aimPitchIncrement + nrPitchIncrement,
            aimYawIncrement + nrYawIncrement);
    }

    void assignTarget() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady())continue;
            if (!p->enemy) continue;
            if (!p->visible) continue;
            if (p->aimedAt) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.x) > MAX_FOV) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.y) > MAX_FOV) continue;
            if (target == nullptr || p->aimbotScore > target->aimbotScore) target = p;
        }
    }

    void highlightTargetIfExists() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady()) continue;
            p->aimbotLocked = false;
        }
        if (target != nullptr)
            target->aimbotLocked = true;
    }

    int floor(float num) {
        if (num < 0 && num > -1) return -1;
        if (num > 0 && num < 1) return 1;
        return num;
    }
};