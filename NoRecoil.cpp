#pragma once
struct NoRecoil {
    const float NR_PITCH_STRENGTH = 1;        //suggested max is 0.5
    const float NR_YAW_STRENGTH = 1;          //suggested max is 0.5
    const float NR_PITCH_STRENGTH_RAND = std::min(1.0f, util::randomFloat(0.0f, 0.05f) + NR_PITCH_STRENGTH);    //add a bit of random
    const float NR_YAW_STRENGTH_RAND = std::min(1.0f, util::randomFloat(0.0f, 0.05) + NR_YAW_STRENGTH);         //add a bit of random

    LocalPlayer* localPlayer;
    FloatVector2D previousPunchAngles;

    NoRecoil(LocalPlayer* localPlayer) { this->localPlayer = localPlayer; }

    void update() {
        if (!localPlayer->isCombatReady()
            || !localPlayer->inZoom                                                     //no need for this in hip fire really so don't do it.
            || localPlayer->weaponSemiAuto) {
            previousPunchAngles = { 0,0 };                                              //reset the previous punch so that we start fresh next time we start shooting
            return;
        }

        FloatVector2D punchAngles = localPlayer->punchAngles;                           //find out the total amount the weapon has kicked back so far
        if (punchAngles.isZeroVector())return;                                          //invalid values so just return

        FloatVector2D viewAngles = localPlayer->viewAngles;                             //find out where we are looking at
        if (viewAngles.isZeroVector())return;                                           //invalid values so just return

        FloatVector2D punchAnglesDelta = punchAngles.subtract(previousPunchAngles);     //find out the weapon kick amount but only for the current frame

        punchAnglesDelta.x *= NR_PITCH_STRENGTH_RAND;                                   //apply pitch streangth modifier so we don't remove all of the recoil
        punchAnglesDelta.y *= NR_YAW_STRENGTH_RAND;                                     //apply yaw streangth modifier so we don't remove all of the recoil

        previousPunchAngles = punchAngles;                                              //save current kick angles for the next frame

        FloatVector2D newViewAngles = viewAngles.subtract(punchAnglesDelta).clamp();    //subtract the weapon kick from the current view angles. Make sure we are witin valid values.

        mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles);   //finally write the new angles to the memory
    }
};
