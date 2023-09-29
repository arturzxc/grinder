//GameVersion=v3.0.44.22
#pragma once
// core    
long OFF_REGION = 0x140000000;                      //[Static]->Region
long OFF_LEVEL = 0x16f71e0;                         //[Miscellaneous]->LevelName
long OFF_LOCAL_PLAYER = 0x21d3758;                  //[Miscellaneous]->LocalPlayer
long OFF_ENTITY_LIST = 0x1e23418;                   //[Miscellaneous]->cl_entitylist
long OFF_IN_ZOOM = 0x074229e8;                      //[Buttons]->in_zoom   
// player
long OFF_LOCAL_ORIGIN = 0x0188;                     //[DataMap.CBaseViewModel]->m_localOrigin
long OFF_TEAM_NUMBER = 0x037c;                      //[RecvTable.DT_BaseEntity]->m_iTeamNum
long OFF_NAME = 0x04b9;                             //[RecvTable.DT_BaseEntity]->m_iName
long OFF_SIGNIFIER_NAME = 0x04b0;                   //[RecvTable.DT_BaseEntity]->m_iSignifierName
long OFF_LIFE_STATE = 0x06c8;                       //[RecvTable.DT_Player]->m_lifeState
long OFF_BLEEDOUT_STATE = 0x26a0;                   //[RecvTable.DT_Player]->m_bleedoutState  
long OFF_LAST_AIMEDAT_TIME = 0x19ad + 0x3 + 0x8;    //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x8
//weapon 
long OFF_WEAPON_HANDLE = 0x1954;                    //[RecvTable.DT_Player]->m_latestPrimaryWeapons
long OFF_WEAPON_INDEX = 0x1798;                     //[RecvTable.DT_WeaponX]->m_weaponNameIndex
//glow
long OFF_GLOW_ENABLE = 0x294;                       //[DT_HighlightSettings].?
long OFF_GLOW_THROUGH_WALL = 0x278;                 //[DT_HighlightSettings].?
long OFF_GLOW_HIGHLIGHT_ID = 0x298;                 //[DT_HighlightSettings].m_highlightServerActiveStates    
long OFF_GLOW_HIGHLIGHTS = 0xb5f9620;               //[?]->?
//items
long OFF_ITEM_INDEX = 0x05c0;                       //[RecvTable.DT_PropSurvival]->m_scriptNameIndex
long OFF_CUSTOM_SCRIPT = 0x1578;                    //[RecvTable.DT_PropSurvival]->m_customScriptInt

