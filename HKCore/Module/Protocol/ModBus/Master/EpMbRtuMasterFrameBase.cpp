#include "StdAfx.h"

#include "EpMbRtuMasterFrameBase.h"

//////////////////////////////////////////////////////////////////////////
//
CEpMbRtuMasterFrameBase::CEpMbRtuMasterFrameBase()
{
	m_pType = NULL;
}

CEpMbRtuMasterFrameBase::~CEpMbRtuMasterFrameBase()
{

}

DWORD CEpMbRtuMasterFrameBase::Parse(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = 0;

	//�豸��ַ
	AddNewByteBlock(g_strEpDeviceAddr, 1, 0);

	//�����
	AddNewTypeByteBlock(1, 1, pBuffer[1]);

	//���������
	nPos = 2;
	Ep_OffsetEpBufferCurr(pBufferPos, 2);
	nPos += ParseCode(pBufferPos);

	WORD wCrcCal = Ep_CRC(pBuffer, nPos);
	WORD wCrcFrame = *((WORD*)(pBuffer+nPos));
	
	if (wCrcCal != wCrcFrame)
	{
		m_dwState = EPFRAME_STATE_CHECK_ERROR;
	}

	//CRC
	AddNewByteBlock(g_strEpCRC, 2, nPos);

	return Ep_OffsetEpBufferCurr(pBufferPos, 2);
}

BOOL CEpMbRtuMasterFrameBase::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

//��[�豸��ַ] [�����01] [��ʼ�Ĵ�����ַ��8λ] [��8λ] [��ȡ�ļĴ�������8λ] [��8λ] [CRCУ��ĵ�8λ] [CRCУ��ĸ�8λ]
//����[11][01][00][13][00][25][CRC��][CRC��]
DWORD CEpMbRtuMasterFrameBase::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = 0;

	CEpProtocol101 *pProtocol = (CEpProtocol101*)GetAncestor(EPCLASSID_PROTOCOL_101);
	ASSERT (pProtocol != NULL);

	//�豸��ַ
	*pBuffer = (BYTE)(pProtocol->GetDeviceAddress());
	AddNewByteBlock(g_strEpDeviceAddr, 1, 0);

	//�����
	pBuffer[1] = 0x01;
	AddNewTypeByteBlock(1, 1, pBuffer[1]);

	//���������
	nPos = 2;
	Ep_OffsetEpBufferCurr(pBufferPos, 2);//����֮ǰƫ��λ��
	nPos += ParseCode(pBufferPos);

	//CRC
	WORD wCrcCal = Ep_CRC(pBuffer, nPos);
	pBuffer += nPos;
	*pBuffer = (BYTE)wCrcCal;
	*(pBuffer+1) = (BYTE)(wCrcCal >> 8);
	AddNewByteBlock(g_strEpCRC, 2, nPos);

	return Ep_OffsetEpBufferCurr(pBufferPos, 2);
}



DWORD CEpMbRtuMasterFrameBase::ParseCode(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

DWORD CEpMbRtuMasterFrameBase::ProduceCode(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

CEpByteBlockType* CEpMbRtuMasterFrameBase::AddNewTypeByteBlock(long nLen, long nIndex, BYTE byteValue)
{
	CEpByteBlockType *pNew = new CEpByteBlockType(byteValue);
	pNew->m_strID = g_strEpFuncCode;
	pNew->m_strName = g_strEpFuncCode;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	AddNewChild(pNew);
	m_pType = pNew;
	return pNew;
}

