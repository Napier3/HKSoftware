#include "StdAfx.h"

#include "Ep101Frame_E5.h"

CEp101Frame_E5::CEp101Frame_E5(void)
{

}

CEp101Frame_E5::~CEp101Frame_E5(void)
{

}


DWORD CEp101Frame_E5::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{

	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

BOOL CEp101Frame_E5::Match(PEPBUFFERPOS pBufferPos)
{
	//ASSERT (Ep_EpBufferLeave(pBufferPos) > 0);
	if (Ep_EpBufferLeave(pBufferPos) <= 0)
	{
		return FALSE;
	}

	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*(pBuffer) == 0xE5)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_E5::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0xE5;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

