#include "StdAfx.h"

#include "Ep104Frame_68.h"

//////////////////////////////////////////////////////////////////////////
//
CEp104Frame_68_Head::CEp104Frame_68_Head()
{
	
}

CEp104Frame_68_Head::~CEp104Frame_68_Head()
{

}

DWORD CEp104Frame_68_Head::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	long nLen = pRcvBuffer[EP_104_FRAME_68_POS_LENGTH];

	if (*pRcvBuffer != 0x68 )
	{
		return -1;
	}

	m_byteLinkAddr = *(pRcvBuffer+EP_104_FRAME_68_POS_LINKADDR);

// 	BYTE byteSum = (BYTE)Ep_CalSum(pRcvBuffer+EP_104_FRAME_68_POS_CONTROL, nLen);
// 
// 	if (byteSum != pRcvBuffer[nLen+EP_104_FRAME_68_POS_CONTROL])
// 	{
// 		m_dwState = EPFRAME_STATE_CHECK_ERROR;
// 	}

	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
		AddNewByteBlock(pDetailList, g_strEpFrameLength, 1, EP_104_FRAME_68_POS_LENGTH);

		//"��2����λ�鶨����Խ�APDU�ֳ�3�ֱ��ĸ�ʽ����I��ʽ��S��ʽ��U��ʽ��ͬʱ�����˷������к�"
		AddNewByteBlock(pDetailList, _T("���ĸ�ʽ/�������к�"), 2, 2);

		//"��2����λ�鶨���˽������к�"
		AddNewByteBlock(pDetailList, _T("�������к�") , 2, 4);
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, 6);
}

BOOL CEp104Frame_68_Head::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

DWORD CEp104Frame_68_Head::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
CEp104Frame_68_Tail::CEp104Frame_68_Tail()
{
	
}

CEp104Frame_68_Tail::~CEp104Frame_68_Tail()
{

}

DWORD CEp104Frame_68_Tail::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
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

BOOL CEp104Frame_68_Tail::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

DWORD CEp104Frame_68_Tail::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

