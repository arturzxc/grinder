#pragma once
struct TriggerBot {
    const bool TB_ONLY_SEMI_AUTO = true;
    const float TB_MAX_RANGE_HAMMER_UNITS = util::metersToGameUnits(10);

    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    Display* display = XOpenDisplay(NULL);

    TriggerBot(LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        if (!localPlayer->isCombatReady()) return;
        if (!localPlayer->weaponSemiAuto) return;
        for (int i = 0; i < players->size(); i++) {
            Player* player = players->at(i);
            if (!player->isCombatReady()) continue;
            if (!player->enemy) continue;
            if (!player->aimedAt) continue;
            if (player->distanceToLocalPlayer < TB_MAX_RANGE_HAMMER_UNITS) {
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
