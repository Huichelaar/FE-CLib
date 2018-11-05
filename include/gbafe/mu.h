#ifndef GBAFE_MU_H
#define GBAFE_MU_H

// mu.c

#include <stdint.h>

#include "proc.h"
#include "unit.h"
#include "ap.h"

typedef struct MoveUnitProc MoveUnitProc;
typedef struct MoveUnitProc MoveUnitState;

typedef struct MoveUnitExtraData MoveUnitExtraData;

struct MoveUnitExtraData {
	u8 index;
	
	u8 objPaletteIndex;
	u16 objTileIndex;
	
	u8 commandCount;
	u8 commands[63];
	
	void* _u;
	struct MoveUnitProc* pMoveunit;
};

struct MoveUnitProc {
	PROC_FIELDS
	
	// should be padded to 0x2C
	
	struct Unit* pUnit;
	AnimHandle* pAnimHandle;
	MoveUnitExtraData* pExtraData;
	void* pVRAM;
	
	u8 spriteFrameIndex;
	u8 _3D;
	u8 cameraFollow;
	u8 state;
	u8 _40; // Related to Movement Speed? (0 initially) (80797D4 sets this to 1) (80797DC sets this to 0)
	u8 classIndex; // Class Index / Map Sprite Entry (The fact that it is used as class index too annoys me)
	u8 currentAnimIndex; // Current Direction byte? (0xB initially) (Stored in routine at 08078694)
	u8 _43; // Something? (Initialized at 0xFE/-2 if another MOVEUNIT instance exists, 0 otherwise. Incremented in routine at 8078D6C)
	u8 _44; // Related to Movement Speed? (0 initially) (8079B10 sets this to 1)
	// u8 _45; // should be padded to 0x46
	u16 objectPriorityBits; // OAM priority mask (0x800 initially)
	u16 _48; // When Moving, Incremented by Movement Speed, added to positions and then finally cleared. State 3 (3F = 3) Decrements it and sets State to 2 when reaches 0
	u16 _4A; // If bit 7 is set, it will not play any sound/create any 6C_89A2938 while moving the unit
	
	short xPosition; // x*256
	short yPosition; // y*256
	short xOffset; // added to x? (0 initially)
	short yOffset; // added to y? (0 initially)
	
	ProcState* pBlendTimerProc; // blend timer thing 6C pointer
};

#pragma long_calls

void MU_Init(void); //! FE8U = (0x0807840C+1)
struct MoveUnitProc* MU_CreateExt(struct Unit* unit, int mms, int palId); //! FE8U = (0x08078428+1)
struct MoveUnitProc* MU_Create(struct Unit* unit); //! FE8U = (0x08078464+1)
void MU_EnableAttractCamera(struct MoveUnitProc*); //! FE8U = (0x080784E4+1)
void MU_DisableAttractCamera(struct MoveUnitProc*); //! FE8U = (0x080784EC+1)
struct MoveUnitProc* MU_CreateForUI(struct Unit* unit); //! FE8U = (0x080784F4+1)
struct MoveUnitProc* MU_CreateInternal(int x, int y, int mms, int objBase, int palId); //! FE8U = (0x08078540+1)
void MU_SetFacing(struct MoveUnitProc* moveunit, int direction); //! FE8U = (0x08078694+1)
void MU_SetDefaultFacing(struct MoveUnitProc* moveunit); //! FE8U = (0x080786BC+1)
void MU_SetDefaultFacing_Auto(); //! FE8U = (0x080786E8+1)
void MU_StartMoveScript_Auto(u8* moveManual); //! FE8U = (0x08078700+1)
int MU_Exists(); //! FE8U = (0x08078720+1)
int MU_IsAnyActive(); //! FE8U = (0x08078738+1)
void MU_StartMoveScript(struct MoveUnitProc* moveunit, u8* moveManual); //! FE8U = (0x08078790+1)
void MU_EndAll(); //! FE8U = (0x080790A4+1)
void MU_End(struct MoveUnitProc* moveunit); //! FE8U = (0x080790B4+1)
void MU_StartActionAnim(struct MoveUnitProc* moveunit); //! FE8U = 0x80798B1
void MU_Hide(struct MoveUnitProc* moveunit); //! FE8U = 0x80797D5
void MU_Show(struct MoveUnitProc* moveunit); //! FE8U = 0x80797DD
void MU_SetDisplayPosition(struct MoveUnitProc* moveunit, int x, int y); //! FE8U = (0x080797E4+1)

#pragma long_calls_off

#endif // GBAFE_MU_H
