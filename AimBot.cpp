#pragma once
struct AimBot {
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    Display* display = XOpenDisplay(NULL);

    AimBot(Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        if (!localPlayer->isCombatReady()) return;
        if (!localPlayer->inAttack && !localPlayer->inZoom) return;

        Player* bestTargetSoFar = findBestTarget();
        if (bestTargetSoFar == 0) return;
        if (bestTargetSoFar->aimedAt) return;

        float smooth = 30;
        float distanceAbs = bestTargetSoFar->distanceToCrosshairs;

        //pitch increment
        float pitchRotationDirection = calcPitchRotationDirection(localPlayer->viewAngles.x, bestTargetSoFar->desiredViewAngles.x);
        float pitchIncrement = (distanceAbs / smooth) * pitchRotationDirection;

        //yaw increment
        float yawRotationDirection = calcYawRotationDirection(localPlayer->viewAngles.y, bestTargetSoFar->desiredViewAngles.y);
        float yawIncrement = (distanceAbs / smooth) * yawRotationDirection;


        //finally add increments to the current angles, clump and write
        FloatVector2D newViewAngles = localPlayer->viewAngles.add(FloatVector2D(pitchIncrement, yawIncrement)).clamp();
        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles);
    }

    Player* findBestTarget() {
        Player* bestTargetSoFar = 0;
        float bestDistanceToCrosshairsSoFar = 999999999;

        if (level->trainingArea)
            for (int i = 0; i < dummies->size(); i++) {
                Player* dummy = dummies->at(i);
                if (!dummy->isCombatReady()) continue;
                if (dummy->localPlayer) continue;
                if (!dummy->visible) continue;
                if (dummy->distanceToCrosshairs > 10) continue;
                if (dummy->distanceToCrosshairs < bestDistanceToCrosshairsSoFar) {
                    bestTargetSoFar = dummy;
                    bestDistanceToCrosshairsSoFar = dummy->distanceToCrosshairs;
                }
            }
        if (!level->trainingArea)
            for (int i = 0; i < players->size(); i++) {
                Player* player = players->at(i);
                if (!player->isCombatReady()) continue;
		if (player->friendly) continue;
                if (player->localPlayer) continue;
                if (!player->visible) continue;
                if (player->distanceToCrosshairs > 10) continue;
                if (player->distanceToCrosshairs < bestDistanceToCrosshairsSoFar) {
                    bestTargetSoFar = player;
                    bestDistanceToCrosshairsSoFar = player->distanceToCrosshairs;
                }
            }

        return bestTargetSoFar;
    }

    int calcYawRotationDirection(int currentYaw, int targetYaw) {
        int clockwiseDistance = (targetYaw - currentYaw + 360) % 360;
        int counterclockwiseDistance = (currentYaw - targetYaw + 360) % 360;
        if (clockwiseDistance <= counterclockwiseDistance)
            return 1;  // Clockwise rotation                
        return -1; // Counterclockwise rotation        
    }

    int calcPitchRotationDirection(int currentPitch, int targetPitch) {
        int clockwiseDistance = (targetPitch - currentPitch + 180) % 180;
        int counterclockwiseDistance = (currentPitch - targetPitch + 180) % 180;
        if (clockwiseDistance <= counterclockwiseDistance)
            return 1;  // upwards    
        return -1; // downwards
    }
};
