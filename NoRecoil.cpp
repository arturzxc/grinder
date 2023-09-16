const float NR_PITCH_STRENGTH = 1;               // [0.00 - 1.00]
const float NR_YAW_STRENGTH = 1;                 // [0.00 - 1.00]
const int NR_ACTIVATION_KEY = XK_Shift_L;        // key code to activate
FloatVector2D previousPunchAngles;

void noRecoilUpdate(int counter, XDisplay* display, LocalPlayer* localPlayer) {
    if (counter % 2 != 0) return; //give mouse a chance to move
    //checks        
    if (!localPlayer->isCombatReady() || !display->keyDown(NR_ACTIVATION_KEY)) {
        previousPunchAngles = { 0,0 }; //reset so that the next time no recoil is starting from fresh punch angles
        return;
    }
    //do we have valid recoil to reduce?
    FloatVector2D punchAngles = localPlayer->punchAngles;
    if (punchAngles.isZeroVector()) {
        previousPunchAngles = { 0,0 };
        return;
    }
    //do we have valid view angles?
    FloatVector2D viewAngles = localPlayer->viewAngles;
    if (viewAngles.isZeroVector()) {
        previousPunchAngles = { 0,0 };
        return;
    }
    //find out the weapon kick amount for the current frame only. 
    FloatVector2D punchAnglesDelta = punchAngles.subtract(previousPunchAngles);
    punchAnglesDelta.x *= NR_PITCH_STRENGTH;
    punchAnglesDelta.y *= NR_YAW_STRENGTH;
    previousPunchAngles = punchAngles;
    //subtract the weapon kick from the current view angles.
    FloatVector2D newViewAngles = viewAngles.subtract(punchAnglesDelta);
    //finally write the new angles to the memory
    mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles.clamp());

}

