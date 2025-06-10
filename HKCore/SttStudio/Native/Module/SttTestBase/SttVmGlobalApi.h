#pragma once

#include "../../../Module/BaseClass/ComplexNumber.h"
#include "../../../Module/API/MathApi.h"

//nValue=0 or 1
void stt_SetBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos, long nValue);
void stt_SetBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex, long nValue);
void stt_ChangeBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos);
void stt_ChangeBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex);

long stt_GetBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos);
long stt_GetBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex);

