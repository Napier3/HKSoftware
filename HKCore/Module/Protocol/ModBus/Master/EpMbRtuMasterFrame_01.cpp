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

//�豸��Ӧ��[�豸��ַ] [�����01] [���ص��ֽڸ���][����1][����2] ...[����n][CRCУ��ĵ�8λ] [CRCУ��ĸ�8λ]
//����[11][01][05][CD][6B][B2][0E][1B][CRC��][CRC��]
BOOL CEpMbRtuMasterFrame_01::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	CEpProtocol101 *pProtocol = (CEpProtocol101*)GetAncestor(EPCLASSID_PROTOCOL_101);
	ASSERT (pProtocol != NULL);
	long nLen = Ep_EpBufferLeave(pBufferPos);

	//�豸��ַ
	if (*pBuffer != pProtocol->GetDeviceAddress())
	{
		return FALSE;
	}
	
	//�����
	if (*(pBuffer+1) != 0x01)
	{	
		return FALSE;
	}
	
	//���ص��ֽڸ���
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

	//���ص��ֽڸ���
	long nCount = *pBuffer;
	AddNewByteBlock(g_strEpCount, 1, nPos);
	nPos++;

	//][����1][����2] ...[����n]
	for (long nIndex=0; nIndex<nCount; nIndex++)
	{
		
	}

	return 0;
}

DWORD CEpMbRtuMasterFrame_01::ProduceCode(PEPBUFFERPOS pBufferPos)
{

	return 0;
}

