#pragma once
struct Sense {
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;

    Sense(Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update(int counter) {
        if (level->trainingArea)//glow dummies
            for (int i = 0; i < dummies->size(); i++) {
                Player* dummy = dummies->at(i);
                if (!dummy->isValid()) continue;
                if (!dummy->isDummie()) continue;
                glow(dummy, 100, 100, 100, GlowMode{ 2, (dummy->aimedAt) ? 108 : 6, (dummy->aimedAt) ? 120 : 40, 100 });
            }
        else //glow players
            for (int i = 0; i < players->size(); i++) {
                Player* player = players->at(i);
                if (!player->isValid()) continue;
                if (!player->isPlayer()) continue;
                if (player->enemy) {
                    //makes it change color to match shield
                    int shield = player->currentShields;
                    int R, G, B;
                    if (shield > 75) {                      //if above 75% shield
                        R = 1; G = 0; B = 2;                //make purple
                    }
                    else if (shield < 76 && shield > 50) {  //if between 75% and 50% shield
                        R = 0; G = 1; B = 2;                //make blue
                    }
                    else if (shield < 51 && shield > 0) { //if between 50% and 0% shield
                        R = 1.5; G = 1.5; B = 1.5;                //make white
                    }
                    else {                                //if 0% shield
                        R = 0; G = 3; B = 0;                //make green
                    }
                    glow(player, R, G, B, GlowMode{ 2, (player->aimedAt) ? 108 : 6, (player->aimedAt) ? 120 : 40, 100 });
                }
                if (player->friendly) glow(player, 0, 2, 0, GlowMode{ 75, 0, 0, 0 });
            }
    }

    void glow(Player* player, float red, float green, float blue, GlowMode gm) {
        //flow enable through walls
        if (player->glowEnable != 1) mem::WriteInt(player->base + off::GLOW_ENABLE, 1);
        if (player->glowThroughWall != 1) mem::WriteInt(player->base + off::GLOW_THROUGH_WALL, 1);

        //glow color
        FloatVector3D newColor(red, green, blue);
        if (player->glowColor != newColor) mem::WriteFloatVector3D(player->base + off::GLOW_COLOR, newColor);

        //glow mode
        GlowMode newGlowMode(
            static_cast<std::byte>(gm.bodyStyle),
            static_cast<std::byte>(gm.borderStyle),
            static_cast<std::byte>(gm.borderWidth),
            static_cast<std::byte>(gm.transparency));
        if (player->glowMode != newGlowMode) mem::WriteGlowMode(player->base + off::GLOW_MODE, newGlowMode);
    }
};
