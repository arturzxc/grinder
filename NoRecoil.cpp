#pragma once
struct NoRecoil {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;

    FloatVector2D previous_weaponPunchAngles;

    NoRecoil(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
    }

    void controlWeapon(int counter) {
        if (!cl->FEATURE_NORECOIL_ON)return;
        if (!localPlayer->isCombatReady()) return;
        if (!localPlayer->inAttack) return;
        FloatVector2D punchAnglesDiff = localPlayer->punchAnglesDiff;
        if (punchAnglesDiff.isZeroVector()) return;
        int pitch = (punchAnglesDiff.x > 0)
            ? roundHalfEven(punchAnglesDiff.x * cl->NORECOIL_PITCH_REDUCTION)
            : 0;
        int yaw = roundHalfEven(-punchAnglesDiff.y * cl->NORECOIL_YAW_REDUCTION);
        display->moveMouseRelative(pitch, yaw);
    }

    int roundHalfEven(float x) {
        return (x >= 0.0)
            ? static_cast<int>(std::round(x))
            : static_cast<int>(std::round(-x)) * -1;
    }
};
