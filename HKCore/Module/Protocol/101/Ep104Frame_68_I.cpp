#include "StdAfx.h"

#include "Ep104Frame_68_I.h"

CEp104Frame_68_I::CEp104Frame_68_I(void)
{
	
}

CEp104Frame_68_I::~CEp104Frame_68_I(void)
{

}


DWORD CEp104Frame_68_I::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	if (pBufferPos->bAddDetail)
	{
		CEpByteBlock *pBb = AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
		pBb = AddNewByteBlock(pDetailList, g_strEpFrameLength, 1, 1);
		pBb = AddNewByteBlock(pDetailList, _T("报文类型"), 1, 2);
		pBb = AddNewByteBlock(pDetailList, _T("保留（无意义）"), 1, 3);
		pBb = AddNewByteBlock(pDetailList, _T("接收序列号"), 2, 4);
	}

	BYTE byteData = *(pBufferPos->pBuffer + 1);

	return Ep_OffsetEpBufferCurr(pBufferPos, byteData + 2);
}

BOOL CEp104Frame_68_I::Match(PEPBUFFERPOS pBufferPos)
{
	//ASSERT (Ep_EpBufferLeave(pBufferPos) >= 6);
	if (Ep_EpBufferLeave(pBufferPos) < 6)
	{
		return FALSE;
	}

	if (*(pBufferPos->pBuffer) != 0x68)
	{
		return FALSE;
	}
	
	BYTE byteData = *(pBufferPos->pBuffer + 2);
	
	if ( (byteData & 0x01) == 0)
	{
		return TRUE;
	}
	
// 	if ( (byteData & 0x02) == 0)
// 	{
// 		return FALSE;
// 	}
	
	return FALSE;
}

DWORD CEp104Frame_68_I::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0x68;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

