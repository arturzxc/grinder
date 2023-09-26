struct AimBot {
private:
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Item*>* items;
    std::vector<Player*>* players;

    const int MAX_FOV = 10;
    Player* target = nullptr;

    bool targetValid(Player* p) {
        if (p == nullptr) return false;
        if (!p->isCombatReady()) return false;
        if (!p->enemy)  return false;
        if (!p->visible)  return false;
        if (p->deltaPitch > MAX_FOV)  return false;
        if (p->deltaYaw > MAX_FOV)  return false;
        return true;
    }

    void assignTarget() {
        Player* bestTargetSoFar = nullptr;
        float bestScoreSoFar = 999999999; //lowest is best
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!targetValid(p)) continue;
            float myScore = p->deltaPitch + p->deltaYaw;
            if (myScore < bestScoreSoFar) {
                bestTargetSoFar = p;
                bestScoreSoFar = myScore;
            }
        }
        target = bestTargetSoFar;
        if (target == nullptr)
            printf("No valid target to be assigned can be found \n");
        else
            printf("Target assigned. Target index: %d\n", target->index);
    }

    void reset() {
        target = nullptr;
    }

public:
    AimBot(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Item*>* items, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->items = items;
        this->players = players;
    }

    void moveCrosshairs() {
        //checks
        if (!display->keyDown(XK_Shift_L)) { reset(); return; }
        if (!localPlayer->isCombatReady()) { reset(); return; }

        //try to find a target. if none can be found then just return
        if (!targetValid(target))
            assignTarget();
        if (!targetValid(target)) { reset(); return; }

        //aim at the target
        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, target->desiredViewAngles.clamp());
    }
};
