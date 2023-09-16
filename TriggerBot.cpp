const float TB_MAX_RANGE_ZOOMED = util::metersToGameUnits(100);
const float TB_MAX_RANGE_HIPFRE = util::metersToGameUnits(10);

void triggerBotUpdate(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* myEnemies) {
    if (!localPlayer->isCombatReady()) return;

    //only these weapons will work with trigger bot
    int weaponId = localPlayer->weaponIndex;
    // printf("Current WeaponID :%d", weaponId); //find what we are holding righ now
    if (
        weaponId != 87 &&   //kraber
        weaponId != 100 &&  //p2020
        weaponId != 91 &&   //mozam
        weaponId != 82 &&   //EVA8
        weaponId != 98 &&   //PK
        weaponId != 90 &&   //Mastiff
        weaponId != 103 &&  //Wingman
        weaponId != 80 &&   //Longbow
        weaponId != 1 &&    //Sentinal
        weaponId != 84 &&   //G7
        weaponId != 85 &&   //Hemlock
        weaponId != 105 &&  //30-30
        weaponId != 102 &&  //triple
        weaponId != 107     //namesis
        )return;

    const float RANGE_MAX = (localPlayer->inZoom) ? TB_MAX_RANGE_ZOOMED : TB_MAX_RANGE_HIPFRE;

    for (int i = 0; i < myEnemies->size(); i++) {
        Player* player = myEnemies->at(i);
        if (!player->isCombatReady()) continue;
        if (!player->enemy) continue;
        if (!player->aimedAt) continue;
        if (player->distance3DToLocalPlayer < RANGE_MAX) {
            display->mouseClickLeft();
            break;
        }
    }
}
