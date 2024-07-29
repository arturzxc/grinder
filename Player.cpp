#pragma once
struct Player {
    LocalPlayer* myLocalPlayer;
    int index;
    long base;
    std::string name;
    bool dead;
    bool knocked;
    int ducking;
    int teamNumber;
    int currentHealth;
    int currentShields;
    int glowEnable;
    int glowThroughWall;
    FloatVector3D localOrigin_prev;
    FloatVector3D localOrigin;
    FloatVector3D localOrigin_predicted;
    bool local;
    bool friendly;
    bool enemy;
    int lastTimeAimedAt;
    int lastTimeAimedAtPrev;
    bool aimedAt;
    int lastTimeVisible;
    int lastTimeVisiblePrev;
    bool visible;
    float distanceToLocalPlayer;
    float distance2DToLocalPlayer;
    //values used by aimbot
    bool aimbotLocked;
    FloatVector2D aimbotDesiredAngles;
    FloatVector2D aimbotDesiredAnglesIncrement;
    FloatVector2D aimbotDesiredAnglesSmoothed;
    FloatVector2D aimbotDesiredAnglesSmoothedNoRecoil;
    float aimbotScore;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
    }

    void readFromMemory() {
        base = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((index + 1) << 5), "Player base");
        if (!mem::Valid(base))return;
        name = mem::ReadString(base + OFF_NAME, 1024, "Player name");
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER, "Player teamNumber");
        currentHealth = mem::Read<int>(base + OFF_CURRENT_HEALTH, "Player currentHealth");
        currentShields = mem::Read<int>(base + OFF_CURRENT_SHIELDS, "Player currentShields");
        if (!isPlayer() && !isDummie()) { reset(); return; }
        dead = (isDummie()) ? false : mem::Read<short>(base + OFF_LIFE_STATE, "Player dead") > 0;
        knocked = (isDummie()) ? false : mem::Read<short>(base + OFF_BLEEDOUT_STATE, "Player knocked") > 0;

        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN, "Player localOrigin");
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(20);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);

        glowEnable = mem::Read<int>(base + OFF_GLOW_HIGHLIGHT_ID, "Player glowEnable");
        glowThroughWall = mem::Read<int>(base + OFF_GLOW_THROUGH_WALL, "Playeasdasdr glowThroughWall");

        lastTimeAimedAt = mem::Read<int>(base + OFF_LAST_AIMEDAT_TIME, "Player lastTimeAimedAt");
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;
        lastTimeAimedAtPrev = lastTimeAimedAt;

        lastTimeVisible = mem::Read<int>(base + OFF_LAST_VISIBLE_TIME, "Player lastTimeVisible");
        visible = isDummie() || aimedAt || lastTimeVisiblePrev < lastTimeVisible; //aimedAt is only true when looking at unobscured target. Helps the shit in-game vis check a bit.
        lastTimeVisiblePrev = lastTimeVisible;

        if (myLocalPlayer->isValid()) {
            local = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            distanceToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            distance2DToLocalPlayer = myLocalPlayer->localOrigin.to2D().distance(localOrigin.to2D());
            if (visible) {
                aimbotDesiredAngles = calcDesiredAngles();
                aimbotDesiredAnglesIncrement = calcDesiredAnglesIncrement();
                aimbotScore = calcAimbotScore();
            }
        }

    }

    bool isValid() {
        return base != 0
            && currentHealth > 0
            && (isPlayer() || isDummie());
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

    void setHighlightThroughWalls(bool glow) {
        long ptrLong = base + OFF_GLOW_THROUGH_WALL;
        mem::Write<int>(ptrLong, ((glow) ? 1 : 0));
    }


    void setHighlightIndex(int highlightIndex) {
        long ptrLong = base + OFF_GLOW_HIGHLIGHT_ID;
        mem::Write<int>(ptrLong, highlightIndex);
    }

    FloatVector2D calcDesiredAngles() {
        return FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
    }

    float calcDesiredPitch() {
        if (local) return 0;
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = myLocalPlayer->localOrigin.add(shift);
        const float extraZ = (ducking != -1) ? 10 : 0;
        const FloatVector3D originB = localOrigin_predicted.add(shift).subtract(FloatVector3D(0, 0, extraZ));
        const float deltaZ = originB.z - originA.z;
        const float pitchInRadians = std::atan2(-deltaZ, distance2DToLocalPlayer);
        const float degrees = pitchInRadians * (180.0f / M_PI);
        return degrees;
    }

    float calcDesiredYaw() {
        if (local) return 0;
        const FloatVector2D shift = FloatVector2D(100000, 100000);
        const FloatVector2D originA = myLocalPlayer->localOrigin.to2D().add(shift);
        const FloatVector2D originB = localOrigin_predicted.to2D().add(shift);
        const FloatVector2D diff = originB.subtract(originA);
        const double yawInRadians = std::atan2(diff.y, diff.x);
        const float degrees = yawInRadians * (180.0f / M_PI);
        return degrees;
    }

    FloatVector2D calcDesiredAnglesIncrement() {
        return FloatVector2D(calcPitchIncrement(), calcYawIncrement());
    }

    float calcPitchIncrement() {
        float wayA = aimbotDesiredAngles.x - myLocalPlayer->viewAngles.x;
        float wayB = 180 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcYawIncrement() {
        float wayA = aimbotDesiredAngles.y - myLocalPlayer->viewAngles.y;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcAimbotScore() {
        return (1000 - (fabs(aimbotDesiredAnglesIncrement.x) + fabs(aimbotDesiredAnglesIncrement.y)));
    }

    void print() const {
        printf("____________________________________________________________________________\n");
        printf("Player[%d]____base: %s\n", index, util::longToHexString(base).c_str());
        printf("Player[%d]____name: %s\n", index, name.c_str());
        printf("Player[%d]____dead: %d\n", index, dead);
        printf("Player[%d]____knocked: %d\n", index, knocked);
        printf("Player[%d]____ducking: %d\n", index, ducking);
        printf("Player[%d]____teamNumber: %d\n", index, teamNumber);
        printf("Player[%d]____currentHealth: %d\n", index, currentHealth);
        printf("Player[%d]____currentShields: %d\n", index, currentShields);
        printf("Player[%d]____glowEnable: %d\n", index, glowEnable);
        printf("Player[%d]____glowThroughWall: %d\n", index, glowThroughWall);
        printf("Player[%d]____localOrigin_prev: %s\n", index, localOrigin_prev.toString().c_str());
        printf("Player[%d]____localOrigin: %s\n", index, localOrigin.toString().c_str());
        printf("Player[%d]____localOrigin_predicted: %s\n", index, localOrigin_predicted.toString().c_str());
        printf("Player[%d]____local: %d\n", index, local);
        printf("Player[%d]____friendly: %d\n", index, friendly);
        printf("Player[%d]____enemy: %d\n", index, enemy);
        printf("Player[%d]____lastTimeAimedAt: %d\n", index, lastTimeAimedAt);
        printf("Player[%d]____lastTimeAimedAtPrev: %d\n", index, lastTimeAimedAtPrev);
        printf("Player[%d]____aimedAt: %d\n", index, aimedAt);
        printf("Player[%d]____lastTimeVisible: %d\n", index, lastTimeVisible);
        printf("Player[%d]____lastTimeVisiblePrev: %d\n", index, lastTimeVisiblePrev);
        printf("Player[%d]____visible: %d\n", index, visible);
        printf("Player[%d]____distanceToLocalPlayer: %.2f\n", index, distanceToLocalPlayer);
        printf("Player[%d]____distance2DToLocalPlayer: %.2f\n", index, distance2DToLocalPlayer);
        printf("Player[%d]____aimbotLocked: %d\n", index, aimbotLocked);
        printf("Player[%d]____aimbotDesiredAngles: %s\n", index, aimbotDesiredAngles.toString().c_str());
        printf("Player[%d]____aimbotDesiredAnglesIncrement: %s\n", index, aimbotDesiredAnglesIncrement.toString().c_str());
        printf("Player[%d]____aimbotDesiredAnglesSmoothed: %s\n", index, aimbotDesiredAnglesSmoothed.toString().c_str());
        printf("Player[%d]____aimbotDesiredAnglesSmoothedNoRecoil: %s\n", index, aimbotDesiredAnglesSmoothedNoRecoil.toString().c_str());
        printf("Player[%d]____aimbotScore: %.2f\n", index, aimbotScore);
        printf("____________________________________________________________________________\n");
    }
};
