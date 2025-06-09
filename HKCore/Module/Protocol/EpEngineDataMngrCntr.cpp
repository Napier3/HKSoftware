#include "StdAfx.h"
#include "EpEngineDataMngrCntr.h"
#include "EpEngineThread.h"

//////////////////////////////////////////////////////////////////////////
//CEpEngineData
CEpEngineData::CEpEngineData(CEpProtocolBase *pProtocol, CEpDevice *pDevice)
{
	m_pEpRecordMngr = NULL;
	m_pProtocol = NULL;
	m_pDevice = NULL;
	m_pEngineThread = NULL;

	m_pDevice = pDevice;
	m_pProtocol = pProtocol;  
	m_pEpRecordMngr = new  CEpRecordMngr();
	m_pEpRecordMngr->SetParent(this);

	InitEngineData(pProtocol, pDevice);
}

BOOL CEpEngineData::InitEngineData(CEpProtocolBase *pProtocol, CEpDevice *pDevice)
{
	//设备数据模型
	m_pDevice = pDevice;

	//规约模板对象
	m_pProtocol = pProtocol;
	m_pProtocol->SetParent(this);

	return IsEngineDataValid();
}

BOOL CEpEngineData::IsConnectSuccessful()
{
	if (m_pEngineThread == NULL)
	{
		return FALSE;
	}

	CEpEngineThread *pThread = (CEpEngineThread*)m_pEngineThread;
	return pThread->IsConnectSuccessful();
}

BOOL CEpEngineData::IsEngineDataValid()
{
	if (m_pDevice == NULL|| m_pProtocol == NULL)
	{
		return FALSE;
	}

// 	if (m_pDevice->GetCount() <= 1)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}


CEpEngineData::~CEpEngineData()
{
	if (m_pEngineThread != NULL)
	{
		m_pEngineThread->PostThreadMessage(WM_QUIT, 0, 0);
	}

	if (m_pDevice != NULL)
	{
		delete m_pDevice;
		m_pDevice = NULL;
	}

	if (m_pProtocol != NULL)
	{
		delete m_pProtocol;
		m_pProtocol = NULL;
	}

	if (m_pEpRecordMngr != NULL)
	{
		delete m_pEpRecordMngr;
		m_pEpRecordMngr = NULL;
	}
}

void CEpEngineData::OnDeviceConnectFinish(BOOL bConnectSuccessful)
{
	m_oSystemMsgSendRegister.m_wParam = bConnectSuccessful;
	m_oSystemMsgSendRegister.m_lParam = bConnectSuccessful;
	m_oSystemMsgSendRegister.PostMessage(-1, -1);
}

BOOL CEpEngineData::IsThreadExit()
{
	if (m_pEngineThread == NULL)
	{
		return TRUE;
	}

	return ((CEpEngineThread*)m_pEngineThread)->IsThreadExitExtern();
}

void CEpEngineData::ExitEngineThread()
{
	if (IsThreadExit())
	{
		return;
	}

	if (m_pEngineThread != NULL)
	{
		((CEpEngineThread*)m_pEngineThread)->ExitEngineThread();
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpEngineDataMngrCntr
CEpEngineDataMngrCntr::CEpEngineDataMngrCntr(void)
{
	m_strName = L"设备列表";
}

CEpEngineDataMngrCntr::~CEpEngineDataMngrCntr(void)
{
}

CEpEngineData*  CEpEngineDataMngrCntr::Create(CEpProtocolBase *pProtocol, CEpDevice *pDevice)
{
	CEpEngineData *pNew = new CEpEngineData(pProtocol, pDevice);
	AddTail(pNew);
	return pNew;
}

CEpEngineData* CEpEngineDataMngrCntr::Find(CEpDevice *pDevice)
{
	CEpEngineData *pFind = NULL;
	CEpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpEngineData*)GetNext(pos);

		if (pDevice == p->m_pDevice)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CEpEngineData* CEpEngineDataMngrCntr::Find(CEpProtocolBase *pProtocol)
{
	CEpEngineData *pFind = NULL;
	CEpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpEngineData*)GetNext(pos);

		if (pProtocol == p->m_pProtocol)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CEpEngineData* CEpEngineDataMngrCntr::Find(CEpDeviceCmmConfig *pCmmConfig)
{
	CEpEngineData *pFind = NULL;
	CEpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpEngineData*)GetNext(pos);

		if (pCmmConfig == p->m_pDeviceCmmConfig)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


void CEpEngineDataMngrCntr::InsertNodeToTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strName, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CEpEngineData *pEngineData = (CEpEngineData *)GetNext(pos);
		ASSERT(pEngineData != NULL);
		CEpDevice *pDevice = pEngineData->m_pDevice;
		ASSERT(pDevice != NULL);

		if (pDevice != NULL)
		{
			pDevice->InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
		}

	}

	pTreeCtrl->Expand((HTREEITEM)m_dwItemData, TVE_EXPAND);		
}
