const Color S_COLOR_RED = { 1,0,0 };
const Color S_COLOR_PURPLE = { 1,0,2 };
const Color S_COLOR_LIGHT_BLUE = { 0,1,2 };
const Color S_COLOR_WHITE = { 1,1,1 };
const Color S_COLOR_GREEN = { 0,1,0 };
const Color S_COLOR_BLACK = { 0,0,0 };


void glowPlayer(Player* player, Color color, GlowMode gm) {
    //glow enable through walls
    if (player->glowEnable != 1) mem::WriteInt(player->base + off::GLOW_ENABLE, 1);
    if (player->glowThroughWall != 1) mem::WriteInt(player->base + off::GLOW_THROUGH_WALL, 1);
    //glow color
    FloatVector3D newColor(color.red, color.green, color.blue);
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
            if (p->visible)
                glowPlayer(p, S_COLOR_GREEN, GlowMode{ 2, 6, 35, 127 });
            else
                glowPlayer(p, S_COLOR_RED, GlowMode{ 2, 6, 35, 127 });
        }
        else
            glowPlayer(p, S_COLOR_BLACK, GlowMode{ 2, 6, 35, 127 });
    }
}

void glowItem(Item* item, Color color, GlowMode gm) {
    //glow enable through walls
    mem::WriteInt(item->base + off::GLOW_ENABLE, 1);
    mem::WriteInt(item->base + off::GLOW_THROUGH_WALL, 1);
    //glow color
    FloatVector3D newColor(color.red, color.green, color.blue);
    mem::WriteFloatVector3D(item->base + off::GLOW_COLOR, newColor);
    //glow mode
    GlowMode newGlowMode(
        static_cast<std::byte>(gm.bodyStyle),
        static_cast<std::byte>(gm.borderStyle),
        static_cast<std::byte>(gm.borderWidth),
        static_cast<std::byte>(gm.transparency));
    mem::WriteGlowMode(item->base + off::GLOW_MODE, newGlowMode);
}

void glowItemsUpdate(std::vector<Item*>* items) {
    for (int i = 0; i < items->size(); i++) {
        Item* p = items->at(i);
        if (!p->isValid()) continue;


        if (p->customScript == 23)  //tripple take
            glowItem(p, S_COLOR_RED, GlowMode{ 118, 0, 35, 127 });
        else if (p->customScript == 90)  //PK
            glowItem(p, S_COLOR_RED, GlowMode{ 118, 0, 35, 127 });
        else if (p->customScript == 193)  //BLUE SHIELD
            glowItem(p, S_COLOR_LIGHT_BLUE, GlowMode{ 118, 0, 35, 127 });
        else if (p->customScript == 194)  //PURPLE SHIELD
            glowItem(p, S_COLOR_PURPLE, GlowMode{ 118, 0, 35, 127 });
        else if (p->customScript == 195)  //RED SHIELD
            glowItem(p, S_COLOR_RED, GlowMode{ 118, 0, 35, 127 });



        // { 192, { "Body Armor Level 1", Rarity::Armor }},
        // { 193, { "Body Armor Level 2", Rarity::Armor }},
        // { 194, { "Body Armor Level 3", Rarity::Armor }},
        // { 195, { "Body Armor Level 4", Rarity::Armor }},


    }
}

