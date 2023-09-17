#pragma once
namespace off {
    // core    
    const long REGION = 0x140000000;                                                        //[Static]->Region
    const long LEVEL = 0x16efe10;                                                           //[Miscellaneous]->LevelName
    const long LOCAL_PLAYER = 0x2225648;                                                    //[Miscellaneous]->LocalPlayer
    const long ENTITY_LIST = 0x1e754c8;                                                     //[Miscellaneous]->cl_entitylist
    // player
    const long LOCAL_ORIGIN = 0x0188;                                                       //[DataMap.CBaseViewModel]->m_localOrigin
    const long TEAM_NUMBER = 0x0480;                                                        //[RecvTable.DT_BaseEntity]->m_iTeamNum
    const long NAME = 0x05c1;                                                               //[RecvTable.DT_BaseEntity]->m_iName
    const long SIGNIFIER_NAME = 0x05b8;                                                     //[RecvTable.DT_BaseEntity]->m_iSignifierName
    const long CURRENT_SHIELDS = 0x01a0;                                                    //[RecvTable.DT_BaseEntity]->m_shieldHealth
    const long LIFE_STATE = 0x07d0;                                                         //[RecvTable.DT_Player]->m_lifeState
    const long PUNCH_ANGLES = 0x24e8;                                                       //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
    const long VIEW_ANGLES = 0x25e4 - 0x14;                                                 //[DataMap.C_Player]->m_ammoPoolCapacity - 0x14
    const long BLEEDOUT_STATE = 0x2790;                                                     //[RecvTable.DT_Player]->m_bleedoutState
    const long ZOOMING = 0x1c81;                                                            //[RecvTable.DT_Player]->m_bZooming        
    const long LAST_VISIBLE_TIME = 0x1a9d + 0x3;                                            //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3
    const long LAST_AIMEDAT_TIME = 0x1a9d + 0x3 + 0x8;                                      //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 +0x8
    //glow
    const long GLOW_ENABLE = 0x03f0 + 0x8;                                                  //[RecvTable.DT_HighlightSettings]->m_highlightServerContextID + 0x8
    const long GLOW_THROUGH_WALL = 0x03f0 + 0x10;                                           //[RecvTable.DT_HighlightSettings]->m_highlightServerContextID + 0x10
    const long GLOW_COLOR = 0x200;                                                          //[?]->?
    const long GLOW_MODE = 0x2c4 + 0x30;                                                    //[?]->?
    //weapon
    const long WEAPON_HANDLE = 0x1a44;                                                      //[RecvTable.DT_Player]->m_latestPrimaryWeapons
    const long WEAPON_INDEX = 0x1888;                                                       //[RecvTable.DT_WeaponX]->m_weaponNameIndex
    const long WEAPON_SEMIAUTO = 0x1a9d + 0x3 + 0x018c;                                     //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x018c
    // buttons
    const long IN_ATTACK = 0x07473fb8;                                                      //[Buttons]->in_attack
    const long IN_ZOOM = 0x07474138;                                                        //[Buttons]->in_zoom



    //prop survival
    const long m_ModelName = 0x0030; //int

    const long m_scriptNameIndex = 0x06c8; //int
    const long m_grade = 0x0490; //int
    const long m_pressUsePrompt=0x0758;//string
}
