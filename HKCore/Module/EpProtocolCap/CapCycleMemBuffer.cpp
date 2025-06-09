// CCapCycleMemBuffer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CapCycleMemBuffer.h"

CCapCycleMemBuffer::CCapCycleMemBuffer()
{
	Ep_Cap_GenerateCaptureID();
	m_n64CapID = g_nCaptureID;
	m_n64IndexPos = 0;
	m_n64FrmDvPos = 0;
	m_ts.n64Time = 0;

	m_nProtocol = 0;
	m_dwFrameLen = 0;

	m_dwDeviceDataLen = 0;
	m_pDeviceDatas = new CEpDeviceDatas();
	m_nParseDataPos = -1;
	m_nParseDataLength = 0;
	Set_RECORD_NORECORD();
}

CCapCycleMemBuffer::~CCapCycleMemBuffer()
{
	Ep_FreeDatas(m_pDeviceDatas);
	delete m_pDeviceDatas;
	m_pDeviceDatas = NULL;
}

void CCapCycleMemBuffer::GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex)
{
	ZeroMemory(&oIndex, sizeof(EPCAPDBBUFFERINDEX));
	oIndex.n64CapID = m_n64CapID;   //cap id
	oIndex.ipGroup = m_ipGroup; //ip���߶˿�
	oIndex.nProtocol = m_nProtocol;  //��Լ����
	oIndex.tm = m_ts; //cap��ʱ��
	oIndex.nFrameLen = (WORD)m_dwFrameLen;//m_nDataLength;  //cap�ĳ���
//	oIndex.nDeviceDataLen = (WORD)m_dwDeviceDataLen;
	oIndex.n64CapFramePos = m_n64FrmDvPos;
	oIndex.n64CapDataPos = m_n64DataPos;
//	oIndex.oDataHead.nDataCount = 0;
//	oIndex.oDataHead.nDeviceDataType = m_pDeviceDatas->m_nDeviceDataType;
}

void CCapCycleMemBuffer::SetCurrPos(PEPBUFFERPOS pBufferPos)
{
	CEpCycleMemBuffer::SetCurrPos(pBufferPos);

	m_nProtocol = pBufferPos->nProtocol;
}
// 
// void CCapCycleMemBuffer::GetBufferPos(PEPBUFFERPOS pBufferPos)
// {
// 	CEpCycleMemBuffer::GetBufferPos(pBufferPos);
// 	pBufferPos->n64ID = m_n64CapID;
// 	pBufferPos->pDatas = m_pDeviceDatas;
// }

void CCapCycleMemBuffer::InitParsePos(const u_char *pkt_data, long nParseDataLen, EP_ETHER_CAP_IP_GROUP ipGroup, UINT nCapType)
{
	if (nParseDataLen < 0)
	{
		nParseDataLen = 0;
	}

	m_nParseDataLength = nParseDataLen;
	m_nParseDataPos = pkt_data - pkt_data_ref;
	m_ipGroup = ipGroup;
	Ep_SetProtocol_CapType(m_nProtocol, nCapType);
}

long CCapCycleMemBuffer::GetLengthNeedParse()
{
	return m_nParseDataLength - m_nCurrPos;
}

long CCapCycleMemBuffer::GetUnparseBufferLength()
{
	return m_nParseDataLength - m_nCurrPos;
}


void CCapCycleMemBuffer::GetBufferPos(PEPBUFFERPOS pBufferPos)
{
	if (m_nParseDataPos == -1)
	{
		pBufferPos->pBuffer = m_pBuffer;      //��������ַ
		pBufferPos->dwBufferLen = m_nDataLength;  //����������
	}
	else
	{
		pBufferPos->pBuffer = m_pBuffer+m_nParseDataPos;      //��������ַ
		pBufferPos->dwBufferLen = m_nParseDataLength;  //m_nDataLength;  //����������
	}

	pBufferPos->nIndex = m_nCurrPos;        //��ǰʹ�õĻ�����λ��
	pBufferPos->dwState = m_dwState;      //״̬������ƥ���״̬
	pBufferPos->n64ID = 0;        //��ص�ID������CaptureID

	pBufferPos->n64ID = m_n64CapID;
	pBufferPos->pDatas = m_pDeviceDatas;
}

void CCapCycleMemBuffer::SetCurrPos(long nPos)
{
	m_nCurrPos = nPos;

	if (m_nCurrPos >= m_nParseDataLength)
	{
		SetState(EBS_BEPARSED);
	}
	else
	{
		SetState(EBS_SOMEPARSED);
	}
}

