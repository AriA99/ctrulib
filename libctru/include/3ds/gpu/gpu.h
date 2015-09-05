#pragma once

#include "registers.h"
#include "enums.h"

//GPUCMD
#define GPUCMD_HEADER(incremental, mask, reg) (((incremental)<<31)|(((mask)&0xF)<<16)|((reg)&0x3FF))

extern u32* gpuCmdBuf;
extern u32 gpuCmdBufSize;
extern u32 gpuCmdBufOffset;

void GPUCMD_SetBuffer(u32* adr, u32 size, u32 offset);
void GPUCMD_SetBufferOffset(u32 offset);
void GPUCMD_GetBuffer(u32** adr, u32* size, u32* offset);
void GPUCMD_AddRawCommands(u32* cmd, u32 size);
void GPUCMD_Run(u32* gxbuf);
void GPUCMD_FlushAndRun(u32* gxbuf);
void GPUCMD_Add(u32 header, u32* param, u32 paramlength);
void GPUCMD_Finalize();

u32 f32tof24(float f);
u32 computeInvValue(u32 val);

#define GPUCMD_AddSingleParam(header, param) GPUCMD_Add((header), (u32[]){(u32)(param)}, 1)

#define GPUCMD_AddMaskedWrite(reg, mask, val) GPUCMD_AddSingleParam(GPUCMD_HEADER(0, (mask), (reg)), (val))
#define GPUCMD_AddWrite(reg, val) GPUCMD_AddMaskedWrite((reg), 0xF, (val))
#define GPUCMD_AddMaskedWrites(reg, mask, vals, num) GPUCMD_Add(GPUCMD_HEADER(0, (mask), (reg)), (vals), (num))
#define GPUCMD_AddWrites(reg, vals, num) GPUCMD_AddMaskedWrites((reg), 0xF, (vals), (num))
#define GPUCMD_AddMaskedIncrementalWrites(reg, mask, vals, num) GPUCMD_Add(GPUCMD_HEADER(1, (mask), (reg)), (vals), (num))
#define GPUCMD_AddIncrementalWrites(reg, vals, num) GPUCMD_AddMaskedIncrementalWrites((reg), 0xF, (vals), (num))
