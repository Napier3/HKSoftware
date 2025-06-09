// XFileTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "DataGroupTreeCtrl.h"

// CDataGroupTreeCtrl

CDataGroupTreeCtrl::CDataGroupTreeCtrl()
{

}

CDataGroupTreeCtrl::~CDataGroupTreeCtrl()
{
}


CExBaseObject* CDataGroupTreeCtrl::GetSelObject()
{
	HTREEITEM hSel = GetSelectedItem();

	if (hSel == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hSel);
	return pSel;
}

HTREEITEM CDataGroupTreeCtrl::ShowCDataGroup(CDataGroup *pRootFolder, HTREEITEM hParent)
{
	HTREEITEM hItem = InsertItem(pRootFolder->m_strName, 0, 0, hParent);
	SetItemData(hItem, (DWORD)pRootFolder);

	POS pos = pRootFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pRootFolder->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			ShowCDataGroup((CDataGroup*)p, hItem);
		}
	}

	return hItem;
}

CDataGroup* CDataGroupTreeCtrl::GetCurrSelGroup()
{
	CDataGroup *pFile = NULL;
	CExBaseObject *pSel = GetSelObject();

	if (pSel->GetClassID() == DTMCLASSID_CDATAGROUP)
	{
		pFile = (CDataGroup *)pSel; 
	}

	return pFile;
}


BOOL CDataGroupTreeCtrl::CanInsert(CExBaseObject* pObj)
{
	return (pObj->m_dwReserved > 0);
}

