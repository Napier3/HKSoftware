//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceBase.cpp  CCapDeviceBase


#include "stdafx.h"
#include "CapDeviceBase.h"
#include "..\ProtocolBase\61850ParseFrameList.h"

CCapDeviceBase::CCapDeviceBase()
{
	//初始化属性
	ZeroMemory(m_byteDestMac, 6);
	ZeroMemory(m_byteSrcMac,6);
	m_dwAppID = 0;
	m_nType = 0;

	//初始化成员变量
	m_pFrame = NULL;
	m_n64CapDataIndex = 0;
	m_bSelect = 0;

	m_nFillBeginPos = 0;;
	m_nDatasCount = 0;
}

CCapDeviceBase::~CCapDeviceBase()
{
}

BOOL CCapDeviceBase::SetChannelNum(long nChannelNum)
{
	long nOldNum = GetCount();

	if (nChannelNum == nOldNum)
	{
		return FALSE;
	}

	if (nOldNum > nChannelNum)
	{
		return TRUE;
	}

	long nIndex = 0;
	long nCount = nChannelNum - nOldNum;
	CCapDeviceChBase *pCh = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pCh = CreateChannel();
		AddNewChild(pCh);
	}

	return nChannelNum;
}

void CCapDeviceBase::InitAddress()
{
	m_strDestAddress = st_GetMacString(m_byteDestMac);
	m_strSrcAddress = st_GetMacString(m_byteSrcMac);
}

void CCapDeviceBase::ParseDeviceInfor()
{
	if (m_pFrame != NULL)
	{
		return;
	}
	C61850ParseFrameList oFrameList;
	EPBUFFERPOS bufPos;
	ZeroMemory(&bufPos, sizeof(EPBUFFERPOS));
	m_oBuffer.GetBufferPos(bufPos);
	m_pFrame = oFrameList.ParseInfor(&bufPos, this);
}

void CCapDeviceBase::SetCapSelect(BOOL bSelect)
{
	m_nFillBeginPos = 0;;
	m_nDatasCount = 0;

	m_bSelect = bSelect;
	m_n64CapDataIndex = 0;
}

void CCapDeviceBase::AddCapDataBuffer(PEPCAPPARSEDATAS pDatas)
{
	if (!m_bSelect)
	{
		return;
	}

	//数据的次数
	m_n64CapDataIndex++;
	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	long nIndex = 0;
	EPCAPPARSEDATA *pSmvData = pDatas->pDatas;

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->CapRecord(pSmvData[nIndex].dwValue, m_nFillBeginPos);

		nIndex++;

		if (nIndex >= pDatas->dwDatas)
		{
			break;
		}
	}

	m_nFillBeginPos++;

	if (m_nFillBeginPos >= CAP_RECORD_POINTS)
	{
		m_nFillBeginPos = 0;
	}

	if (m_nDatasCount != CAP_RECORD_POINTS)
	{
		m_nDatasCount++;
	}

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->SetPosition(m_nFillBeginPos, m_nDatasCount);
	}
}

void CCapDeviceBase::InitDevice(PEPCAPPARSEDATAS pDatas)
{
	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	long nIndex = 0;
	EPCAPPARSEDATA *pData = pDatas->pDatas;

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->m_nChType = pData[nIndex].wChType;
		pCh->m_nLength = pData[nIndex].wLength;
		nIndex++;

		if (nIndex >= pDatas->dwDatas)
		{
			break;
		}
	}
}

void CCapDeviceBase::BeginCap()
{
	m_n64CapDataIndex = 0;
	m_nFillBeginPos = 0;
	m_nDatasCount = 0;

	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->SetPosition(m_nFillBeginPos, m_nDatasCount);
	}
}

