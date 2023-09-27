#pragma once
struct Player {
    LocalPlayer* myLocalPlayer;
    int index;
    long base;
    std::string name;
    bool dead;
    bool knocked;
    int teamNumber;
    int currentShields;
    int glowEnable;
    int glowThroughWall;
    FloatVector3D localOrigin_prev;
    FloatVector3D localOrigin;
    FloatVector3D localOrigin_predicted;
    int lastTimeVisible;
    int lastTimeVisiblePrev;
    bool visible;
    bool localPlayer;
    bool friendly;
    bool enemy;
    int lastTimeAimedAt;
    int lastTimeAimedAtPrev;
    bool aimedAt;
    float distance3DToLocalPlayer;
    float distance2DToLocalPlayer;
    FloatVector2D desiredViewAngles;
    FloatVector2D desiredViewAnglesSmoothed;
    float distanceToCrosshairs;
    float deltaPitch;
    float deltaYaw;
    int contextId;
    float increment;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
    }

    void readMemory() {
        reset();
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset(); return; }
        name = mem::ReadString(base + off::NAME);
        teamNumber = mem::ReadInt(base + off::TEAM_NUMBER);
        if (!isPlayer() && !isDummie()) { reset(); return; }
        dead = (isDummie()) ? false : mem::ReadShort(base + off::LIFE_STATE) > 0;
        knocked = (isDummie()) ? false : mem::ReadShort(base + off::BLEEDOUT_STATE) > 0;
        currentShields = mem::ReadInt(base + off::CURRENT_SHIELDS);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);
        localOrigin = mem::ReadFloatVector3D(base + off::LOCAL_ORIGIN);
        int playerSpeed = 25;
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(playerSpeed);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        glowEnable = mem::ReadInt(base + off::GLOW_ENABLE);
        glowThroughWall = mem::ReadInt(base + off::GLOW_THROUGH_WALL);
        contextId = mem::Read<int>(base + off::GLOW_HIGHLIGHT_ID + 1);
        lastTimeVisible = mem::ReadInt(base + off::LAST_VISIBLE_TIME);
        visible = (isDummie()) || lastTimeVisiblePrev < lastTimeVisible; //make dummies always visible as the vis check for them is fucked
        lastTimeVisiblePrev = lastTimeVisible;
        lastTimeAimedAt = mem::ReadInt(base + off::LAST_AIMEDAT_TIME);
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;
        lastTimeAimedAtPrev = lastTimeAimedAt;
        if (myLocalPlayer->isValid()) {
            localPlayer = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            distance3DToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            distance2DToLocalPlayer = myLocalPlayer->localOrigin.to2D().distance(localOrigin.to2D());
            if (visible) {
                desiredViewAngles = FloatVector2D(calcDesiredPitch(), calcDesiredYaw());

                //new Yaw
                float smooth = 20;
                increment = calculateYawIncrement(myLocalPlayer->viewAngles.y, desiredViewAngles.y) / smooth;
                smooth = (increment < 0.5) ? 10 : 20;
                float newYaw = clampYaw(myLocalPlayer->viewAngles.y + increment);
                desiredViewAnglesSmoothed.y = newYaw;

                int angelWeight = 20;
                desiredViewAnglesSmoothed = FloatVector2D(
                    calcDesiredPitchWeighted(myLocalPlayer->viewAngles.x, desiredViewAngles.x, angelWeight),
                    newYaw);

                deltaPitch = calcPitchDelta(myLocalPlayer->viewAngles.x, desiredViewAnglesSmoothed.x);
            }
        }
    }

    bool isValid() {
        return base != 0 && (!isPlayer() || !isDummie());
    }

    bool isCombatReady() {
        if (!isValid())return false;
        if (isDummie()) return true;
        if (dead) return false;
        if (knocked) return false;
        return true;
    }

    bool isPlayer() {
        return name == "player";
    }

    bool isDummie() {
        return teamNumber == 97;
    }

    void glow() {
        if (!isValid()) return;
        if (!isPlayer() && !isDummie()) return;
        if (enemy) {
            if (glowEnable != 1)
                mem::Write<int>(base + off::GLOW_ENABLE, 1);
            if (glowThroughWall != 1)
                mem::Write<int>(base + off::GLOW_THROUGH_WALL, 1);
            if (contextId != 0)
                mem::Write<int>(base + off::GLOW_HIGHLIGHT_ID + 1, 0);
        }
    }

    double calcDesiredPitchWeighted(double pitchA, double pitchB, double weight) {
        // Ensure pitchA and pitchB are within the valid range [-89, 89] degrees
        pitchA = std::max(std::min(pitchA, 89.0), -89.0);
        pitchB = std::max(std::min(pitchB, 89.0), -89.0);

        // Calculate the difference between the pitch angles
        double pitchDifference = pitchB - pitchA;

        // Calculate the new pitch angle as a weighted average of pitchA and pitchB
        double result = pitchA + (weight * pitchDifference / 100.0);

        // Ensure the result stays within the valid range [-89, 89] degrees
        result = std::max(std::min(result, 89.0), -89.0);

        return result;
    }

    float calcDesiredPitch() {
        if (localPlayer)return 0;
        //clone & shift so that we are in the coordinate quadrant no. 1
        //biggest apex map is something like 50k wide and long so 100k shift should always be enough
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = myLocalPlayer->localOrigin.add(shift);
        const FloatVector3D originB = localOrigin.add(shift).subtract(FloatVector3D(0, 0, 20)); //subtract a little bit so that we aim at the chest

        //calculate angle
        const float deltaZ = originB.z - originA.z;
        const float pitchInRadians = std::atan2(-deltaZ, distance2DToLocalPlayer);

        //convert and return
        const float degrees = pitchInRadians * (180.0f / M_PI);
        return degrees;
    }

    float calcDesiredYaw() {
        if (localPlayer)return 0;
        //clone & shift so that we are in the coordinate quadrant no. 1
        //biggest apex map is something like 50k wide and long so 100k shift should always be enough
        //we only need x and y to calculate the angle so transform the origins into 2D vectors
        const FloatVector2D shift = FloatVector2D(100000, 100000);
        const FloatVector2D originA = myLocalPlayer->localOrigin.to2D().add(shift);
        const FloatVector2D originB = localOrigin_predicted.to2D().add(shift);

        // //calculate angle
        const FloatVector2D diff = originB.subtract(originA);
        const double yawInRadians = std::atan2(diff.y, diff.x);

        //convert and return
        const float degrees = yawInRadians * (180.0f / M_PI);
        return degrees;
    }

    float calcPitchDelta(float currentPitch, float desiredPitch) {
        float angularDifference = desiredPitch - currentPitch;
        return fabs(angularDifference);
    }

    float calculateYawIncrement(float oldAngle, float newAngle) {
        float wayA = newAngle - oldAngle;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float clampYaw(float angle) {
        float myAngle = angle;
        if (myAngle > 180)
            myAngle = (360 - myAngle) * -1;
        else if (myAngle < -180)
            myAngle = (360 + myAngle);
        return myAngle;
    }

};
