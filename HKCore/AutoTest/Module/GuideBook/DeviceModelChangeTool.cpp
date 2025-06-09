// IecCfgDataViewBase.cpp : 实现文件
//

#include "stdafx.h"
#include "DeviceModelChangeTool.h"

//////////////////////////////////////////////////////////////////////////
CDvmDataChangeDeviceWndRef::CDvmDataChangeDeviceWndRef()
{
	m_pDeviceWndRef = NULL;
	m_bDataChanged = FALSE;
}

CDvmDataChangeDeviceWndRef::~CDvmDataChangeDeviceWndRef()
{
	
}

//////////////////////////////////////////////////////////////////////////
CDvmDataChangeDeviceWndRef* CDvmDataChangeDeviceObj::Register(CWnd *pWnd)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDataChangeMsgRcvRefObj(pWnd);
	
	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CDvmDataChangeDeviceWndRef();
	pFind->m_pDeviceWndRef = pWnd;
	pFind->m_bDataChanged = TRUE;
	AddNewChild(pFind);

	return pFind;
}

BOOL CDvmDataChangeDeviceObj::HasRegister(CWnd *pWndRef)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDataChangeMsgRcvRefObj(pWndRef);
	return (pFind != NULL);
}

void CDvmDataChangeDeviceObj::SetDataChanged(BOOL bChanged)
{
	CDvmDataChangeDeviceWndRef *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmDataChangeDeviceWndRef *)GetNext(pos);
		p->m_bDataChanged = bChanged;
	}

}

BOOL CDvmDataChangeDeviceObj::HasMsgNeedProcess(CWnd *pWndRef)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDataChangeMsgRcvRefObj(pWndRef);

	if (pFind != NULL)
	{
		return pFind->m_bDataChanged;
	}
	else
	{
		return FALSE;
	}
}

void CDvmDataChangeDeviceObj::ProcessMsg(CWnd *pWnd)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDataChangeMsgRcvRefObj(pWnd);

	if (pFind != NULL)
	{
		pFind->m_bDataChanged = FALSE;
	}
}

CDvmDataChangeDeviceWndRef* CDvmDataChangeDeviceObj::FindDataChangeMsgRcvRefObj(CWnd *pWndRef)
{
	CDvmDataChangeDeviceWndRef *p = NULL;
	CDvmDataChangeDeviceWndRef *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmDataChangeDeviceWndRef *)GetNext(pos);
		
		if (p->m_pDeviceWndRef == pWndRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//
long CDvmDataChangeMsgTool::g_nGlobalRef = 0;
CDvmDataChangeMsgTool* CDvmDataChangeMsgTool::g_pGlobal = NULL;

CDvmDataChangeMsgTool::CDvmDataChangeMsgTool()
{

}

CDvmDataChangeMsgTool::~CDvmDataChangeMsgTool()
{
	
}

CDvmDataChangeMsgTool* CDvmDataChangeMsgTool::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDvmDataChangeMsgTool();
	}

	return g_pGlobal;
}

void CDvmDataChangeMsgTool::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

CDvmDataChangeDeviceObj* CDvmDataChangeMsgTool::Register(CDevice *pDevice)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_Register(pDevice);
}

void CDvmDataChangeMsgTool::UnRegister(CDevice *pDevice)
{
	ASSERT (g_pGlobal != NULL);

	g_pGlobal->In_UnRegister(pDevice);
}

void CDvmDataChangeMsgTool::SetDataChanged(CDevice *pDevice, BOOL bChanged)
{
	ASSERT (g_pGlobal != NULL);

	g_pGlobal->In_SetDataChanged(pDevice, bChanged);
}


CDvmDataChangeDeviceWndRef* CDvmDataChangeMsgTool::Register(CDevice *pDevice, CWnd *pWndRef)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_Register(pDevice, pWndRef);
}

void CDvmDataChangeMsgTool::UnRegister(CWnd *pWndRef)
{
	ASSERT (g_pGlobal != NULL);

	g_pGlobal->In_UnRegister(pWndRef);
}

BOOL CDvmDataChangeMsgTool::HasMsgNeedProcess(CWnd *pWndRef)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_HasMsgNeedProcess(pWndRef);
}

void CDvmDataChangeMsgTool::ProcessMsg(CWnd *pWnd)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_ProcessMsg(pWnd);
}

