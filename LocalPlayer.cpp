#pragma once
struct LocalPlayer {
    long base;
    bool dead;
    bool knocked;
    int teamNumber;
    bool inAttack;
    bool inZoom;
    long highlightSettingsPtr;
    FloatVector3D localOrigin;
    FloatVector2D viewAngles;
    FloatVector2D punchAngles;
    FloatVector2D punchAnglesPrev;
    FloatVector2D punchAnglesDiff;
    int weaponIndex;
    bool weaponDiscarded;

    void readFromMemory() {
        base = mem::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER, "LocalPlayer base");
        if (!mem::Valid(base))return;
        dead = mem::Read<short>(base + OFF_LIFE_STATE, "LocalPlayer base") > 0;
        knocked = mem::Read<short>(base + OFF_BLEEDOUT_STATE, "LocalPlayer base") > 0;
        inZoom = mem::Read<short>(base + OFF_ZOOMING, "LocalPlayer inZoom") > 0;
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER, "LocalPlayer teamNumber");
        inAttack = mem::Read<bool>(OFF_REGION + OFF_IN_ATTACK, "LocalPlayer inAttack") > 0;
        highlightSettingsPtr = mem::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS, "LocalPlayer HiglightsSettingPtr");
        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN, "LocalPlayer localOrigin");
        viewAngles = mem::Read<FloatVector2D>(base + OFF_VIEW_ANGLES, "LocalPlayer viewAngles");
        punchAngles = mem::Read<FloatVector2D>(base + OFF_PUNCH_ANGLES, "LocalPlayer punchAngles");
        punchAnglesDiff = punchAnglesPrev.subtract(punchAngles);
        punchAnglesPrev = punchAngles;
        if (!dead && !knocked) {
            long weaponHandle = mem::Read<long>(base + OFF_WEAPON_HANDLE, "LocalPlayer weaponHandle");
            long weaponHandleMasked = weaponHandle & 0xffff;
            long weaponEntity = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (weaponHandleMasked << 5), "LocalPlayer weaponEntity");
            weaponIndex = mem::Read<int>(weaponEntity + OFF_WEAPON_INDEX, "LocalPlayer weaponIndex");
            weaponDiscarded = mem::Read<int>(weaponEntity + OFF_WEAPON_DISCARDED, "LocalPlayer weaponDiscarded") == 1;
        }
    }

    bool isValid() {
        return mem::Valid(base);
    }

    bool isCombatReady() {
        if (base == 0) return false;
        if (dead) return false;
        if (knocked) return false;
        return true;
    }

    void print() const {
        printf("________________________________________________________________________\n");
        printf("LocalPlayer____Base: %s\n", util::longToHexString(base).c_str());
        printf("LocalPlayer____Dead: %s\n", dead ? "true" : "false");
        printf("LocalPlayer____Knocked: %s\n", knocked ? "true" : "false");
        printf("LocalPlayer____Team Number: %d\n", teamNumber);
        printf("LocalPlayer____In Attack: %s\n", inAttack ? "true" : "false");
        printf("LocalPlayer____In Zoom: %s\n", inZoom ? "true" : "false");
        printf("LocalPlayer____Local Origin: %s\n", localOrigin.toString().c_str());
        printf("LocalPlayer____View Angles: %s\n", viewAngles.toString().c_str());
        printf("LocalPlayer____Punch Angles: %s\n", punchAngles.toString().c_str());
        printf("LocalPlayer____Punch Angles Prev: %s\n", punchAnglesPrev.toString().c_str());
        printf("LocalPlayer____Punch Angles Diff: %s\n", punchAnglesDiff.toString().c_str());
        printf("LocalPlayer____Weapon Index: %d\n", weaponIndex);
        printf("LocalPlayer____Weapon Discarded: %s\n", weaponDiscarded ? "true" : "false");
        printf("________________________________________________________________________\n");
    }
};