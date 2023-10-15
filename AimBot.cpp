#pragma once
struct AimBot {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    Player* target = nullptr;

    const float MAX_TARGET_ACQUISITION_FOV = 10; //only acquire targets that are no further than 5 degrees from crosshairs
    const float MIN_AIMBOT_REACTION_FOV = 0.1; //if our crosshair is super close to the target angle then stop 
    const int MAX_DISTANCE = util::metersToGameUnits(200);

    AimBot(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void aimAssist(int counter) {
        if (!this->cl->FEATURE_AIMBOT_ON) return;
        highlightTargetIfExists();
        if (!localPlayer->isCombatReady()) { target = nullptr; return; };
        if (!display->keyDown(XK_Shift_L) && !localPlayer->inAttack) { target = nullptr; return; };
        if (target == nullptr) assignTarget();
        if (target == nullptr) return;
        if (!target->visible) return;
        if (target->distance2DToLocalPlayer > MAX_DISTANCE) { target = nullptr; return; };
        mouseMoveAim();
    }

    void mouseMoveAim() {
        //No recoil calcs
        FloatVector2D punchAnglesDiff = localPlayer->punchAnglesDiff.divide(cl->AIMBOT_SMOOTH).multiply(cl->AIMBOT_STICK_SPEED);
        double nrPitchIncrement = punchAnglesDiff.x;
        double nrYawIncrement = -punchAnglesDiff.y;
        //Aimbot calcs
        FloatVector2D aimbotDelta = target->aimbotDesiredAnglesIncrement.divide(cl->AIMBOT_SMOOTH).multiply(cl->AIMBOT_STICK_SPEED);
        double aimYawIncrement = aimbotDelta.y * -1;
        double aimPitchIncrement = aimbotDelta.x;
        //combine
        double totalPitchIncrement = aimPitchIncrement + nrPitchIncrement;
        double totalYawIncrement = aimYawIncrement + nrYawIncrement;
        //turn into integers
        int totalPitchIncrementInt = roundHalfEven(totalPitchIncrement);
        int totalYawIncrementInt = roundHalfEven(totalYawIncrement);
        //are we close enough yet?
        if (fabs(target->aimbotDesiredAnglesIncrement.x) < MIN_AIMBOT_REACTION_FOV) totalPitchIncrementInt = 0;
        if (fabs(target->aimbotDesiredAnglesIncrement.y) < MIN_AIMBOT_REACTION_FOV) totalYawIncrementInt = 0;
        if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0)return;
        //move mouse
        display->moveMouseRelative(totalPitchIncrementInt, totalYawIncrementInt);
    }

    void assignTarget() {
        for (int i = 0;i < players->size();i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady())continue;
            if (!p->enemy) continue;
            if (!p->visible) continue;
            if (p->aimedAt) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.x) > MAX_TARGET_ACQUISITION_FOV) continue;
            if (fabs(p->aimbotDesiredAnglesIncrement.y) > MAX_TARGET_ACQUISITION_FOV) continue;
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

    int roundHalfEven(double x) {
        return (x >= 0.0)
            ? static_cast<int>(std::round(x))
            : static_cast<int>(std::round(-x)) * -1;
    }
};
