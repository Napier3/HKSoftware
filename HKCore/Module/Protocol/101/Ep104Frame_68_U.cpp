#include "StdAfx.h"

#include "Ep104Frame_68_U.h"

CEp104Frame_68_U::CEp104Frame_68_U(void)
{
	
}

CEp104Frame_68_U::~CEp104Frame_68_U(void)
{

}


DWORD CEp104Frame_68_U::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	if (pBufferPos->bAddDetail)
	{
		CEpByteBlock *pBb = AddNewByteBlock(pDetailList, g_strEpFrameStart, 1, 0);
		pBb = AddNewByteBlock(pDetailList, g_strEpFrameLength, 1, 1);
		pBb = AddNewByteBlock(pDetailList, _T("报文类型"), 1, 2);

		int nTemp =*(pBufferPos->pBuffer + 2) & 0xFC;

		switch (nTemp)
		{
		case 0x04:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)启动数据传输"), 1, 2);
			break;
		case 0x08:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)确认启动数据传输"), 1, 2);
			break;
		case 0x10:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)停止数据传输"), 1, 2);
			break;
		case 0x20:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)确认停止数据传输"), 1, 2);
			break;
		case 0x40:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)测试链路"), 1, 2);
			break;
		case 0x80:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)确认测试链路"), 1, 2);
			break;
		default:
			pBb = AddNewByteBlock(pDetailList, _T("类型:(U)未知的报文控制命令"), 1, 2);
			break;
		}
	}

	BYTE byteData = *(pBufferPos->pBuffer + 1);//len

	return Ep_OffsetEpBufferCurr(pBufferPos, byteData + 2);
}

BOOL CEp104Frame_68_U::Match(PEPBUFFERPOS pBufferPos)
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
		return FALSE;
	}
	
	if ( (byteData & 0x02) == 0)
	{
		return FALSE;
	}
	
	return TRUE;
}

DWORD CEp104Frame_68_U::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0x68;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

