// XFileTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibTreeCtrl.h"

// CCharLibTreeCtrl

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharLibTreeCtrl::CCharLibTreeCtrl()
{

}

CCharLibTreeCtrl::~CCharLibTreeCtrl()
{
}


CExBaseObject* CCharLibTreeCtrl::GetSelObject()
{
	HTREEITEM hSel = GetSelectedItem();

	if (hSel == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hSel);
	return pSel;
}

void CCharLibTreeCtrl::ShowCharLib(CCharacteristicLib *pLib, BOOL bOnllyShowFolder)
{
	m_bOnllyShowFolder = bOnllyShowFolder;
	m_pCharacteristicLib = pLib;
	HTREEITEM hItem = ShowCharFolder(pLib, TVI_ROOT);
	Expand(hItem, TVE_EXPAND);
}

HTREEITEM CCharLibTreeCtrl::ShowCharFolder(CCharacterFolder *pRootFolder, HTREEITEM hParent)
{
	HTREEITEM hFolder = NULL;
	
	if (pRootFolder->GetClassID() == CHARCLASSID_CCHARFOLDER)
	{
		hFolder = InsertItem(pRootFolder->m_strName, 2, 2, hParent);
	}
	else
	{
		hFolder = InsertItem(pRootFolder->m_strName, 0, 0, hParent);
	}

	if (!m_bOnllyShowFolder)
	{
		pRootFolder->m_dwItemData = (DWORD)hFolder;
	}

	SetItemData(hFolder, (DWORD)pRootFolder);

	POS pos = pRootFolder->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pRootFolder->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CHARCLASSID_CCHARFOLDER)
		{
			ShowCharFolder((CCharacterFolder*)p, hFolder);
		}
		else if ( nClassID == CHARCLASSID_CCHARACTERISTIC)
		{
			if (!m_bOnllyShowFolder)
			{
				HTREEITEM hItem = InsertItem(p->m_strName, 1, 1, hFolder);
				SetItemData(hItem, (DWORD)p);
				p->m_dwItemData = (DWORD)hItem;
			}
		}
	}

	return hFolder;
}

CCharacteristic* CCharLibTreeCtrl::GetCurrSelChar()
{
	CCharacteristic *pFind = NULL;
	CExBaseObject *pSel = GetSelObject();

	if (pSel->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
	{
		pFind = (CCharacteristic*)pSel; 
	}

	return pFind;
}

CCharacterFolder* CCharLibTreeCtrl::GetCurrSelFolder(BOOL bHasRoot)
{
	CCharacterFolder *pFind = NULL;
	CExBaseObject *pSel = GetSelObject();

	if (pSel == NULL)
	{
		return NULL;
	}

	if (pSel->GetClassID() == CHARCLASSID_CCHARFOLDER)
	{
		pFind = (CCharacterFolder *)pSel; 
	}
	else if (pSel->GetClassID() == CHARCLASSID_CCHARACTERISTICLIB)
	{
		if (bHasRoot)
		{
			pFind = (CCharacterFolder *)pSel; 
		}
	}

	return pFind;
}


void CCharLibTreeCtrl::InsertCharTemp(CCharacteristic *pCharTemp)
{
	CExBaseList *pParent = (CExBaseList*)pCharTemp->GetParent();
	HTREEITEM hParent = (HTREEITEM)pParent->m_dwItemData;
	HTREEITEM hItem = InsertItem(pCharTemp->m_strName, 1, 1, hParent);
	SetItemData(hItem, (DWORD)pCharTemp);
	pCharTemp->m_dwItemData = (DWORD)hItem;
}

void CCharLibTreeCtrl::UpdateCharTemp(CCharacteristic *pCharTemp)
{
	HTREEITEM hItem = (HTREEITEM)pCharTemp->m_dwItemData;
	SetItemText(hItem, pCharTemp->m_strName);
}

void CCharLibTreeCtrl::InsertCharFolder(CCharacterFolder *pCharFolder)
{
	CExBaseList *pParent = (CExBaseList*)pCharFolder->GetParent();
	HTREEITEM hParent = (HTREEITEM)pParent->m_dwItemData;
	HTREEITEM hItem = InsertItem(pCharFolder->m_strName, 2, 2, hParent);
	SetItemData(hItem, (DWORD)pCharFolder);
	pCharFolder->m_dwItemData = (DWORD)hItem;
}

void CCharLibTreeCtrl::UpdateCharFolder(CCharacterFolder *pCharFolder)
{
	HTREEITEM hItem = (HTREEITEM)pCharFolder->m_dwItemData;
	SetItemText(hItem, pCharFolder->m_strName);
}

