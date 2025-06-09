#include "stdafx.h"
#include "SttVmGlobalApi.h"

void stt_SetBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos, long nValue)
{
	ASSERT (0 <= nBitPos && nBitPos <= 7);

	BYTE byteShift = 1 << nBitPos;

	if (nValue == 1)
	{
		pBinaryBuf[nBytePos] = pBinaryBuf[nBytePos]  | byteShift;
	}
	else
	{
		pBinaryBuf[nBytePos] = pBinaryBuf[nBytePos]  & (~byteShift);
	}
}

void stt_SetBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex, long nValue)
{
	long nBytePos = nBinaryIndex / 8;
	long nBitPos = nBinaryIndex % 8;
	stt_SetBinaryBitVal(pBinaryBuf, nBytePos, nBitPos, nValue);
}

void stt_ChangeBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos)
{
	long nValue = stt_GetBinaryBitVal(pBinaryBuf, nBytePos, nBitPos);

	if (nValue == 0)
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}

	stt_SetBinaryBitVal(pBinaryBuf, nBytePos, nBitPos, nValue);
}

void stt_ChangeBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex)
{
	long nBytePos = nBinaryIndex / 8;
	long nBitPos = nBinaryIndex % 8;
	stt_ChangeBinaryBitVal(pBinaryBuf, nBytePos, nBitPos);
}

long stt_GetBinaryBitVal(BYTE *pBinaryBuf, long nBytePos, long nBitPos)
{
	ASSERT (0 <= nBitPos && nBitPos <= 7);

	BYTE byteValue = (pBinaryBuf[nBytePos] >> nBitPos) & 0x01;

	return byteValue;
}


long stt_GetBinaryBitVal(BYTE *pBinaryBuf, long nBinaryIndex)
{
	long nBytePos = nBinaryIndex / 8;
	long nBitPos = nBinaryIndex % 8;
	return stt_GetBinaryBitVal(pBinaryBuf, nBytePos, nBitPos);
}



