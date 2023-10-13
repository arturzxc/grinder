#pragma once
struct LocalPlayer {
    long base;
    bool dead;
    bool knocked;
    int teamNumber;
    bool inAttack;
    bool inZoom;
    bool inJump;
    FloatVector3D localOrigin;
    FloatVector2D viewAngles;
    FloatVector2D punchAngles;
    FloatVector2D punchAnglesPrev;
    FloatVector2D punchAnglesDiff;
    int weaponIndex;

    void reset() {
        base = 0;
    }

    void readFromMemory() {
        base = mem::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);
        if (base == 0) return;
        dead = mem::Read<short>(base + OFF_LIFE_STATE) > 0;
        knocked = mem::Read<short>(base + OFF_BLEEDOUT_STATE) > 0;
        inZoom = mem::Read<short>(base + OFF_ZOOMING) > 0;
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER);
        inAttack = mem::Read<bool>(OFF_REGION + OFF_IN_ATTACK) > 0;
        inJump = mem::Read<bool>(OFF_REGION + OFF_IN_JUMP) > 0;
        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN);
        viewAngles = mem::Read<FloatVector2D>(base + OFF_VIEW_ANGLES);
        punchAngles = mem::Read<FloatVector2D>(base + OFF_PUNCH_ANGLES);
        punchAnglesDiff = punchAnglesPrev.subtract(punchAngles);
        punchAnglesPrev = punchAngles;
        if (!dead && !knocked) {
            long weaponHandle = mem::Read<long>(base + OFF_WEAPON_HANDLE);
            long weaponHandleMasked = weaponHandle & 0xffff;
            long weaponEntity = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (weaponHandleMasked << 5));
            weaponIndex = mem::Read<int>(weaponEntity + OFF_WEAPON_INDEX);
        }
    }

    bool isValid() {
        return base != 0;
    }

    bool isCombatReady() {
        if (base == 0) return false;
        if (dead) return false;
        if (knocked) return false;
        return true;
    }

    void lookAt(FloatVector2D angles) {
        mem::Write<FloatVector2D>(base + OFF_VIEW_ANGLES, angles.clamp());
    }
};