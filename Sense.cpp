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
        if (counter % 10 != 0) return;
        if (level->trainingArea)//glow dummies
            for (int i = 0; i < dummies->size(); i++) {
                Player* dummy = dummies->at(i);
                if (!dummy->isValid()) continue;
                if (!dummy->isDummie()) continue;
                glow(dummy, 50, 50, 50, 75, 102, dummy->visible ? 80 : 40);
            }
        else //glow players
            for (int i = 0; i < players->size(); i++) {
                Player* player = players->at(i);
                if (!player->isValid()) continue;
                if (!player->isPlayer()) continue;
                if (player->enemy) {
                    if (player->visible) glow(player, 0, 2, 0, 124, 6, 35);
                    else glow(player, 2, 0, 0, 126, 6, 35);
                }if (player->friendly)
                    glow(player, 0, 0, 0, 75, 0, 0);
            }
    }

    void glow(Player* player, float red, float green, float blue, int bodyStyle, int borderStyle, int borderWidth) {
        if (player->glowEnable != 1) mem::WriteInt(player->base + off::GLOW_ENABLE, 1);
        if (player->glowThroughWall != 1) mem::WriteInt(player->base + off::GLOW_THROUGH_WALL, 1);
        FloatVector3D newColor(red, green, blue);
        if (player->glowColor != newColor) mem::WriteFloatVector3D(player->base + off::GLOW_COLOR, newColor);
        ByteVector3D newGlowMode(static_cast<std::byte>(bodyStyle), static_cast<std::byte>(borderStyle), static_cast<std::byte>(borderWidth));
        if (player->glowMode != newGlowMode) mem::WriteByteVector3D(player->base + off::GLOW_MODE_BODY_STYLE, newGlowMode);
    }
};