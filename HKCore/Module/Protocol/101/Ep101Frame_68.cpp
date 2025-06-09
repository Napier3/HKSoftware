#include "StdAfx.h"

#include "Ep101Frame_68.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Head::CEp101Frame_68_Head()
{
	m_nLength = 0;
}

CEp101Frame_68_Head::~CEp101Frame_68_Head()
{

}

DWORD CEp101Frame_68_Head::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	m_nLength = pRcvBuffer[EP_101_FRAME_68_POS_LENGTH1];

	if (*pRcvBuffer != 0x68 && *(pRcvBuffer+EP_101_FRAME_68_POS_START2) != 0x68)
	{
		return -1;
	}

	m_byteLinkAddr = *(pRcvBuffer+EP_101_FRAME_68_POS_LINKADDR);

	BYTE byteSum = (BYTE)Ep_CalSum(pRcvBuffer+EP_101_FRAME_68_POS_CONTROL, m_nLength);

	if (byteSum != pRcvBuffer[m_nLength+EP_101_FRAME_68_POS_CONTROL])
	{
		m_dwState = EPFRAME_STATE_CHECK_ERROR;
	}

	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
		AddNewByteBlock(pDetailList, g_strEpFrameLength, 1, EP_101_FRAME_68_POS_LENGTH1);
		AddNewByteBlock(pDetailList, g_strEpFrameLength, 1, EP_101_FRAME_68_POS_LENGTH2);
		AddNewByteBlock(pDetailList, g_strEpFrameStart , 1, EP_101_FRAME_68_POS_START2);
		AddControlByteBlock(pDetailList, g_strEpFrameControl, 1, EP_101_FRAME_68_POS_CONTROL
			, *(pRcvBuffer+EP_101_FRAME_68_POS_CONTROL));
		AddNewByteBlock(pDetailList, g_strEpFrameLinkAddr , 1, EP_101_FRAME_68_POS_LINKADDR);
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, 6);
}

BOOL CEp101Frame_68_Head::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

DWORD CEp101Frame_68_Head::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Tail::CEp101Frame_68_Tail()
{
	
}

CEp101Frame_68_Tail::~CEp101Frame_68_Tail()
{

}

DWORD CEp101Frame_68_Tail::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = Ep_GetEpFramePos(pBufferPos);

	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameSumChk, 1, nPos);
	}

	nPos++;

	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameEnd, 1, nPos);
	}

	nPos++;

	return Ep_OffsetEpBufferCurr(pBufferPos, 2);
}

BOOL CEp101Frame_68_Tail::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

DWORD CEp101Frame_68_Tail::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

