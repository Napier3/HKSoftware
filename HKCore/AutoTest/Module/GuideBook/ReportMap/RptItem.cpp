#include "StdAfx.h"
#include "RptItem.h"

CRptItem::CRptItem(void)
{
	m_pGbItemRef = NULL;
	m_bHasBkmk = FALSE;
	m_bExpand = FALSE;
}


CRptItem::~CRptItem(void)
{
	DeleteAll();
}

void CRptItem::InitGbItems(CGuideBook *pGuideBook)
{
	CRptItem *pItem = new CRptItem();
	AddNewChild(pItem);
	pItem->m_pGbItemRef = pGuideBook;
    pItem->m_strName = g_sLangTxt_GlobalData;//_T("全局数据");
	pItem->m_strID = g_strGbGlobalDatasID;

	InitGbItem(pGuideBook);
	pGuideBook->m_pRptRef = pItem;
}

void CRptItem::InitGbItem(CExBaseList *pList)
{
	if (pList->IsBaseObject())
	{
		return;
	}

	UINT nClassID = pList->GetClassID();

	if (!Gb_IsItemBaseClassID(nClassID))
	{
		return;
	}

	m_pGbItemRef = (CGbItemBase *)pList;
	m_pGbItemRef->m_pRptRef = this;

	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			CRptItem *pItem = new CRptItem();
			AddNewChild(pItem);
			pItem->InitGbItem((CExBaseList*)p);
		}
	}
}

BOOL CRptItem::InitItemStateByBkmk()
{
	POS pos = GetHeadPosition();
	CRptItem *p = NULL;
	m_bHasBkmk = FALSE;

	if (m_pGbItemRef != NULL)
	{
		if (m_pGbItemRef->m_pRptMap != NULL)
		{
			m_bHasBkmk |= m_pGbItemRef->m_pRptMap->HasBkmk();
		}
	}

	while (pos != NULL)
	{
		p = (CRptItem*)GetNext(pos);
		m_bHasBkmk |= p->InitItemStateByBkmk();
	}

	return m_bHasBkmk;
}

void CRptItem::ClearDWData()
{
	POS pos = GetHeadPosition();
	CRptItem *p = NULL;
	m_dwItemData = 0;

	if (m_pGbItemRef != NULL)
	{
		m_pGbItemRef->m_pRptMap->ClearDWData();
	}

	while (pos != NULL)
	{
		p = (CRptItem*)GetNext(pos);
		p->ClearDWData();
	}
}

void CRptItem::InitExpandState(BOOL bExpand)
{
	POS pos = GetHeadPosition();
	CRptItem *p = NULL;

	while (pos != NULL)
	{
		p = (CRptItem*)GetNext(pos);
		p->m_bExpand = bExpand;
	}
}

BOOL CRptItem::IsAllAncestorExpand()
{
	CRptItem *pParent = this;
	BOOL bExpand = TRUE;

	while (pParent != NULL)
	{
		if (pParent->m_pGbItemRef->GetClassID() == GBCLASSID_GUIDEBOOK)
		{
			break;
		}

		if (!pParent->m_bExpand)
		{
			bExpand = FALSE;
			break;
		}
		
		pParent = (CRptItem*)pParent->GetParent();
	}

	return bExpand;
}

void CRptItem::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strName, 0, 1, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	if (m_pGbItemRef == NULL)
	{
		return;
	}

	m_pGbItemRef->m_pRptMap->InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}

long CRptItem::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;

	while (pos)
	{
		pObj = GetNext(pos);
		pObj->InsertTreeCtrl(pTreeCtrl,htiParent, dwParam);
		nCount++;
	}

	return nCount;
}

