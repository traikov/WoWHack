#pragma once

#define obj_Type                       0x14
#define obj_Pos_X                      0x79C
#define obj_Pos_Y                      0x798
#define obj_Pos_Z                      0x7A0
#define obj_Rotation                   0x7A8
#define obj_Guid                       0x30
#define obj_UnitFields                 0x8

#define gObj_Pos_X                     0xEC
#define gObj_Pos_Y                     0xE8
#define gObj_Pos_Z                     0xF0

#define unit_Level                     0x36 * 4
#define unit_Health                    0x18 * 4
#define unit_Energy                    0x19 * 4,
#define unit_MaxHealth                 0x20 * 4
#define unit_SummonedBy                0xE * 4
#define unit_MaxEnergy                 0x21 * 4

#define Player_TrackCreatures          0x3FE * 4  /* 0xFF8 */
#define Player_TrackResources          0x3FF * 4  /* 0xFFC */

#define _MapID                         0x00D38AC4

#define game_WallClimb                 0x0075B693
#define game_SuperWallClimb            0x858
#define game_WaterWalking              0x75E439
#define game_InfiniteJump              0x988433

#define corpse_Pos_X                   0x00BD0A5C
#define corpse_Pos_Y                   0x00BD0A58
#define corpse_Pos_Z                   0x00BD0A60

#define client_StaticClientConnection  0x00C79CE0
#define client_ObjectManagerOffset     0x2ED0
#define client_FirstObjectOffset       0xAC
#define client_LocalGuidOffset         0xC0
#define client_NextObjectOffset        0x3C
#define client_LocalPlayerGUID         0xBD07A8
#define client_MouseOverGUID           0x00BD07A0
#define client_LocalTargetGUID         0x00BD07B0

#define player_STATIC_PLAYER           0x00CD87A8
#define player_PBaseOffset1            0x34
#define player_PBaseOffset2            0x24


#define CGPlayer_C__ClickToMove        0x00727400     
#define CTM_Activate_Pointer           0xBD08F4     
#define CTM_Activate_Offset            0x30                
#define CTM_Base                       0x00CA11D8                  
#define CTM_X                          0x90                          
#define CTM_Y                          0x8C                               
#define CTM_Z                          0x94                            
#define CTM_TurnSpeed                  0x4                      
#define CTM_Distance                   0xC                       
#define CTM_Action                     0x1C                        
#define CTM_GUID                       0x20     

#define Descriptors					     0x8
#define FrameScript_ExecuteAddress	 	 0x00819210
#define GetUnitFromName                  0x0060C1F0
#define CGUnit_C__UpdateDisplayInfo      0x0073e410
#define CGUnit_C__OnMountDisplayChanged  0x00740450
#define DisplayID                        0x43 * 4
#define OriginalDisplayID                0x44 * 4
#define MountDisplayID				     0x45 * 4
#define ObjectScale                      0x9C