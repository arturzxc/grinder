const float AB_FOV = 10;
const int AB_ACTIVATION_KEY = XK_Shift_L;        // key code to activate
Player* target;

Player* findNewTarget(std::vector<Player*>* myEnemies) {
    Player* bestTargetSoFar = 0;
    float bestScoreSoFar = 999999999; //lowest is best
    for (int i = 0; i < myEnemies->size(); i++) {
        Player* p = myEnemies->at(i);
        //checks
        if (!p->isCombatReady()) continue;
        if (!p->enemy) continue;
        if (!p->visible) continue;
        if (p->deltaPitch > AB_FOV) continue;
        if (p->deltaYaw > AB_FOV) continue;
        //calculate score
        float deltaPitch = p->deltaPitch;
        float deltaYaw = p->deltaYaw;
        float myScore = deltaPitch + deltaYaw;
        if (myScore < bestScoreSoFar) {
            bestTargetSoFar = p;
            bestScoreSoFar = myScore;
        }
    }
    return bestTargetSoFar;
}

void aimbotUpdate(int counter, XDisplay* display, LocalPlayer* localPlayer, std::vector<Player*>* myEnemies) {
    if (!localPlayer->isCombatReady() || !display->keyDown(AB_ACTIVATION_KEY))
        return;

    //find a target or release the lock
    if (target == 0
        || !target->isCombatReady()
        || !target->visible
        || target->deltaPitch > AB_FOV
        || target->deltaYaw > AB_FOV)
        target = findNewTarget(myEnemies);
    if (target == 0)
        return;

    if (target->aimedAt)
        return;

    mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, target->desiredViewAngles.clamp());
}



