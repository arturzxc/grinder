#pragma once
struct AimBot {
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    std::vector<Player*>* dummies;
    Display* display = XOpenDisplay(NULL);
    Player* target;

    AimBot(Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players, std::vector<Player*>* dummies) {
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
        this->dummies = dummies;
    }

    void update() {
        if (!localPlayer->isCombatReady()) { target = 0; return; };
        if (!localPlayer->inZoom) { target = 0; return; };



        if (target == 0 || !target->isCombatReady()) {
            target = findBestTarget();
            // target->targetLocked = true;
        }
        if (target == 0) return;

        printf("LP_ANGS:%s ", localPlayer->viewAngles.toString().c_str());
        printf("P[%d] D_ANGS: %s ", target->index, target->desiredViewAngles.toString().c_str());


        float smooth = 10;

        //pitch increment
        // float pitchMaxDistance = 15;
        // float pitchDeadzone = std::max(1.0f, 1100 / target->distance3DToLocalPlayer);
        // printf("P[%d] pitchDeadzone: %.6f", target->index, pitchDeadzone);
        float  pitchIncrement = 0;
        // if (target->pitchDelta > pitchDeadzone && target->pitchDelta < pitchMaxDistance) { //if we are not yeat in the deadzone
            // float pitchRotationDirection = calcPitchRotationDirection(localPlayer->viewAngles.x, target->desiredViewAngles.x);
        float deltaPitch = target->deltaPitch;
        pitchIncrement = deltaPitch / smooth;
        // }

        //yaw increment
        float yawMaxDistance = 15;
        float yawDeadzone = std::max(1.0f, 500 / target->distance3DToLocalPlayer);
        // printf(" yawDeadzone: %.6f   ", yawDeadzone);
        float yawIncrement = 0;
        // if (target->yawDelta > yawDeadzone && target->yawDelta < yawMaxDistance) {//if we are not yeat in the deadzone
        // float yawRotationDirection = calcYawRotationDirection(localPlayer->viewAngles.y, target->desiredViewAngles.y);

        float deltaYaw = target->deltaYaw;

        yawIncrement = (deltaYaw / smooth);
        printf(" INCREMENT: %.4f \n", yawIncrement);
        // }

        //finally add increments to the current angles, clump and write
        FloatVector2D incrementVector = FloatVector2D(pitchIncrement, yawIncrement);
        if (incrementVector.isZeroVector())return;
        FloatVector2D newViewAngles = localPlayer->viewAngles.add(incrementVector);

        // 'push' the bot base the point where the sign changes from + to - or vice versa.
        // if (newViewAngles.y < -180) newViewAngles.y = 179;
        // if (newViewAngles.y > 180) newViewAngles.y = -179;

        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles.clamp());


    }

    Player* findBestTarget() {
        Player* bestTargetSoFar = 0;
        float bestScoreSoFar = 999999999; //lowest is best

        if (level->trainingArea)
            for (int i = 0; i < dummies->size(); i++) {
                Player* p = dummies->at(i);
                // if (p->index == 2735) return p;

                if (!p->isCombatReady()) continue;
                if (!p->enemy) continue;

                float deltaPitch = std::abs(p->deltaPitch);
                float deltaYaw = std::abs(p->deltaYaw);


                float myScore = (deltaPitch * deltaPitch) + (deltaYaw * deltaYaw);
                if (myScore < bestScoreSoFar) {
                    bestTargetSoFar = p;
                    bestScoreSoFar = myScore;
                }
            }
        if (!level->trainingArea)
            for (int i = 0; i < players->size(); i++) {
                Player* p = players->at(i);
                if (!p->isCombatReady()) continue;
                if (!p->enemy) continue;
                if (!p->visible) continue;
                float myScore = p->deltaYaw + p->deltaPitch;
                if (myScore < bestScoreSoFar) {
                    bestTargetSoFar = p;
                    bestScoreSoFar = myScore;
                }
            }

        return bestTargetSoFar;
    }



};
