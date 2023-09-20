#pragma once
namespace off {
    // core    
    const long REGION = 0x140000000;                                                        //[Static]->Region
    const long LEVEL = 0x16f71e0;                                                           //[Miscellaneous]->LevelName
    const long LOCAL_PLAYER = 0x21d3758;                                                    //[Miscellaneous]->LocalPlayer
    const long ENTITY_LIST = 0x1e23418;                                                     //[Miscellaneous]->cl_entitylist
    // buttons
    const long IN_ATTACK = 0x07422868;                                                      //[Buttons]->in_attack
    const long IN_ZOOM = 0x074229e8;                                                        //[Buttons]->in_zoom
    // player
    const long LOCAL_ORIGIN = 0x0188;                                                       //[DataMap.CBaseViewModel]->m_localOrigin
    const long TEAM_NUMBER = 0x037c;                                                        //[RecvTable.DT_BaseEntity]->m_iTeamNum
    const long NAME = 0x04b9;                                                               //[RecvTable.DT_BaseEntity]->m_iName
    const long SIGNIFIER_NAME = 0x04b0;                                                     //[RecvTable.DT_BaseEntity]->m_iSignifierName
    const long CURRENT_SHIELDS = 0x01a0;                                                    //[RecvTable.DT_BaseEntity]->m_shieldHealth
    const long LIFE_STATE = 0x06c8;                                                         //[RecvTable.DT_Player]->m_lifeState
    const long PUNCH_ANGLES = 0x23f8;                                                       //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
    const long VIEW_ANGLES = 0x24f4 - 0x14;                                                 //[DataMap.C_Player]->m_ammoPoolCapacity - 0x14
    const long BLEEDOUT_STATE = 0x26a0;                                                     //[RecvTable.DT_Player]->m_bleedoutState
    const long ZOOMING = 0x1b91;                                                            //[RecvTable.DT_Player]->m_bZooming        
    const long LAST_VISIBLE_TIME = 0x19ad + 0x3;                                            //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3
    const long LAST_AIMEDAT_TIME = 0x19ad + 0x3 + 0x8;                                      //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 +0x8
    //glow
    const long GLOW_ENABLE = 0x294;                                                         //[?]->?
    const long GLOW_THROUGH_WALL = 0x278;                                                   //[?]->?
    const long GLOW_MODE = 0x29c;                                                           //[?]->?
    const long GLOW_COLOR = 0x200;                                                          //[?]->?    
    //weapon
    const long WEAPON_HANDLE = 0x1954;                                                      //[RecvTable.DT_Player]->m_latestPrimaryWeapons
    const long WEAPON_INDEX = 0x1798;                                                       //[RecvTable.DT_WeaponX]->m_weaponNameIndex
    const long WEAPON_SEMIAUTO = 0x19ad + 0x3 + 0x018c;                                     //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x018c
    //prop survival
    const long ITEM_INDEX = 0x05c0;                                                         //[RecvTable.DT_PropSurvival]->m_scriptNameIndex
}
