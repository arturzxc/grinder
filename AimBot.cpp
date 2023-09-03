#pragma once
struct AimBot {
    const float SMOOTH = 10;            //The lower the stronger the aimbot. Suggested 100
    const float FOV_MULTIPLIER = 50;    //FOV is dynamic based on distance. Suggested 5

    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    std::vector<Player*>* myEnemies;
    Display* display = XOpenDisplay(NULL);
    Player* target;

    AimBot(
        Level* level,
        LocalPlayer* localPlayer,
        std::vector<Player*>* players,
        std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        if (!localPlayer->isCombatReady()) { target = 0; return; };
        if (level->trainingArea)
            if (!localPlayer->inZoom && !localPlayer->inAttack) { target = 0; return; }; //user ADS for training area
        if (!level->trainingArea)
            if (!localPlayer->inAttack) { target = 0; return; }; //use in attack for matches

        //are we dealing with dummies or players
        myEnemies = (level->trainingArea) ? dummies : players;

        //attempt to acquire a target or return
        if (target == 0 || !target->isCombatReady() || !target->visible)
            target = findBestTarget();
        if (target == 0) return;

        //pitch increment calculation
        float  pitchIncrement = 0;
        {
            float pitchDeadzone = std::max(0.1f, 1700 / target->distance3DToLocalPlayer);
            float deltaPitch = target->deltaPitch;
            if (deltaPitch > pitchDeadzone && deltaPitch < pitchDeadzone * FOV_MULTIPLIER) {//respect the deadzone and max fov
                float pitchRotationDirection = calcPitchRotationDirection(localPlayer->viewAngles.x, target->desiredViewAngles.x);
                pitchIncrement = (deltaPitch * pitchRotationDirection) / SMOOTH;

            }
        }

        //yaw increment calculation
        float yawIncrement = 0;
        {
            float yawDeadzone = std::max(0.1f, 400 / target->distance3DToLocalPlayer);
            float deltaYaw = target->deltaYaw;
            if (deltaYaw > yawDeadzone && deltaYaw < yawDeadzone * FOV_MULTIPLIER) {//respect the deadzone and max fov
                int yawRotationDirection = calcYawRotationDirection(localPlayer->viewAngles.y, target->desiredViewAngles.y);
                yawIncrement = (deltaYaw * yawRotationDirection) / SMOOTH;

            }
        }

        //add increments to the current angles and then clamp clump
        FloatVector2D incrementVector = FloatVector2D(pitchIncrement, yawIncrement);
        if (incrementVector.isZeroVector())return;

        target->targetLocked = true;

        FloatVector2D newViewAngles = localPlayer->viewAngles.add(incrementVector);
        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles.clamp());


    }

    Player* findBestTarget() {
        Player* bestTargetSoFar = 0;
        float bestScoreSoFar = 999999999; //lowest is best
        for (int i = 0; i < myEnemies->size(); i++) {
            Player* p = myEnemies->at(i);
            if (!p->isCombatReady()) continue;
            if (!p->enemy) continue;
            if (!p->visible) continue;
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


    Player* getLockedPlayer() {
        return target;
    }

};
