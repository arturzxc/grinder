#pragma once
struct Sense {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    Sense(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void update() {
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!p->isValid()) continue;
            if (!p->enemy) continue;

            //8 bloodhound (through walls nice)
            //9 caustic            
            int highlightIndex = (p->visible) ? 9 : 8;
            // printf("INDEX: %d", highlightIndex);
            p->setHighlightIndex(highlightIndex);
            p->setHighlightThroughWalls(true);
        }
    }


};
