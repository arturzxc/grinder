struct AimBot {
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    Display* display = XOpenDisplay(NULL);

    AimBot(Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        // if (!localPlayer->isCombatReady()) return;
        //only these weapons will work with trigger bot
        // int weaponId = localPlayer->weaponIndex;
        // if (weaponId != 0 &&  //R301
        //     weaponId != 99 && //R99
        //     weaponId != 104)//Volt
        //     return;
        // printf("Aimbot working\n");

        Player* bestTargetSoFar = findBestTarget();
        if (bestTargetSoFar == 0) return;

        printf("\n");
        printf("LP_ANG:%s T_DES_ANGLS[%d]:%s T_DIS_CROSS:%04f \n",
            localPlayer->viewAngles.toString().c_str(),
            bestTargetSoFar->index,
            bestTargetSoFar->desiredViewAngles.toString().c_str(),
            bestTargetSoFar->distanceToCrosshairs);
        printf("\n");
    }

    Player* findBestTarget() {
        Player* bestTargetSoFar = 0;
        float bestDistanceToCrosshairsSoFar = 999999999;

        if (level->trainingArea)
            for (int i = 0; i < dummies->size(); i++) {
                Player* dummy = dummies->at(i);
                if (!dummy->isCombatReady()) continue;
                if (dummy->localPlayer) continue;
                if (!dummy->visible) continue;
                if (dummy->distanceToCrosshairs < bestDistanceToCrosshairsSoFar) {
                    bestTargetSoFar = dummy;
                    bestDistanceToCrosshairsSoFar = dummy->distanceToCrosshairs;
                }

                printf("LP_ANG: %s DUMMY_ANG[%d] %s DIST_CROSSHRS:%04f DUMMY_AMDAT %d DUMM_VIS:%d\n",
                    localPlayer->viewAngles.toString().c_str(),
                    dummy->index,
                    dummy->desiredViewAngles.toString().c_str(),
                    dummy->distanceToCrosshairs,
                    dummy->aimedAt,
                    dummy->visible);
            }

        return bestTargetSoFar;
    }
};