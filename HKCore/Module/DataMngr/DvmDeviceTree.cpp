#include "stdafx.h"
#include "DvmDeviceTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CDvmDeviceTree::CDvmDeviceTree()
{
	m_bSetItemData = TRUE;
	m_pDvmDevice = NULL;
}

CDvmDeviceTree::~CDvmDeviceTree()
{
}

BEGIN_MESSAGE_MAP(CDvmDeviceTree, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDvmDeviceTree::OnTvnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CDvmDeviceTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CDvmDeviceTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	UINT uFlags;
	HTREEITEM hItem = HitTest(point,&uFlags);

	if( (hItem != NULL) && (TVHT_ONITEM & uFlags) )
	{
		//Expand(hItem, TVE_EXPAND);
		SelChanged(hItem);
	}

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CDvmDeviceTree::ShowDvmDevice(CDvmDevice *pDevice, CWnd *pMsgWnd, BOOL bSetItemData)
{
	m_bSetItemData = bSetItemData;
	LockWindowUpdate();
	m_pDvmDevice = pDevice;
	m_pMsgRcvWnd = pMsgWnd;
	DeleteAllItems();

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	HTREEITEM hDevice = NULL;
	hDevice = InsertItem(pDevice->m_strName, 0, 0);
	SetItemData(hDevice, (DWORD)pDevice);

	if (m_bSetItemData)
	{
		pDevice->m_dwItemData = (DWORD)hDevice;
	}

	POS pos = pDevice->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;

	while (pos != NULL)
	{
		pLdevice = (CDvmLogicDevice *)pDevice->GetNext(pos);
		InsertLdevice(pLdevice, hDevice);
	}

	Expand(hDevice, TVE_EXPAND);
	UnlockWindowUpdate();
}

void CDvmDeviceTree::InsertLdevice(CDvmLogicDevice *pLdevice, HTREEITEM hParent)
{
	HTREEITEM hLDevice = NULL;
	hLDevice = InsertItem(pLdevice->m_strName, 1, 1, hParent);
	SetItemData(hLDevice, (DWORD)pLdevice);

	if (m_bSetItemData)
	{
		pLdevice->m_dwItemData = (DWORD)hLDevice;
	}

	POS pos = pLdevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLdevice->GetNext(pos);
		if (pDataset->m_strID.CompareNoCase(_T("dsIecConfig"))==0)
		{
			continue;
		}

		InsertDataset(pDataset, hLDevice);
	}
}

void CDvmDeviceTree::InsertDataset(CDvmDataset *pDataset, HTREEITEM hParent)
{
	HTREEITEM hDataset = NULL;
	hDataset = InsertItem(pDataset->m_strName, 2, 2, hParent);
	SetItemData(hDataset, (DWORD)pDataset);

	if (m_bSetItemData)
	{
		pDataset->m_dwItemData = (DWORD)hDataset;
	}
}

CExBaseObject* CDvmDeviceTree::SelectItem(const CString& strID)
{
	if (m_pDvmDevice == NULL || m_bSetItemData == FALSE || strID.IsEmpty())
	{
		return NULL;
	}

	HTREEITEM hItem;
	CDvmDataset *pDataSet = m_pDvmDevice->FindDataset(strID);

	if (pDataSet != NULL)
	{
		hItem = (HTREEITEM)pDataSet->m_dwItemData;
		return SelChanged(hItem);
	}

	return NULL;
}

CExBaseObject* CDvmDeviceTree::SelChanged(HTREEITEM hItem)
{
	CExBaseObject* pNode  = (CExBaseObject*)GetItemData(hItem);
	ASSERT(pNode != NULL);

	CTreeCtrl::SelectItem(hItem);
	
	if (m_pMsgRcvWnd != NULL)
	{
		m_pMsgRcvWnd->PostMessage(DVMOBJ_SEL_CHANGED, (WPARAM)pNode, (LPARAM)pNode);
	}

	return pNode;
}

void CDvmDeviceTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
	
	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	if (pNMTreeView->itemNew.hItem == NULL || pNMTreeView->itemNew.lParam == 0)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(DVMOBJ_SEL_CHANGED, pNMTreeView->itemNew.lParam, pNMTreeView->itemNew.lParam);
}

CExBaseObject* CDvmDeviceTree::GetSelectObject()
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(hItem);
}

void CDvmDeviceTree::InsertDvmObj(CExBaseObject *pDvmObj)
{
	UINT nClassID = pDvmObj->GetClassID();
	CExBaseObject *pParent = (CExBaseObject*)pDvmObj->GetParent();
	HTREEITEM hParent = (HTREEITEM)pParent->m_dwItemData;

	if (nClassID == DVMCLASSID_CDVMLOGICDEVICE)
	{
		InsertLdevice((CDvmLogicDevice*)pDvmObj, hParent);
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		InsertDataset((CDvmDataset*)pDvmObj, hParent);
	}
}

void CDvmDeviceTree::UpdateDvmObj(CExBaseObject *pDvmObj)
{
	HTREEITEM hItem = (HTREEITEM)pDvmObj->m_dwItemData;
	SetItemText(hItem, pDvmObj->m_strName);
}
