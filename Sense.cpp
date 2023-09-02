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
                Player* p = dummies->at(i);
                if (!p->isValid()) continue;
                if (!p->isDummie()) continue;
                // if (dummy->index != 8516) continue;
                glow(p, 100, 0, 0, GlowMode{ 2, 6, (p->targetLocked) ? 120 : 40, 100 });
            }
        else //glow players
            for (int i = 0; i < players->size(); i++) {
                Player* p = players->at(i);
                if (!p->isValid()) continue;
                if (!p->isPlayer()) continue;
                if (p->enemy) {
                    //makes it change color to match shield
                    int shield = p->currentShields;
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
                    // if (player->visible)
                    //     glow(player, 0, 5, 0, GlowMode{ 124, 0, 0, 100 });
                    // else
                    glow(p, R * 5, G * 5, B * 5, GlowMode{ 12, 6, 35, 100 });
                }
                if (p->friendly) glow(p, 0, 0, 0, GlowMode{ 75, 7, 60, 100 });
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

//BODY STYLE VALUES
// NONE(0),
// NOT_SURE_1(-124), //spotty sort of meshy of my color. not through walls
// NOT_SURE_2(-123),
// NOT_SURE_3(-122), //spotty sort of meshy when visible and solid when invisible. not through walls. my color
// NOT_SURE_4(-120), //glass like looking. not through walls. my color
// NOT_SURE_5(-119), //glass like looking. through walls. my color
// NOT_SURE_6(-85), //seems not working
// NOT_SURE_7_NOT_THROUGH_WALLS(112), //solid color. not through walls. my color
// NOT_SURE_8(114), //sort of like caustic. through walls. my color
// NOT_SURE_9(117), //flashing
// PINK(1),
// PINK_NOT_THROUGH_WALLS(110),
// MY_COLOR_ONLY_THROUGH_WALLS(2),
// RED_VISIBLE_GREEN_INVISIBLE_FLASHING(3),
// PULSING_LINE_GLOW(12),
// PULSING_LINE(13),
// BLACK(75),
// WAVE(103),
// MY_COLOR_BRIGHT(109),
// MY_COLOR_2_BRIGHT(118),
// SHARP_PULSING(124),
// SHARP_PULSING_THROUGH_WALLS(126);



//BORDER STYLES
// NONE(0),
// MY_COLOR_BRIGHT(6),
// MY_COLOR_BRIGHT_FADES(102),
// MY_COLOR_DARK(101),
// MY_COLOR_FADES(104),
// PINK(1),
// BLUE(4),
// GOLD_FLASHING(5),
// GOLD(7),
// BROWN(8),
// GOLD_SINGLE_PIXEL(9),
// WAVE_EFFECT(103),
// RED(107),
// RED_BRIGHT(108),
// BREATHING_EFFECT(110),
// HEARTBEAT_EFFECT(110);
