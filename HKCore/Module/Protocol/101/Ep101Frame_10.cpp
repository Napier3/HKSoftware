#include "StdAfx.h"

#include "Ep101Frame_10.h"

CEp101Frame_10::CEp101Frame_10(void)
{

}

CEp101Frame_10::~CEp101Frame_10(void)
{

}

DWORD CEp101Frame_10::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);


// 	if (pBufferPos->bAddDetail)
// 	{
// 		AddControlByteBlock(pDetailList, g_strEpFrameControl, 1, EP_101_FRAME_10_POS_CONTROL
// 			, *(pRcvBuffer+EP_101_FRAME_10_POS_CONTROL));
// 	}

	m_byteLinkAddr = *(pRcvBuffer+EP_101_FRAME_10_POS_LINKADDR);
	
	BYTE byteSum = (BYTE)Ep_CalSum(pRcvBuffer+EP_101_FRAME_10_POS_CONTROL, 2);

	if (byteSum != *(pRcvBuffer+EP_101_FRAME_10_POS_SUM_CHK))
	{
		m_dwState = EPFRAME_STATE_CHECK_ERROR;
	}

	//pBufferPos->nIndex += 5; //CEp101Frame_10报文长度为5个字节


	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
		AddNewByteBlock(pDetailList, g_strEpFrameControl , 1, EP_101_FRAME_10_POS_CONTROL);
		AddNewByteBlock(pDetailList, g_strEpFrameLinkAddr , 1, EP_101_FRAME_10_POS_LINKADDR);
		AddNewByteBlock(pDetailList, g_strEpFrameSumChk , 1, EP_101_FRAME_10_POS_SUM_CHK);
		AddNewByteBlock(pDetailList, g_strEpFrameEnd , 1, EP_101_FRAME_10_POS_END);
	}


	return Ep_OffsetEpBufferCurr(pBufferPos, EP_101_FRAME_10_POS_END+1);
}

BOOL CEp101Frame_10::Match(PEPBUFFERPOS pBufferPos)
{
	if (Ep_EpBufferLeave(pBufferPos) < EP_101_FRAME_10_LENGTH)
	{
		return FALSE;
	}

	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*(pBuffer) != 0x10)
	{
		return FALSE;
	}

	if (*(pBuffer+EP_101_FRAME_10_POS_END) != 0x16)
	{
		return 0;
	}

	return 1;
}

DWORD CEp101Frame_10::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0X10;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

