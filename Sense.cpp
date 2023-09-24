// const Color S_COLOR_RED = { 1,0,0 };
// const Color S_COLOR_PURPLE = { 1,0,2 };
// const Color S_COLOR_LIGHT_BLUE = { 0,1,2 };
// const Color S_COLOR_WHITE = { 1,1,1 };
// const Color S_COLOR_GREEN = { 0,1,0 };
// const Color S_COLOR_BLACK = { 0,0,0 };
// const GlowMode S_GLOW_MODE = { 2, 6, 35, 127 };

void glowPlayer(Player* player, int contextId) {
    if (!player->isValid()) return;
    // if (!player->aimedAt) return;


    // int currentPlayerContextId = mem::Read<int>(player->base + off::GLOW_ACTIVE_STATES + 1);
    // printf("Player[%d] contextId:%d\n", player->index, currentPlayerContextId);

}

void glowPlayers(std::vector<Player*>* players) {
    //Prepare two contexts. The first one for visible enemies and the second one for invisible ones.
    long highlightSettingsPtr = mem::Read<long>(off::REGION + off::GLOW_SETTINGS); //find pointer to all the contexts
    const long HIGHLIGHT_CONTEXT_SIZE = 0x28;

    //TODO: FIGURE THA FUCK OUT WHICH IS THE DEFAULT ENEMY CONTEXT AND FUCK ONLY WITH THAT ONE!

    //Setting #1: For visible enemies

    for (int i = 0;i < 3;i++) {
        GlowMode gm = mem::Read<GlowMode>(highlightSettingsPtr + (HIGHLIGHT_CONTEXT_SIZE * i) + 4);
        gm.bodyStyle = static_cast<std::byte>(112);
        gm.borderStyle = static_cast<std::byte>(108);
        gm.borderWidth = static_cast<std::byte>(40);
        gm.transparency = static_cast<std::byte>(64);
        mem::Write<GlowMode>(highlightSettingsPtr + (HIGHLIGHT_CONTEXT_SIZE * i) + 4, gm);
        mem::Write<Color>(highlightSettingsPtr + (HIGHLIGHT_CONTEXT_SIZE * i) + 8, { 0,100,0 });
    }

    //manupulate player contextIds as needed
    for (int i = 0; i < players->size(); i++) {
        Player* p = players->at(i);
        if (!p->isValid()) continue;
	if (!p->isPlayer() && !p->isDummie()) continue;
        if (p->enemy) {
            // if (p->visible)
            //     glowPlayer(p, visibleEnemyContextId);
            // else
            //     glowPlayer(p, invisibleEnemyContextId);

            mem::Write<int>(p->base + off::GLOW_ENABLE, 1);
            mem::Write<int>(p->base + off::GLOW_THROUGH_WALL, 1);
            mem::Write<int>(p->base + off::GLOW_ACTIVE_STATES + 1, 1);
        }
    }
}

// void glowItem(Item* item, Color color, GlowMode gm) {
    // mem::WriteInt(item->base + off::GLOW_ENABLE, 1);
    // mem::WriteInt(item->base + off::GLOW_THROUGH_WALL, 1);
    // FloatVector3D newColor(color.red, color.green, color.blue);
    // mem::WriteFloatVector3D(item->base + off::GLOW_COLOR, newColor);
    // GlowMode newGlowMode(
    //     static_cast<std::byte>(gm.bodyStyle),
    //     static_cast<std::byte>(gm.borderStyle),
    //     static_cast<std::byte>(gm.borderWidth),
    //     static_cast<std::byte>(gm.transparency));
    // mem::WriteGlowMode(item->base + off::GLOW_MODE, newGlowMode);
// }

// void glowItems(std::vector<Item*>* items) {
    // for (int i = 0; i < items->size(); i++) {
    //     Item* p = items->at(i);
    //     if (!p->isValid()) continue;
    //     if (!p->isItem()) continue;


    //     //weapons
    //     GlowMode weapGlowMode = GlowMode{ 118, 101, 35, 127 };
    //     if (p->customScript == 23)  //tripple take
    //         glowItem(p, S_COLOR_PURPLE, weapGlowMode);
    //     else   if (p->customScript == 90)  //PK & bolts
    //         glowItem(p, S_COLOR_PURPLE, weapGlowMode);
    //     else   if (p->customScript == 128)  //3030
    //         glowItem(p, S_COLOR_PURPLE, weapGlowMode);


    //     //shields            
    //     GlowMode shieldsGlowMode = GlowMode{ 118, 101, 35, 127 };
    //     if (p->customScript == 193 || p->customScript == 198)  //BLUE SHIELD
    //         glowItem(p, S_COLOR_STRONG_LIGHT_BLUE, shieldsGlowMode);
    //     else if (p->customScript == 194 || p->customScript == 199)  //PURPLE SHIELD
    //         glowItem(p, S_COLOR_STRONG_PURPLE, shieldsGlowMode);
    //     else if (p->customScript == 195 || p->customScript == 200)  //RED SHIELD
    //         glowItem(p, S_COLOR_STRONG_RED, shieldsGlowMode);
    // }
// }



    //1  - Target dummy effect.  walls
    //2  - Teammate effect.  walls
    //3  - White outline.  walls
    //4  - Red outline. Not  walls
    //5  - Goldish distorted.  walls
    //6  - Red. No fill.  walls.
    //7  - Dark goldish.  walls.
    //8  - Caustic. No walls.
    //9  - Gold. No walls.
    //10 - Nothing
    //11 - Mad maggie
    //12 - Teammate effect. Fat.  walls
    //13 - Mad maggie. No Walls
    //14 - Mad maggie. No walls. Fat
    //15 - Caustic. Walls
    //16 - Dark gold. Wave effect. walls.
    //17 - Teammate like. walls
    //18 - Goldish. Walls
    //19 - Goldish. Walls
    //20 - Teammate like. Thin. walls.
    //21 - Teammate like. Thin. walls.
    //22 - Teammate like. Thin. walls.
    //23 - Teammate like. Thin. walls.
    //24 - Teammate like. Thin. No walls.
    //25 - Yellow. walls.
    //26 - White breathing. no walls
    //27 - Yellow with fill. walls
    //28 - Yellow with fill. walls
    //29 - Purple with fill. walls
    //30 - White. fill. no walls
    //31 - White. fill. no walls
    //32 - Purple. fill. no walls. fades with distance
    //33 - Yellow. fill. no walls
    //34 - Mad maggie like. the further the more fill. no walls.
    //35 - White no walls
    //36 - Bluish. no walls
    //37 - Purple no walls.
    //38 - Yellow. no walls
    //39 - Hairloom alike
    //40 - white. no walls
    //41 - white. no walls
    //42 - white. no walls
    //43 - white. no walls

    //45 - Red pink outline. walls
    //46 - White black lines fill. walls

    //48 - Green outline only on invisible parts! //bodyStyle:139 borderStyle:140 borderWidth:64 transparency:64 (default minus border)

    //52 fill for invisible and border for visible. default is bodyStyle:141 borderStyle:129 borderWidth:64 transparency:64

    //60 teammate like. walls

    //71 - Black. Walls