void CDvmDataChangeMsgTool::OnDeleteObj(CExBaseObject *pObj)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_OnDeleteObj(pObj);
}

void CDvmDataChangeMsgTool::OnDeleteObjs(CExBaseList *pList)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_OnDeleteObjs(pList);
}

void CDvmDataChangeMsgTool::OnAddObj(CExBaseObject *pObj)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_OnAddObj(pObj);
}

void CDvmDataChangeMsgTool::OnAddObjs(CExBaseList *pList)
{
	ASSERT (g_pGlobal != NULL);

	return g_pGlobal->In_OnAddObjs(pList);
}


CDvmDataChangeDeviceObj* CDvmDataChangeMsgTool::In_Register(CDevice *pDevice)
{
	CDvmDataChangeDeviceObj *pFind = FindDevice(pDevice);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CDvmDataChangeDeviceObj();
	pFind->m_pDevice = pDevice;
	AddNewChild(pFind);

	return pFind;
}

void CDvmDataChangeMsgTool::In_UnRegister(CDevice *pDevice)
{
	CDvmDataChangeDeviceObj *pFind = FindDevice(pDevice);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}

void CDvmDataChangeMsgTool::In_SetDataChanged(CDevice *pDevice, BOOL bChanged)
{
	CDvmDataChangeDeviceObj *pFind = FindDevice(pDevice);

	if (pFind != NULL)
	{
		pFind->SetDataChanged(bChanged);
	}
}


CDvmDataChangeDeviceWndRef* CDvmDataChangeMsgTool::In_Register(CDevice *pDevice, CWnd *pWndRef)
{
	CDvmDataChangeDeviceObj *pFind = FindDevice(pDevice);

	if (pFind != NULL)
	{
		return pFind->Register(pWndRef);
	}
	else
	{
		return NULL;
	}
}

void CDvmDataChangeMsgTool::In_UnRegister(CWnd *pWndRef)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDeviceWndRef(pWndRef);

	if (pFind != NULL)
	{
		CDvmDataChangeDeviceObj *pDeviceObj = (CDvmDataChangeDeviceObj*)pFind->GetParent();
		pDeviceObj->Delete(pFind);
	}
}

BOOL CDvmDataChangeMsgTool::In_HasMsgNeedProcess(CWnd *pWndRef)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDeviceWndRef(pWndRef);

	if (pFind != NULL)
	{
		return pFind->m_bDataChanged;
	}
	else
	{
		return TRUE;
	}
}

void CDvmDataChangeMsgTool::In_ProcessMsg(CWnd *pWnd)
{
	CDvmDataChangeDeviceWndRef *pFind = FindDeviceWndRef(pWnd);

	if (pFind != NULL)
	{
		pFind->m_bDataChanged = FALSE;
	}
}

CDvmDataChangeDeviceObj* CDvmDataChangeMsgTool::FindDevice(CDevice *pDevice)
{
	POS pos = GetHeadPosition();
	CDvmDataChangeDeviceObj *p = NULL;
	CDvmDataChangeDeviceObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataChangeDeviceObj *)GetNext(pos);

		if (p->m_pDevice == pDevice)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDataChangeDeviceWndRef* CDvmDataChangeMsgTool::FindDeviceWndRef(CWnd *pWndRef)
{
	POS pos = GetHeadPosition();
	CDvmDataChangeDeviceObj *p = NULL;
	CDvmDataChangeDeviceWndRef *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataChangeDeviceObj *)GetNext(pos);
		pFind = p->FindDataChangeMsgRcvRefObj(pWndRef);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}


void CDvmDataChangeMsgTool::In_OnDeleteObj(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return;
	}

	CDevice *pDevice = (CDevice*)pObj->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice == NULL)
	{
		return;
	}

	SetDataChanged(pDevice, TRUE);
}


void CDvmDataChangeMsgTool::In_OnDeleteObjs(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		In_OnDeleteObj(p);
	}
}

void CDvmDataChangeMsgTool::In_OnAddObj(CExBaseObject *pObj)
{
	In_OnDeleteObj(pObj);
}

void CDvmDataChangeMsgTool::In_OnAddObjs(CExBaseList *pList)
{
	In_OnDeleteObjs(pList);
}