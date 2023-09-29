#pragma once
struct LocalPlayer {
    long base;
    bool dead;
    bool knocked;
    int teamNumber;
    bool inAttack;
    bool inZoom;
    FloatVector3D localOrigin;
    int weaponIndex;

    void reset() {
        base = 0;
    }

    void readMemory() {
        reset();
        base = mem::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);
        if (base == 0) { reset(); return; }
        dead = mem::Read<short>(base + OFF_LIFE_STATE) > 0;
        knocked = mem::Read<short>(base + OFF_BLEEDOUT_STATE) > 0;
        inZoom = mem::Read<short>(OFF_REGION + OFF_IN_ZOOM) > 0;
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER);
        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN);
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
        if (base == 0)return false;
        if (dead) return false;
        if (knocked) return false;
        return true;
    }
};