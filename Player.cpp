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
    FloatVector3D glowColor;
    GlowMode glowMode;
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
        glowColor = FloatVector3D();
        glowMode = GlowMode();
        // lastTimeVisible = 0;
        // lastTimeVisiblePrev = 0;
        visible = false;
        localPlayer = false;
        friendly = false;
        enemy = false;
        // lastTimeAimedAt = 0;
        // lastTimeAimedAtPrev = 0;
        aimedAt = false;
        distance3DToLocalPlayer = 999999999;
        distance2DToLocalPlayer = 999999999;
        desiredViewAngles = FloatVector2D();
        distanceToCrosshairs = 999999999;
    }

    void update() {
        reset();
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset();return; }
        name = mem::ReadString(base + off::NAME);
        if (name != "player" && name != "dynamic_dummie") return;
        if (isPlayer()) { //only for non characters
            dead = mem::ReadShort(base + off::LIFE_STATE) > 0;
            knocked = mem::ReadShort(base + off::BLEEDOUT_STATE) > 0;
        }
        teamNumber = mem::ReadInt(base + off::TEAM_NUMBER);
        currentShields = mem::ReadInt(base + off::CURRENT_SHIELDS);
        localOrigin = mem::ReadFloatVector3D(base + off::LOCAL_ORIGIN);
        glowEnable = mem::ReadInt(base + off::GLOW_ENABLE);
        glowThroughWall = mem::ReadInt(base + off::GLOW_THROUGH_WALL);
        glowColor = mem::ReadFloatVector3D(base + off::GLOW_COLOR);
        glowMode = mem::ReadGlowMode(base + off::GLOW_MODE);

        lastTimeVisiblePrev = lastTimeVisible;
        lastTimeVisible = mem::ReadInt(base + off::LAST_VISIBLE_TIME);
        visible = lastTimeVisiblePrev < lastTimeVisible;

        lastTimeAimedAtPrev = lastTimeAimedAt;
        lastTimeAimedAt = mem::ReadInt(base + off::LAST_AIMEDAT_TIME);
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;

        if (myLocalPlayer->isValid()) {//only calculate if localPlayer is valid
            localPlayer = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            if (visible) { //only calculate for visible targets
                distance3DToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
                distance2DToLocalPlayer = myLocalPlayer->localOrigin.to2D().distance(localOrigin.to2D());
                desiredViewAngles = FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
                distanceToCrosshairs = myLocalPlayer->viewAngles.distance(desiredViewAngles);
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
        return name == "dynamic_dummie";
    }

    float calcDesiredPitch() {
        if (localPlayer)return 0;
        //clone & shift so that we are in the coordinate quadrant no. 1
        //biggest apex map is something like 50k wide and long so 100k shift should always be enough
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = myLocalPlayer->localOrigin.add(shift);
        const FloatVector3D originB = localOrigin.add(shift).subtract(FloatVector3D(0, 0, 15)); //subtract a little bit so that we aim at the chest

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
};