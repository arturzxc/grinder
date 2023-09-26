// #pragma once
// struct AimBot2 {
//     const float SMOOTH = 25;                                //The lower the stronger the aimbot. Suggested 100
//     const float FOV = 200;                                   //FOV is dynamic based on distance. Suggested 5
//     const float MIN_TARGET_ACQUIZITION_TIME = 200;          //Avg player is 300-500ms, Pro players are 200ms

//     std::vector<Player*>* myEnemies;
//     Player* target = 0;
//     long long timeTargetLost = 0;

//     bool update() {
//         //are we dealing with dummies or players
//         myEnemies = (level->trainingArea) ? dummies : players;

//         if (!localPlayer->isCombatReady()) {
//             printf("LocalPlayer not ready %lld\n", util::currentEpochMillis());
//             loseTarget();
//             return false;
//         }

//         if (!localPlayer->inZoom && !localPlayer->inAttack) {
//             printf("LocalPlayer not zooming/attacking %lld\n", util::currentEpochMillis());
//             loseTarget();
//             return false;
//         }

//         //get new target if required
//         if (target == 0 || !target->visible || !target->isCombatReady())
//             if (timeLockExpired())
//                 target = findNewTarget();


//         if (target == 0) {//nothing to shoot
//             loseTarget();
//             return false;
//         }


//         //pitch increment calculation
//         float  pitchIncrement = 0;
//         {
//             float pitchDeadzone = std::max(0.1f, 1000 / target->distance3DToLocalPlayer);
//             float deltaPitch = target->deltaPitch;
//             if (deltaPitch > pitchDeadzone && deltaPitch < FOV) {//respect the deadzone and max fov
//                 float pitchRotationDirection = calcPitchRotationDirection(localPlayer->viewAngles.x, target->desiredViewAngles.x);
//                 pitchIncrement = (deltaPitch * pitchRotationDirection) / SMOOTH;

//             }
//         }

//         //yaw increment calculation
//         float yawIncrement = 0;
//         {
//             float yawDeadzone = std::max(0.1f, 400 / target->distance3DToLocalPlayer);
//             float deltaYaw = target->deltaYaw;
//             if (deltaYaw > yawDeadzone && deltaYaw < FOV) {//respect the deadzone and max fov
//                 int yawRotationDirection = calcYawRotationDirection(localPlayer->viewAngles.y, target->desiredViewAngles.y);
//                 yawIncrement = (deltaYaw * yawRotationDirection) / SMOOTH;

//             }
//         }

//         //add increments to the current angles and then clamp clump
//         FloatVector2D incrementVector = FloatVector2D(pitchIncrement, yawIncrement);
//         if (incrementVector.isZeroVector()) return false;

//         target->targetLocked = true;

//         FloatVector2D newViewAngles = localPlayer->viewAngles.add(incrementVector);
//         mem::WriteFloatVector2D(localPlayer->base + off::VIEW_ANGLES, newViewAngles.clamp());

//         return true;
//     }

//     Player* findNewTarget() {
//         Player* bestTargetSoFar = 0;
//         float bestScoreSoFar = 999999999; //lowest is best
//         for (int i = 0; i < myEnemies->size(); i++) {
//             Player* p = myEnemies->at(i);
//             //checks
//             if (!p->isCombatReady()) continue;
//             if (!p->enemy) continue;
//             if (!p->visible) continue;
//             if (p->distance3DToLocalPlayer > util::metersToGameUnits(30))continue;
//             //calculate score
//             float deltaPitch = p->deltaPitch;
//             float deltaYaw = p->deltaYaw;
//             float myScore = deltaPitch + deltaYaw;
//             if (myScore < bestScoreSoFar) {
//                 bestTargetSoFar = p;
//                 bestScoreSoFar = myScore;
//             }
//         }
//         return bestTargetSoFar;
//     }

//     int calcYawRotationDirection(int currentYaw, int targetYaw) {
//         int clockwiseDistance = (targetYaw - currentYaw + 360) % 360;
//         int counterclockwiseDistance = (currentYaw - targetYaw + 360) % 360;
//         if (clockwiseDistance <= counterclockwiseDistance)
//             return 1;  // Clockwise rotation                
//         return -1; // Counterclockwise rotation        
//     }

//     int calcPitchRotationDirection(int currentPitch, int targetPitch) {
//         int clockwiseDistance = (targetPitch - currentPitch + 180) % 180;
//         int counterclockwiseDistance = (currentPitch - targetPitch + 180) % 180;
//         if (clockwiseDistance <= counterclockwiseDistance)
//             return 1;  // upwards    
//         return -1; // downwards
//     }


//     Player* getLockedPlayer() {
//         return target;
//     }

//     void loseTarget() {
//         if (target == 0) return; //we don't have anything to lose
//         printf("TARGET LOST %lld\n", util::currentEpochMillis());
//         target = 0;
//         timeTargetLost = util::currentEpochMillis();
//     }

//     bool timeLockExpired() {
//         long long timeDiff = util::currentEpochMillis() - timeTargetLost;
//         bool canAcquireTarget = timeDiff > MIN_TARGET_ACQUIZITION_TIME;
//         if (!canAcquireTarget) {
//             long long timeToWait = MIN_TARGET_ACQUIZITION_TIME - timeDiff;
//             printf("Too early to acquire target. Still need to wait: %lld \n", timeToWait);
//             return false;
//         }

//         if (canAcquireTarget) {
//             printf("!!! LOCAL PLAYER READY TO ACQUIRE TARGET!!! %lld\n", util::currentEpochMillis());
//         }

//         return canAcquireTarget;
//     }

// };
