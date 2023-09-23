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
    FloatVector3D localOrigin;
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
    float distanceToCrosshairs;
    float deltaPitch;
    float deltaYaw;
    bool targetLocked;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
        name = "";
        dead = true;
        knocked = true;
        teamNumber = -1;
        currentShields = -1;
        glowEnable = 5;
        glowThroughWall = 2;
        localOrigin = FloatVector3D();
        visible = false;
        localPlayer = false;
        friendly = false;
        enemy = false;
        aimedAt = false;
        distance3DToLocalPlayer = 999999999;
        distance2DToLocalPlayer = 999999999;
        desiredViewAngles = FloatVector2D();
        deltaYaw = 0;
        deltaPitch = 0;
        targetLocked = false;
    }

    void readMemory() {
        reset();
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset();return; }
        name = mem::ReadString(base + off::NAME);
        teamNumber = mem::ReadInt(base + off::TEAM_NUMBER);
        if (!isPlayer() && !isDummie()) return;
        dead = (isDummie()) ? false : mem::ReadShort(base + off::LIFE_STATE) > 0;
        knocked = (isDummie()) ? false : mem::ReadShort(base + off::BLEEDOUT_STATE) > 0;
        currentShields = mem::ReadInt(base + off::CURRENT_SHIELDS);
        localOrigin = mem::ReadFloatVector3D(base + off::LOCAL_ORIGIN);
        glowEnable = mem::ReadInt(base + off::GLOW_ENABLE);
        glowThroughWall = mem::ReadInt(base + off::GLOW_THROUGH_WALL);
        lastTimeVisible = mem::ReadInt(base + off::LAST_VISIBLE_TIME);
        visible = lastTimeVisiblePrev < lastTimeVisible; //make dummies always visible cause vis check for them is fucked up.
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
            desiredViewAngles = FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
            deltaPitch = CalculatePitchDistance(myLocalPlayer->viewAngles.x, desiredViewAngles.x);
            deltaYaw = CalculateYawDistance(myLocalPlayer->viewAngles.y, desiredViewAngles.y);
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
        const FloatVector2D originB = localOrigin.to2D().add(shift);

        // //calculate angle
        const FloatVector2D diff = originB.subtract(originA);
        const double yawInRadians = std::atan2(diff.y, diff.x);

        //convert and return
        const float degrees = yawInRadians * (180.0f / M_PI);
        return degrees;
    }

    float CalculateYawDistance(float currentYaw, float desiredYaw) {
        float angularDifference = desiredYaw - currentYaw;
        if (angularDifference < -180.0f)
            angularDifference += 360.0f;
        else if (angularDifference > 180.0f) {
            angularDifference -= 360.0f;
        }
        return fabs(angularDifference);
    }

    float CalculatePitchDistance(float currentPitch, float desiredPitch) {
        float angularDifference = desiredPitch - currentPitch;
        return  std::abs(angularDifference);
    }

};
