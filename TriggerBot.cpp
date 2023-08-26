#pragma once
struct TriggerBot {
    const float TB_MAX_RANGE_ZOOMED = util::metersToGameUnits(50);
    const float TB_MAX_RANGE_HIPFRE = util::metersToGameUnits(10);

    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    Display* display = XOpenDisplay(NULL);

    TriggerBot(Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        if (!localPlayer->isCombatReady()) return;

        //only these weapons will work with trigger bot
        int weaponId = localPlayer->weaponIndex;
        if (weaponId != 100 &&  //p2020
            weaponId != 91 &&   //mozam
            weaponId != 82 &&   //EVA8
            weaponId != 98 &&   //PK
            weaponId != 90 &&   //Mastiff
            weaponId != 103 &&  //Wingman
            weaponId != 80 &&   //Longbow
            weaponId != 1 &&    //Sentinal
            weaponId != 24 &&   //G7
            weaponId != 85 &&   //Hemlock
            weaponId != 105 &&   //30-30
            weaponId != 102 &&   //triple
            weaponId != 107)   //namesis
            return;

        const float RANGE_MAX = (localPlayer->inZoom) ? TB_MAX_RANGE_ZOOMED : TB_MAX_RANGE_HIPFRE;

        if (level->trainingArea)
            for (int i = 0; i < dummies->size(); i++) {
                Player* player = dummies->at(i);
                if (!player->isCombatReady()) continue;
                if (!player->enemy) continue;
                if (!player->aimedAt) continue;
                if (player->distanceToLocalPlayer < RANGE_MAX) {
                    shoot();
                    break;
                }
            }
        else
            for (int i = 0; i < players->size(); i++) {
                Player* player = players->at(i);
                if (!player->isCombatReady()) continue;
                if (!player->enemy) continue;
                if (!player->aimedAt) continue;
                if (player->distanceToLocalPlayer < RANGE_MAX) {
                    shoot();
                    break;
                }
            }
    }

    void shoot() {
        XTestFakeButtonEvent(display, Button1, True, 0);
        XTestFakeButtonEvent(display, Button1, False, 0);
        XFlush(display);
    }

};
