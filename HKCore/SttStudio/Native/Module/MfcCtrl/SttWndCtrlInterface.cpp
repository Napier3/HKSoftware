// CSttWndCtrlInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "SttWndCtrlInterface.h"

//////////////////////////////////////////////////////////////////////////
//
CSttWndCtrlMsgRcvInterface::CSttWndCtrlMsgRcvInterface()
{
}

CSttWndCtrlMsgRcvInterface::~CSttWndCtrlMsgRcvInterface()
{
	RemoveAll();
}

void CSttWndCtrlMsgRcvInterface::ShowDatas()
{
	POS pos = GetHeadPosition();
	CSttWndCtrlInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->ShowData();
	}
}

void CSttWndCtrlMsgRcvInterface::SaveDatas()
{
	POS pos = GetHeadPosition();
	CSttWndCtrlInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->SaveData();
	}
}

void CSttWndCtrlMsgRcvInterface::ClearRefData()
{
	POS pos = GetHeadPosition();
	CSttWndCtrlInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->InitSttWnd(NULL);
	}
}
//////////////////////////////////////////////////////////////////////////
// CSttWndCtrlInterface
CSttWndCtrlInterface::CSttWndCtrlInterface()
{
	m_pRefData = NULL;
	m_pSttWndCtrlMsgRcv = NULL;
}

CSttWndCtrlInterface::~CSttWndCtrlInterface()
{
}

void CSttWndCtrlInterface::OnSttDataChanged()
{
	if (m_pSttWndCtrlMsgRcv != NULL)
	{
		m_pSttWndCtrlMsgRcv->OnSttDataChanged(m_pRefData);
	}
}

void CSttWndCtrlInterface::InitSttWnd(CDvmData *pData, CSttWndCtrlMsgRcvInterface *pMsgRcv)
{
	m_pSttWndCtrlMsgRcv = pMsgRcv;

	if (pMsgRcv->Find(this) == NULL)
	{
		pMsgRcv->AddTail(this);
	}

	InitSttWnd(pData);
}

void CSttWndCtrlInterface::InitSttWnd(CDvmData *pData)
{
	m_pRefData = pData;
	ShowData();
}

void CSttWndCtrlInterface::ShowData()
{

}

void CSttWndCtrlInterface::SaveData()
{
	
}

void CSttWndCtrlInterface::GetDataValue(CDvmData *pData)
{
//2021-9-29  lijunqing
	if (pData == NULL)
	{
		return;
	}

	if (m_pRefData != NULL)
	{
		if (m_pRefData != pData)
		{
			pData->m_strValue = m_pRefData->m_strValue;
			return;
		}
	}
	
	CDvmData *pOld = m_pRefData;
	m_pRefData = pData;
	SaveData();
	m_pRefData = pOld;
}

void CSttWndCtrlInterface::SetDataValue(const CString &strValue)
{
	if (m_pRefData == NULL)
	{
		return;
	}

	m_pRefData->m_strValue = strValue;
	ShowData();
}

void CSttWndCtrlInterface::SetDataValue(long nValue)
{
	if (m_pRefData == NULL)
	{
		return;
	}

	m_pRefData->m_strValue.Format(_T("%d"), nValue);;
	ShowData();
}
