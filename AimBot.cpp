#pragma once
struct AimBot {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    Player* target = nullptr;

    const float maxDegreesFOV = 0.5;
    const int maxDistance = util::metersToGameUnits(60);

    AimBot(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void aimAssist() {
        highlightTargetIfExists();
        if (!localPlayer->isCombatReady()) { target = nullptr; return; };
        if (!display->isLeftMouseButtonDown()) { target = nullptr; return; };
        if (target == nullptr) assignTarget();
        if (target == nullptr) return;
        if (!target->visible) return;
        if (target->distance2DToLocalPlayer > maxDistance) { target = nullptr; return; };

        //ViewAngles version
        // localPlayer->lookAt(target->aimbotDesiredAnglesSmoothedNoRecoil)


        //Moving controller stick version
        // if(fabs(target->aimbotDesiredAnglesIncrement.y)

        int stickSpeed = 20;

        //SOME SHIT GETS PARSED AS 0 AND WE SHOULD CHANGE IT TO 1 or -1 so the assist keeps working. we only stop when close enought to destination

        int stickYawIncrement = floor(target->aimbotDesiredAnglesIncrement.y * stickSpeed * -1, 1);
        // printf("NEW_INC_YAW: %d\n", stickYawIncrement);

        int stickPitchIncrement = floor(target->aimbotDesiredAnglesIncrement.x * stickSpeed * 1, 1);
        // printf("NEW_INC_PITCH: %d\n", stickPitchIncrement);

        display->moveControllerAimStick(stickYawIncrement, stickPitchIncrement);

    }

    void assignTarget() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady())continue;
            if (!p->enemy) continue;
            if (!p->visible) continue;
            if (p->aimedAt) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.x) > maxDegreesFOV) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.y) > maxDegreesFOV) continue;
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

    int floor(int num, int floor) {
        if (num < 0 && num > -1) return -floor;
        if (num > 0 && num < 1) return floor;
        return num;
    }
};