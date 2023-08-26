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
    std::byte glowModeBodyStyle;
    std::byte glowModeBorderStyle;
    std::byte glowModeBorderWidth;
    ByteVector3D glowMode;
    int lastTimeVisible;
    int lastTimeVisiblePrev;
    bool visible;
    bool localPlayer;
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

    void update() {
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) return;
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
        glowMode = mem::ReadByteVector3D(base + off::GLOW_MODE_BODY_STYLE);
        lastTimeVisiblePrev = lastTimeVisible;
        lastTimeVisible = mem::ReadInt(base + off::LAST_VISIBLE_TIME);
        visible = lastTimeVisible > 0 && lastTimeVisiblePrev > 0 && lastTimeVisiblePrev < lastTimeVisible;
        if (myLocalPlayer->isValid()) {//only calculate if localPlayer is valid
            localPlayer = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            if (visible) { //only calculate for visible targets
                lastTimeAimedAtPrev = lastTimeAimedAt;
                lastTimeAimedAt = mem::ReadInt(base + off::LAST_TIME_AIMED_AT);
                aimedAt = lastTimeAimedAt > 0 && lastTimeAimedAtPrev > 0 && lastTimeAimedAtPrev < lastTimeAimedAt;
                distanceToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            }
            else {
                //reset values
                lastTimeAimedAtPrev = 0;
                lastTimeAimedAt = 0;
                aimedAt = false;
                distanceToLocalPlayer = 999999999;
            }
        }
        else {
            //reset values
            localPlayer = false;
            friendly = false;
            enemy = false;
            lastTimeAimedAtPrev = 0;
            lastTimeAimedAt = 0;
            aimedAt = false;
            distanceToLocalPlayer = 999999999;
        }
    }

    bool isValid() {
        return base != 0;
    }

    bool isCombatReady() {
        if (base == 0)return false;
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
};