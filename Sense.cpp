#pragma once
struct Sense {
    const GlowMode visibleEnemyGlowMode = { 124, 107, 60, 100 };
    const GlowMode invisibleEnemyGlowMode = { 126, 107, 60, 100 };

    const GlowMode visibleFriendlyGlowMode = { 124, 4, 60, 100 };
    const GlowMode invisibleFriendlyGlowMode = { 126, 4, 60, 100 };

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
                if (dummy->visible)
                    glow(dummy, 0, 2, 0, visibleEnemyGlowMode);
                else
                    glow(dummy, 2, 0, 0, invisibleEnemyGlowMode);
            }
        else //glow players
            for (int i = 0; i < players->size(); i++) {
                Player* player = players->at(i);
                if (!player->isValid()) continue;
                if (!player->isPlayer()) continue;
                if (player->enemy) {
                    if (player->visible) glow(player, 0, 2, 0, visibleEnemyGlowMode);
                    else glow(player, 2, 0, 0, invisibleEnemyGlowMode);
                }if (player->friendly)
                    if (player->visible) glow(player, 0, 2, 0, visibleFriendlyGlowMode);
                    else glow(player, 2, 0, 0, invisibleFriendlyGlowMode);
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