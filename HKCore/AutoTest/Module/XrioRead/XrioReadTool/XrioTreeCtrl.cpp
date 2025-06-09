// D:\WorkLiJQ\Source\AutoTest\Module\XrioRead\XrioReadTool\XrioTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
//#include "XrioAnyliseTool.h"
#include "XrioTreeCtrl.h"
#include "..\XrioCustomParameter.h"


// CXrioTreeCtrl

IMPLEMENT_DYNAMIC(CXrioTreeCtrl, CTreeCtrl)

CXrioTreeCtrl::CXrioTreeCtrl()
{
	m_pXrioCustom = NULL;
	m_pFrameWnd = NULL;
}

CXrioTreeCtrl::~CXrioTreeCtrl()
{
	m_oParametersListRef.RemoveAll();
}


BEGIN_MESSAGE_MAP(CXrioTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CXrioTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CXrioTreeCtrl 消息处理程序

BOOL CXrioTreeCtrl::OnShowXrioTree(CXrioCustom *pXrioCustom)
{
	m_pXrioCustom = pXrioCustom;
	m_oParametersListRef.RemoveAll();
	DeleteAllItems();

	if (m_pXrioCustom == NULL)
	{
		return FALSE;
	}

	HTREEITEM hTreeItem = Insert(m_pXrioCustom, TVI_ROOT, NULL);

//	if (m_bSetExBaseItemData)
	{
		hTreeItem = (HTREEITEM)m_pXrioCustom->m_dwItemData;
	}

	Expand(hTreeItem,TVE_EXPAND);
	SelectItem(hTreeItem);
	OnTvnSelchanged(hTreeItem);

	return TRUE;
}

HTREEITEM CXrioTreeCtrl::Insert(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter)
{
	HTREEITEM hTreeItem = NULL;

	if (pItem == NULL)
	{
		return NULL;
	}

	if (!CanInsert(pItem))
	{
		return NULL;
	}

	UINT nImg = GetImgIndex(pItem);

	hTreeItem = InsertItem(pItem->m_strName, nImg, nImg, htiParent,hAfter);

//	if (m_bSetExBaseItemData)
	{
		pItem->m_dwItemData = (DWORD)hTreeItem;
	}

	SetItemData(hTreeItem, (DWORD)pItem);

	if (pItem->IsBaseList())
	{
		CExBaseList *pList = (CExBaseList*)pItem;
		POS pos = pList->GetHeadPosition();

		while (pos != NULL)
		{
			CExBaseObject *p = pList->GetNext(pos);
			Insert(p, hTreeItem, NULL);
		}
	}

	return hTreeItem;
}

UINT CXrioTreeCtrl::GetImgIndex(CExBaseObject*pItem)
{
	UINT nClassID = pItem->GetClassID();

	if (nClassID == XRIOCLASSID_CUSTOM)
	{
		return _XRIO_IMAGE_INDEX_CUSTOM_;
	}
	else if(nClassID == XRIOCLASSID_CUSTOMBLOCK)
	{
		return _XRIO_IMAGE_INDEX_BLOCK_;
	}
	else if(nClassID == XRIOCLASSID_CUSTOMPARAMETER)
	{
		return _XRIO_IMAGE_INDEX_PARAMETER_;
	}

	return 0;
}

BOOL CXrioTreeCtrl::CanInsert(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();

	if ((nClassID == XRIOCLASSID_CUSTOM)||(nClassID == XRIOCLASSID_CUSTOMBLOCK)/*||(nClassID == XRIOCLASSID_CUSTOMPARAMETER)*/)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



void CXrioTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem = GetSelectedItem();

	OnTvnSelchanged(hItem);

	*pResult = 0;
}

void CXrioTreeCtrl::OnTvnSelchanged(HTREEITEM hItem)
{
	if (hItem != NULL)
	{
		CExBaseObject* pSelObj = (CExBaseObject*)GetItemData(hItem);
		ASSERT(pSelObj != NULL);
		m_oParametersListRef.RemoveAll();
		xrio_GetAllChildParameters((CExBaseList&)(*pSelObj),m_oParametersListRef);
		xrio_PostParaObjSelChangeMsg(m_pFrameWnd, WM_THREAD_XRIO_PARAMETERS_SHOW, &m_oParametersListRef);
	}
}

