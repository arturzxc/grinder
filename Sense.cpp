const Color S_COLOR_RED = { 1,0,0 };
const Color S_COLOR_PURPLE = { 1,0,2 };
const Color S_COLOR_LIGHT_BLUE = { 0,1,2 };
const Color S_COLOR_WHITE = { 1,1,1 };
const Color S_COLOR_GREEN = { 0,1,0 };
const Color S_COLOR_BLACK = { 0,0,0 };

const int strongMulti = 1;
const Color S_COLOR_STRONG_RED = { 1 * strongMulti,0,0 };
const Color S_COLOR_STRONG_PURPLE = { 1 * strongMulti,0,2 * strongMulti };
const Color S_COLOR_STRONG_LIGHT_BLUE = { 0,1,2 };
const Color S_COLOR_STRONG_WHITE = { 1 * strongMulti,1 * strongMulti,1 * strongMulti };
const Color S_COLOR_STRONG_GREEN = { 0,1 * strongMulti,0 };
const Color S_COLOR_STRONG_BLACK = { 0,0,0 };


void glowPlayer(Player* player, Color color, GlowMode gm) {
    //glow enable through walls
    if (player->glowEnable != 10) mem::WriteInt(player->base + off::GLOW_ENABLE, 10);
    if (player->glowThroughWall != 1) mem::WriteInt(player->base + off::GLOW_THROUGH_WALL, 1);
    //glow color
    FloatVector3D newColor(color.red, color.green, color.blue);
    // if (player->glowColor != newColor) mem::WriteFloatVector3D(player->base + off::GLOW_COLOR, newColor);
    //glow mode
    GlowMode newGlowMode(
        static_cast<std::byte>(gm.bodyStyle),
        static_cast<std::byte>(gm.borderStyle),
        static_cast<std::byte>(gm.borderWidth),
        static_cast<std::byte>(gm.transparency));
    // if (player->glowMode != newGlowMode) mem::WriteGlowMode(player->base + off::GLOW_MODE, newGlowMode);
}

void glowPlayers(std::vector<Player*>* players) {
    for (int i = 0; i < players->size(); i++) {
        Player* p = players->at(i);
        if (!p->isValid()) continue;
        if (!p->isCombatReady()) continue;
        if (p->enemy) {
            if (p->visible)
                glowPlayer(p, S_COLOR_GREEN, GlowMode{ 2, 6, 35, 127 });
            else
                glowPlayer(p, S_COLOR_RED, GlowMode{ 2, 6, 35, 127 });
        }
    }
}

void glowItem(Item* item, Color color, GlowMode gm) {
    // mem::WriteInt(item->base + off::GLOW_ENABLE, 1);
    // mem::WriteInt(item->base + off::GLOW_THROUGH_WALL, 1);
    FloatVector3D newColor(color.red, color.green, color.blue);
    // mem::WriteFloatVector3D(item->base + off::GLOW_COLOR, newColor);
    GlowMode newGlowMode(
        static_cast<std::byte>(gm.bodyStyle),
        static_cast<std::byte>(gm.borderStyle),
        static_cast<std::byte>(gm.borderWidth),
        static_cast<std::byte>(gm.transparency));
    // mem::WriteGlowMode(item->base + off::GLOW_MODE, newGlowMode);
}

void glowItems(std::vector<Item*>* items) {
    for (int i = 0; i < items->size(); i++) {
        Item* p = items->at(i);
        if (!p->isValid()) continue;
        if (!p->isItem()) continue;


        //weapons
        GlowMode weapGlowMode = GlowMode{ 118, 101, 35, 127 };
        if (p->customScript == 23)  //tripple take
            glowItem(p, S_COLOR_PURPLE, weapGlowMode);
        else   if (p->customScript == 90)  //PK & bolts
            glowItem(p, S_COLOR_PURPLE, weapGlowMode);
        else   if (p->customScript == 128)  //3030
            glowItem(p, S_COLOR_PURPLE, weapGlowMode);


        //shields            
        GlowMode shieldsGlowMode = GlowMode{ 118, 101, 35, 127 };
        if (p->customScript == 193 || p->customScript == 198)  //BLUE SHIELD
            glowItem(p, S_COLOR_STRONG_LIGHT_BLUE, shieldsGlowMode);
        else if (p->customScript == 194 || p->customScript == 199)  //PURPLE SHIELD
            glowItem(p, S_COLOR_STRONG_PURPLE, shieldsGlowMode);
        else if (p->customScript == 195 || p->customScript == 200)  //RED SHIELD
            glowItem(p, S_COLOR_STRONG_RED, shieldsGlowMode);
    }
}

