struct LocalPlayer {
    long base;
    bool dead;
    bool knocked;
    int teamNumber;
    bool inAttack;
    bool inZoom;
    FloatVector3D localOrigin;
    FloatVector2D viewAngles;
    FloatVector2D punchAngles;
    int weaponIndex;
    bool weaponSemiAuto;

    void update() {
        base = mem::ReadLong(off::REGION + off::LOCAL_PLAYER);
        if (base == 0) return;
        dead = mem::ReadShort(base + off::LIFE_STATE) > 0;
        knocked = mem::ReadShort(base + off::BLEEDOUT_STATE) > 0;
        inAttack = mem::ReadShort(off::REGION + off::IN_ATTACK) > 0;
        inZoom = mem::ReadShort(off::REGION + off::IN_ZOOM) > 0;
        teamNumber = mem::ReadInt(base + off::TEAM_NUMBER);
        localOrigin = mem::ReadFloatVector3D(base + off::LOCAL_ORIGIN);
        viewAngles = mem::ReadFloatVector2D(base + off::VIEW_ANGLES);
        punchAngles = mem::ReadFloatVector2D(base + off::VEC_PUNCH_WEAPON_ANGLE);
        //find weapon & weapon index
        long weaponHandle = mem::ReadLong(base + off::WEAPON_HANDLE);
        long weaponHandleMasked = weaponHandle & 0xffff;
        long weaponEntity = mem::ReadLong(off::REGION + off::ENTITY_LIST + (weaponHandleMasked << 5));
        weaponIndex = mem::ReadInt(weaponEntity + off::WEAPON_INDEX);
        weaponSemiAuto = mem::ReadShort(weaponEntity + off::WEAPON_SEMIAUTO) > 0;
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