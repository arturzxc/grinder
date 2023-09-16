void glowPlayer(Player* player, float red, float green, float blue, GlowMode gm) {
    //glow enable through walls
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

void glowUpdate(std::vector<Player*>* players) {
    for (int i = 0; i < players->size(); i++) {
        Player* p = players->at(i);
        if (!p->isValid()) continue;
        if (p->enemy) {
            if (p->visible) glowPlayer(p, 0, 10, 0, GlowMode{ 2, 6, 35, 127 });
            else glowPlayer(p, 10, 0, 0, GlowMode{ 2, 6, 35, 127 });
        }
        if (p->friendly) glowPlayer(p, 0, 0, 0, GlowMode{ 2, 6, 35, 127 });
    }
}

