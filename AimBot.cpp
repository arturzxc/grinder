struct AimBot {
private:
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Item*>* items;
    std::vector<Player*>* players;
    Player* target = nullptr;

    bool targetValid(Player* p) {
        if (p == nullptr) return false;
        if (!p->isCombatReady()) return false;
        if (!p->enemy)  return false;
        return true;
    }

    void assignTarget(int index) { //for testing
        Player* bestTargetSoFar = nullptr;
        for (int i = 0;i < players->size();i++)
            if (index == players->at(i)->index) {
                target = players->at(i);
            }
        target == bestTargetSoFar;
    }

    void assignTarget() {
        Player* bestTargetSoFar = nullptr;
        float bestScoreSoFar = 999999999; //lowest is best
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!targetValid(p)) continue;
            if (!p->visible)   continue;
            if (fabs(p->increment) > 1) continue;
            if (p->deltaPitch > 3) continue;
            float myScore = p->deltaPitch + p->deltaYaw;
            if (myScore < bestScoreSoFar) {
                bestTargetSoFar = p;
                bestScoreSoFar = myScore;
            }
        }
        target = bestTargetSoFar;
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

        //who are we aiming at
        // for (int i = 0;i < players->size();i++)
        //     if (players->at(i)->isDummie() && players->at(i)->aimedAt)
        //         printf("[%d] \n", players->at(i)->index);


        //checks        
        if (!display->keyDown(XK_Shift_L)) { reset(); return; } //SHIT FAILS TO LOCK BECAUSE BUTTON PRESS NEEDS TO SAVE PREVIOUS STATE

        if (!localPlayer->isCombatReady()) { reset(); return; }

        if (!targetValid(target))
            assignTarget();
        if (!targetValid(target)) { reset(); return; }

        //start moving crosshairs towards the locked target
        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, target->desiredViewAnglesWeighted.clamp());

        //change the flag so that sense highlight this guy more
        if (target != nullptr)
            target->targetLocked = true;
    }
};
