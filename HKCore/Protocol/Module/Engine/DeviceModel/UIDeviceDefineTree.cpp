// UIDeviceDefineTree.cpp : 实现文件
//

#include "stdafx.h"
#include "UIDeviceDefineTree.h"
#include "DevcieModel.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUIDeviceDefineTree

IMPLEMENT_DYNAMIC(CUIDeviceDefineTree, CTreeCtrl)

CUIDeviceDefineTree::CUIDeviceDefineTree()
{

}

CUIDeviceDefineTree::~CUIDeviceDefineTree()
{
}


BEGIN_MESSAGE_MAP(CUIDeviceDefineTree, CTreeCtrl)
END_MESSAGE_MAP()



// CUIDeviceDefineTree 消息处理程序
void CUIDeviceDefineTree::ShowDevice(CExBaseList *pDeviceDefine)
{
	DeleteAllItems();

	if (pDeviceDefine == NULL)
	{
		return;
	}

	CExBaseList *pDevice = ((CPpDvmDevice*)pDeviceDefine)->GetDeviceModel();

	if (pDevice == NULL)
	{
		return;
	}

	if (pDevice->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		InsertDevice((CDvmDevice*)pDevice, TVI_ROOT);
	}
	else
	{
		CString strText = _T("设备数据模型");
		HTREEITEM hRoot = InsertItem(strText, 0, 0, TVI_ROOT);
		SetItemData(hRoot,(DWORD)pDevice);
		pDevice->m_dwReserved = (DWORD)hRoot;

		CDvmDevice *p = NULL;
		POS pos = pDevice->GetHeadPosition();

		while (pos != NULL)
		{
			p = (CDvmDevice*)pDevice->GetNext(pos);
			InsertDevice((CDvmDevice*)p, hRoot);
		}

		Expand(hRoot, TVE_EXPAND);
	}

}

void CUIDeviceDefineTree::InsertLdevice(CDvmLogicDevice *pLDevice, HTREEITEM hParent)
{
	CString strText;
	strText.Format(_T("%s(%s)(%d)"), pLDevice->m_strName, pLDevice->m_strID, pLDevice->m_nIndex);
	HTREEITEM hLDevice = InsertItem(strText, 0, 0, hParent);
	SetItemData(hLDevice,(DWORD)pLDevice);
	pLDevice->m_dwReserved = (DWORD)hLDevice;
	
	CDvmDataset *pDataset = NULL;
	POS pos = pLDevice->GetHeadPosition();

	while (pos != NULL)
	{
		pDataset = (CDvmDataset*)pLDevice->GetNext(pos);
		
// 		strText.Format(_T("%s(%s)(%d)"), pDataset->m_strName, pDataset->m_strID, pDataset->m_nIndex);
// 		HTREEITEM hDataset = InsertItem(strText, 0, 0, hLDevice);
// 		SetItemData(hDataset, (DWORD)pDataset);

		if (pDataset->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			InsertDataset(pDataset, hLDevice);
		}
	}

	Expand(hLDevice, TVE_EXPAND);
}

void CUIDeviceDefineTree::InsertDataset(CDvmDataset *pDataset, HTREEITEM hParent)
{
	CString strText;
	strText.Format(_T("%s(%s)(%d)"), pDataset->m_strName, pDataset->m_strID, pDataset->m_nIndex);
	HTREEITEM hDataset = InsertItem(strText, 0, 0, hParent);
	SetItemData(hDataset, (DWORD)pDataset);
	pDataset->m_dwReserved = (DWORD)hDataset;
}

void CUIDeviceDefineTree::InsertDevice(CDvmDevice *pDevice, HTREEITEM hParent)
{
	CString strText;
	strText.Format(_T("%s(%s)"), pDevice->m_strName, pDevice->m_strID);
	HTREEITEM hDevice = InsertItem(strText, 0, 0, hParent);
	SetItemData(hDevice,(DWORD)pDevice);
	pDevice->m_dwReserved = (DWORD)hDevice;

	InsertDataset(pDevice->m_pDeviceAttr, hDevice);

	CDvmLogicDevice *pLDevice = NULL;
	POS pos = pDevice->GetHeadPosition();

	while (pos != NULL)
	{
		pLDevice = (CDvmLogicDevice*)pDevice->GetNext(pos);
		InsertLdevice(pLDevice, hDevice);
	}

	Expand(hDevice, TVE_EXPAND);
}

CDvmDataset* CUIDeviceDefineTree::GetCurrSelDataset()
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	CExBaseObject *p = (CExBaseObject*)GetItemData(hItem);

	if (p == NULL)
	{
		return NULL;
	}

	if (p->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return NULL;
	}

	return (CDvmDataset*)p;
}



CExBaseObject* CUIDeviceDefineTree::GetCurrSelObject()
{
	HTREEITEM hItem = GetSelectedItem();
	CExBaseObject *pSel = NULL;

	if (hItem != NULL)
	{
		pSel = (CExBaseObject*)GetItemData(hItem);
	}

	return pSel;
}

void CUIDeviceDefineTree::InsertDvmObject(CExBaseObject *pDvmObject)
{
	CExBaseList *pParent = (CExBaseList*)pDvmObject->GetParent();
	UINT nClassID = pDvmObject->GetClassID();

	switch (nClassID)
	{
	case DVMCLASSID_CDVMDEVICE:
		InsertDevice((CDvmDevice*)pDvmObject, (HTREEITEM)pParent->m_dwReserved);
		break;

	case DVMCLASSID_CDVMLOGICDEVICE:
		InsertLdevice((CDvmLogicDevice*)pDvmObject, (HTREEITEM)pParent->m_dwReserved);
		break;

	case DVMCLASSID_CDVMDATASET:
		InsertDataset((CDvmDataset*)pDvmObject, (HTREEITEM)pParent->m_dwReserved);
		break;
	}
}

