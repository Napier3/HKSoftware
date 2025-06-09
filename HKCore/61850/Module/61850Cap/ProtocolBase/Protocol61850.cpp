// EpProtocolBas.cpp: implementation of the CProtocol61850 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protocol61850.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocol61850::CProtocol61850()
{ 
	m_pParseFrames = new C61850ParseFrameList();
	AddNewChild(m_pParseFrames);

	m_strName = _T("61850");
	m_strID = m_strName;
	m_pCapDeviceMngr = NULL;
}

CProtocol61850::~CProtocol61850()
{

}

CExBaseObject* CProtocol61850::Parse(CFrameMemBuffer *pBuffer, CFrameDetail *pDetailList, DWORD dwPara)
{
	InitBufPos();
	m_bufPos.dwPara = dwPara;
	pBuffer->GetBufferPos(m_bufPos);
	m_bufPos.pItemData = &pBuffer->m_oCapBufferItem;
	CExBaseObject *p = m_pParseFrames->Parse(&m_bufPos, pDetailList);

	if (p != NULL)
	{
		AddCapDevice(&pBuffer->m_oCapBufferItem, pBuffer, p);
	}

	return p;
}

CExBaseObject* CProtocol61850::Parse(CFrameMemBuffer *pBuffer, DWORD dwPara)
{
	InitBufPos();
	m_bufPos.dwPara = dwPara;
	pBuffer->GetBufferPos(m_bufPos);
	m_bufPos.pItemData = &pBuffer->m_oCapBufferItem;
	CExBaseObject *p = m_pParseFrames->Parse(&m_bufPos);

	if (p != NULL)
	{
		AddCapDevice(&pBuffer->m_oCapBufferItem, pBuffer, p);
	}

	return p;
}

void CProtocol61850::AddCapDevice(PEPCAPBUFFERITEM pItemData, CFrameMemBuffer *pBuffer, CExBaseObject *pFrame)
{
	CCapDeviceBase *pDevice = m_pCapDeviceMngr->FindCapDevice(pItemData);

	if (pDevice == NULL)
	{
		pDevice = m_pCapDeviceMngr->AddCapDevice(pItemData);
		long nLen = pBuffer->GetBufferLength();//GetDataLength();
		BYTE *pData = pBuffer->GetBuffer();
		pDevice->m_oBuffer.SetBuffer(pData, nLen);
		pDevice->SetChannelNum(pItemData->nChCount);
		pDevice->InitDevice(&m_oCapParseDatas);
		pDevice->ParseDeviceInfor();
		//pDevice->m_pFrame = pFrame;
		AfxGetMainWnd()->PostMessage(WM_ADDCAPDEVICE, (WPARAM)pDevice, (LPARAM)pDevice);
	}
	else
	{
		pDevice->AddCapDataBuffer(&m_oCapParseDatas);
	}
}

