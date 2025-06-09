#include "StdAfx.h"

#include "EpMbRtuMasterFrame_01.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEpMbRtuMasterFrame_01::CEpMbRtuMasterFrame_01()
{
	
}

CEpMbRtuMasterFrame_01::~CEpMbRtuMasterFrame_01()
{

}

//设备响应：[设备地址] [命令号01] [返回的字节个数][数据1][数据2] ...[数据n][CRC校验的低8位] [CRC校验的高8位]
//例：[11][01][05][CD][6B][B2][0E][1B][CRC低][CRC高]
BOOL CEpMbRtuMasterFrame_01::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	CEpProtocol101 *pProtocol = (CEpProtocol101*)GetAncestor(EPCLASSID_PROTOCOL_101);
	ASSERT (pProtocol != NULL);
	long nLen = Ep_EpBufferLeave(pBufferPos);

	//设备地址
	if (*pBuffer != pProtocol->GetDeviceAddress())
	{
		return FALSE;
	}
	
	//命令号
	if (*(pBuffer+1) != 0x01)
	{	
		return FALSE;
	}
	
	//返回的字节个数
	BYTE byteCount = *(pBuffer+2);

	if (nLen < byteCount + 5)
	{
		Ep_SetMatchStateNotFull(pBufferPos);
	}
	
	return TRUE;
}

DWORD CEpMbRtuMasterFrame_01::ParseCode(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = Ep_GetEpFramePos(pBufferPos);
	long nPosOld = nPos;

	//返回的字节个数
	long nCount = *pBuffer;
	AddNewByteBlock(g_strEpCount, 1, nPos);
	nPos++;

	//][数据1][数据2] ...[数据n]
	for (long nIndex=0; nIndex<nCount; nIndex++)
	{
		
	}

	return 0;
}

DWORD CEpMbRtuMasterFrame_01::ProduceCode(PEPBUFFERPOS pBufferPos)
{

	return 0;
}

