#pragma once
struct Player {
    LocalPlayer* myLocalPlayer;
    int index;
    long base;
    std::string name;
    bool dead;
    bool knocked;
    int teamNumber;
    int glowEnable;
    int glowThroughWall;
    int highlightId;
    FloatVector3D localOrigin;
    bool isLocalPlayer;
    bool friendly;
    bool enemy;
    int lastTimeAimedAt;
    int lastTimeAimedAtPrev;
    bool aimedAt;
    float distanceToLocalPlayer;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
    }

    void readFromMemory() {
        base = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) return;
        name = mem::ReadString(base + OFF_NAME, 1024);
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER);
        if (!isPlayer() && !isDummie()) { reset(); return; }
        dead = (isDummie()) ? false : mem::Read<short>(base + OFF_LIFE_STATE) > 0;
        knocked = (isDummie()) ? false : mem::Read<short>(base + OFF_BLEEDOUT_STATE) > 0;
        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN);
        glowEnable = mem::Read<int>(base + OFF_GLOW_ENABLE);
        glowThroughWall = mem::Read<int>(base + OFF_GLOW_THROUGH_WALL);
        highlightId = mem::Read<int>(base + OFF_GLOW_HIGHLIGHT_ID + 1);
        lastTimeAimedAt = mem::Read<int>(base + OFF_LAST_AIMEDAT_TIME);
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;
        lastTimeAimedAtPrev = lastTimeAimedAt;
        if (myLocalPlayer->isValid()) {
            isLocalPlayer = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            distanceToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            
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
        if (glowEnable != 1) mem::Write<int>(base + OFF_GLOW_ENABLE, 1);
        if (glowThroughWall != 2) mem::Write<int>(base + OFF_GLOW_THROUGH_WALL, 2);
        if (highlightId != 0) mem::Write<int>(base + OFF_GLOW_HIGHLIGHT_ID + 1, 0);
    }

    float calcDesiredYaw(int weight) {
        if (isLocalPlayer) return 0;
        //clone & shift so that we are in the coordinate quadrant no #1
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
