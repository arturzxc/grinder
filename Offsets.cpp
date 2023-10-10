//GameVersion=v3.0.46.46
//LastUpdated=05/10/2023
//UpdatedBy:arturzxc
#pragma once
// core    
constexpr long OFF_REGION = 0x140000000;                      //[Static]->Region
constexpr long OFF_LEVEL = 0x16f51c0;                         //[Miscellaneous]->LevelName
constexpr long OFF_LOCAL_PLAYER = 0x21d1738;                  //[Miscellaneous]->LocalPlayer
constexpr long OFF_ENTITY_LIST = 0x1e213f8;                   //[Miscellaneous]->cl_entitylist
// player
constexpr long OFF_ZOOMING = 0x1b91;                          //[RecvTable.DT_Player]->m_bZooming
constexpr long OFF_LOCAL_ORIGIN = 0x0188;                     //[DataMap.CBaseViewModel]->m_localOrigin
constexpr long OFF_TEAM_NUMBER = 0x037c;                      //[RecvTable.DT_BaseEntity]->m_iTeamNum
constexpr long OFF_NAME = 0x04b9;                             //[RecvTable.DT_BaseEntity]->m_iName
constexpr long OFF_SIGNIFIER_NAME = 0x04b0;                   //[RecvTable.DT_BaseEntity]->m_iSignifierName
constexpr long OFF_LIFE_STATE = 0x06c8;                       //[RecvTable.DT_Player]->m_lifeState
constexpr long OFF_BLEEDOUT_STATE = 0x26a0;                   //[RecvTable.DT_Player]->m_bleedoutState  
constexpr long OFF_LAST_VISIBLE_TIME = 0x19ad + 0x3;          //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3
constexpr long OFF_LAST_AIMEDAT_TIME = 0x19ad + 0x3 + 0x8;    //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x8
constexpr long OFF_VIEW_ANGLES = 0x24f4 - 0x14;               //[DataMap.C_Player]-> m_ammoPoolCapacity - 0x14
constexpr long OFF_PUNCH_ANGLES = 0x23f8;                     //[?]->?
//weapon 
constexpr long OFF_WEAPON_HANDLE = 0x1954;                    //[RecvTable.DT_Player]->m_latestPrimaryWeapons
constexpr long OFF_WEAPON_INDEX = 0x1798;                     //[RecvTable.DT_WeaponX]->m_weaponNameIndex
//glow
constexpr long OFF_GLOW_ENABLE = 0x294;                       //[DT_HighlightSettings].?
constexpr long OFF_GLOW_THROUGH_WALL = 0x278;                 //[DT_HighlightSettings].?
constexpr long OFF_GLOW_FIX = 0x270;
constexpr long OFF_GLOW_HIGHLIGHT_ID = 0x298;                 //[DT_HighlightSettings].m_highlightServerActiveStates    
constexpr long OFF_GLOW_HIGHLIGHTS = 0xB5F7620;               //[?]->?


