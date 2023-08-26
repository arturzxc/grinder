#pragma once
namespace off {
    // core
    const long REGION = 0x140000000;                                                        //[Mine]->Region
    const long LEVEL = 0x16eed90;                                                           //[Miscellaneous]->LevelName
    const long LOCAL_PLAYER = 0x22245c8;                                                    //[Miscellaneous]->AVC_GameMovement+0x8
    const long ENTITY_LIST = 0x1e74448;                                                     //[Miscellaneous]->cl_entitylist
    // player
    const long LOCAL_ORIGIN = 0x0188;                                                       //[DataMap.CBaseViewModel]->m_localOrigin
    const long TEAM_NUMBER = 0x0480;                                                        //[RecvTable.DT_BaseEntity]->m_iTeamNum
    const long NAME = 0x05c1;                                                               //[RecvTable.DT_BaseEntity]->m_iName
    const long LIFE_STATE = 0x07d0;                                                         //[RecvTable.DT_Player]->m_lifeState
    const long VEC_PUNCH_WEAPON_ANGLE = 0x24e8;                                             //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
    const long VIEW_ANGLES = 0x25e4 - 0x14;                                                 //[DataMap.C_Player]->m_ammoPoolCapacity - 0x14
    const long BLEEDOUT_STATE = 0x2790;                                                     //[RecvTable.DT_Player]->m_bleedoutState
    const long ZOOMING = 0x1c81;                                                            //[RecvTable.DT_Player]->m_bZooming
    const long LAST_VISIBLE_TIME = 0x1aa0;                                                  //[Miscellaneous]->CPlayer!lastVisibleTime
    const long CURRENT_SHIELDS = 0x01a0;                                                    //[RecvTable.DT_BaseEntity]->m_shieldHealth
    const long LAST_TIME_AIMED_AT = 0x1a9d + 0x3 + 0x8;                                     //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 +0x8
    //glow
    const long GLOW_ENABLE = 0x03F8;                                                        //[RecvTable.DT_HighlightSettings]->m_highlightServerContextID + 0x8
    const long GLOW_THROUGH_WALL = 0x0400;                                                  //[RecvTable.DT_HighlightSettings]->m_highlightServerContextID + 0x10
    const long GLOW_COLOR = 0x200;                                                          //[Miscellaneous]->glow_color
    const long GLOW_MODE_BODY_STYLE = 0x2c4 + 0x30;                                         //[Miscellaneous]->glow_mode
    const long GLOW_MODE_BORDER_STYLE = GLOW_MODE_BODY_STYLE + sizeof(std::byte);
    const long GLOW_MODE_BORDER_WIDTH = GLOW_MODE_BORDER_STYLE + sizeof(std::byte);
    //weapon
    const long WEAPON_HANDLE = 0x1a44;                                                      //[RecvTable.DT_Player]->m_latestPrimaryWeapons
    const long WEAPON_INDEX = 0x1888;                                                       //[RecvTable.DT_WeaponX]->m_weaponNameIndex
    const long WEAPON_SEMIAUTO = 0x1a9d + 0x3 + 0x018c;                                     //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x018c
    // buttons
    const long IN_ATTACK = 0x07472f98;                                                      //[Buttons]->in_attack
    const long IN_ZOOM = 0x07473138;                                                        //[Buttons]->in_zoom
}
