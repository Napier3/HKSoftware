// \Module\BaseClass\ExBaseListTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListTreeCtrl.h"

//////////////////////////////////////////////////////////////////////////
//QExBaseTreeWidgetItem
QExBaseTreeWidgetItem::QExBaseTreeWidgetItem(QTreeWidgetItem *parent, CExBaseObject *pData)
    : QTreeWidgetItem(parent)
{
    m_pItemData = pData;

	if (pData != NULL)
	{
		pData->m_dwItemData = (DWORD)this;
	}
}

QExBaseTreeWidgetItem::QExBaseTreeWidgetItem(QTreeWidget *parent, CExBaseObject *pData)
    : QTreeWidgetItem(parent)
{
    m_pItemData = pData;

	if (pData != NULL)
	{
		pData->m_dwItemData = (DWORD)this;
	}
}

QExBaseTreeWidgetItem::~QExBaseTreeWidgetItem()
{

}

//////////////////////////////////////////////////////////////////////////
// CExBaseListTreeCtrl
BOOL CExBaseListTreeCtrl::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	AddObj(pData);

	return TRUE;
}

BOOL CExBaseListTreeCtrl::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
	UpdateObject(pData);

	return TRUE;
}

BOOL CExBaseListTreeCtrl::Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther, BOOL bInvalidate)
{
	return DeleteObject(pData, bSelectOther);
}

BOOL CExBaseListTreeCtrl::Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate)
{
	SetCurrSelObj(pData);
	return TRUE;
}

#include<QHeaderView>

CExBaseListTreeCtrl::CExBaseListTreeCtrl(QWidget *parent)
	: QTreeWidget(parent)
{
	setStyle(QStyleFactory::create("windows"));
	setHeaderHidden(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
// 	header()->setResizeMode(QHeaderView::ResizeToContents );
// 	header()->setStretchLastSection( true);

	m_pOptrInterface = NULL;
	m_pList = NULL;
	
	connect(this,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	connect(this,SIGNAL(itemChanged(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemDoubleClicked(QTreeWidgetItem *, int)));

}

CExBaseListTreeCtrl::~CExBaseListTreeCtrl()
{
}


QExBaseTreeWidgetItem* CExBaseListTreeCtrl::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	if (parent == NULL)
	{
		return new QExBaseTreeWidgetItem(this, pData);
	}
	else
	{
		return new QExBaseTreeWidgetItem(parent, pData);
	}
}


QExBaseTreeWidgetItem* CExBaseListTreeCtrl::InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	QExBaseTreeWidgetItem *pNew = NewItem(parent, pData);
	pNew->setText(0, pData->m_strName);

	if (parent == NULL)
	{
		addTopLevelItem(pNew);
	}

	return pNew;
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::InsertItem(QTreeWidgetItem *parent, const CString &strText)
{
	QExBaseTreeWidgetItem *pNew = NewItem(parent, NULL);
	pNew->setText(0, strText);
	return pNew;
}
// CExBaseListTreeCtrl 消息处理程序


void CExBaseListTreeCtrl::ShowBaseList(CExBaseList *pList, BOOL bAddRoot)
{
	clear();
	QExBaseTreeWidgetItem* hItem = NULL;
	m_pList = pList;

	if (bAddRoot)
	{
        hItem = AddObj(pList, (QExBaseTreeWidgetItem* )NULL);

		if (hItem)
		{
			hItem->setExpanded(true);
		}
	}
	else
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
            AddObj(p,(QExBaseTreeWidgetItem* ) NULL);
		}
	}

	//resizeColumnToContents(0);
}

void CExBaseListTreeCtrl::ShowBaseListEx(CExBaseList *pList, BOOL bAddRoot, BOOL bExpand)
{
	clear();
	QExBaseTreeWidgetItem* hItem = NULL;
	m_pList = pList;

	if (bAddRoot)
	{
        hItem = AddObj(pList, (QExBaseTreeWidgetItem* )NULL);

		if (hItem)
		{
			hItem->setExpanded(bExpand);
		}
	}
	else
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
            AddObj(p,(QExBaseTreeWidgetItem* ) NULL,bExpand);
		}
	}

	//resizeColumnToContents(0);
}

void CExBaseListTreeCtrl::SetCurrSelObj(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return;
	}

	QExBaseTreeWidgetItem *hItem = (QExBaseTreeWidgetItem*)pObj->m_dwItemData;
	
	if (hItem != NULL)
	{
		hItem->setSelected(true);
	}
}

CExBaseObject* CExBaseListTreeCtrl::GetSelectObject()
{
	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem*)currentItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	return hItem->m_pItemData;
}

CString CExBaseListTreeCtrl::GetSelectID()
{
	return _T("");
}

CString CExBaseListTreeCtrl::GetSelectName()
{
	return _T("");
}

BOOL CExBaseListTreeCtrl::GetSelectID(CString &strID)
{
	return FALSE;
}

BOOL CExBaseListTreeCtrl::GetSelectName(CString &strName)
{
	return FALSE;
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::PrevSiblingItem(QExBaseTreeWidgetItem *hItem)
{
	if (hItem == NULL)
	{
		return NULL;
	}

	QTreeWidgetItem *hParent = hItem->parent();
	QTreeWidgetItem *hPrev = NULL, *p = NULL;

	if (hParent == NULL)
	{
		int nCount = topLevelItemCount();

		for (int k=0; k<nCount; k++)
		{
			p = topLevelItem(k);

			if (p == hItem)
			{
				break;
			}

			hPrev = p;
		}
	}
	else
	{
		int nCount = hParent->childCount();

		for (int k=0; k<nCount; k++)
		{
			p = hParent->child(k);

			if (p == hItem)
			{
				break;
			}

			hPrev = p;
		}
	}

	return (QExBaseTreeWidgetItem*)hPrev;
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::NextSiblingItem(QExBaseTreeWidgetItem *hItem)
{
	if (hItem == NULL)
	{
		return NULL;
	}

	QTreeWidgetItem *hParent = hItem->parent();
	QTreeWidgetItem *hNext = NULL, *p = NULL;

	if (hParent == NULL)
	{
		int nCount = topLevelItemCount();

		for (int k=0; k<nCount; k++)
		{
			p = topLevelItem(k);

			if (p == hItem)
			{
				hNext =  topLevelItem(k+1);
				break;
			}
		}
	}
	else
	{
		int nCount = hParent->childCount();

		for (int k=0; k<nCount; k++)
		{
			p = hParent->child(k);

			if (p == hItem)
			{
				hNext =  hParent->child(k+1);
				break;
			}
		}
	}

	return (QExBaseTreeWidgetItem*)hNext;
}


BOOL CExBaseListTreeCtrl::DeleteObject(CExBaseObject *pObj, BOOL bSelOther)
{
	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem*)pObj->m_dwItemData;

	if (hItem == NULL)
	{
		return FALSE;
	}

	QExBaseTreeWidgetItem* hSelItem = (QExBaseTreeWidgetItem*)currentItem();
	QExBaseTreeWidgetItem* hPrev = PrevSiblingItem(hItem);
	QExBaseTreeWidgetItem* hNext = NextSiblingItem(hItem);
	QExBaseTreeWidgetItem* hParent = (QExBaseTreeWidgetItem*)hItem->parent();

	if (hParent == NULL)
	{//toplevel node
		removeItemWidget(hItem, 0);
	}
	else
	{
		QExBaseTreeWidgetItem *pParent = (QExBaseTreeWidgetItem*)hItem->parent();
		pParent->removeChild(hItem);
	}

	if (!bSelOther)
	{
		return TRUE;
	}

	if (hSelItem != hItem)
	{
		return TRUE;
	}

	if (hNext != NULL)
	{
		hNext->setSelected(true);
	}
	else
	{
		if (hPrev != NULL)
		{
			hPrev->setSelected(true);
		}
		else if (hParent != NULL)
		{
			hParent->setSelected(true);
		}
	}

	return TRUE;
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::AddObj(CExBaseObject *pObj, BOOL bExpand)
{
	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();
	QExBaseTreeWidgetItem* hItem = NULL;

	if (pParent == NULL)
	{
		hItem = AddObj(pObj, (QExBaseTreeWidgetItem*)NULL, bExpand);
	}
	else
	{
		hItem = AddObj(pObj, (QExBaseTreeWidgetItem*)pParent->m_dwItemData, bExpand);
	}

// 	if (bExpand)
// 	{
// 		hItem->setExpanded(true);
// 	}

	//RedrawWindow();

	return hItem;
}

void CExBaseListTreeCtrl::UpdateObject(CExBaseObject *pObj, BOOL bUpdateChildren, BOOL bExpand)
{
	if (!CanAdd(pObj))
	{
		return;
	}

	QExBaseTreeWidgetItem *pItem = (QExBaseTreeWidgetItem*)pObj->m_dwItemData;
	pItem->setText(0, pObj->m_strName);

	if (bUpdateChildren)
	{
		//删除所有子对象，重新插入子对象
		int itemChildrenCounts = pItem->childCount();
		QTreeWidgetItem * child = NULL;

		while(itemChildrenCounts--)   
		{
			child = pItem->child(itemChildrenCounts); //index从大到小区做删除处理
			pItem->removeChild(child);
			delete child;
			child = NULL;
		}

		if (pObj->IsBaseList())
		{
			AddObjChildren((CExBaseList*)pObj, pItem, bExpand);

			if (bExpand)
			{
				pItem->setExpanded(true);
			}
		}
	}
}

BOOL CExBaseListTreeCtrl::CanAdd(CExBaseObject *pObj)
{
	return CanAdd(pObj->GetClassID());
}

BOOL CExBaseListTreeCtrl::CanAdd(UINT nClassID)
{
	//2021-8-21  lijunqing  如果没有定义，则显示所有
	if (m_arrdwClassID.GetCount() == 0)
	{
		return TRUE;
	}

	return GetIndexOfClassID(nClassID) >= 0;
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand)
{
	UINT nClassID = pObj->GetClassID();
	QExBaseTreeWidgetItem* hItem = NULL;

	if (!CanAdd(pObj))
	{
		return NULL;
	}

	hItem = InsertItem(hParent, pObj);

	if (!CBaseObject::IsBaseList(nClassID))
	{
		return hItem;
	}

	CExBaseList *pList = (CExBaseList*)pObj;
	AddObjChildren(pList, hItem, bExpand);

	if (bExpand)
	{
		hItem->setExpanded(true);
		//shaolei 2023-7-20 同步展开父项目节点

        if(hParent != NULL)//zhouhj 2023.7.25 判断是否为空
        {
            hParent->setExpanded(true);
        }
	}

	return hItem;
}


void CExBaseListTreeCtrl::AddObjChildren(CExBaseList *pList, QExBaseTreeWidgetItem* hItem, BOOL bExpand)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		AddObj(p, hItem, bExpand);
	}
}

QExBaseTreeWidgetItem* CExBaseListTreeCtrl::InsertObj(UINT nClassID, const  CString &strName, QExBaseTreeWidgetItem* hParent)
{
	return InsertItem(hParent, strName);
}

void CExBaseListTreeCtrl::ClearArrClassID()
{
	m_arrdwClassID.RemoveAll();
}

void CExBaseListTreeCtrl::AddClassID(UINT nClassID)
{
	m_arrdwClassID.Add(nClassID);
}

void CExBaseListTreeCtrl::RemoveClassID(UINT nClassID)
{
	long nIndex = GetIndexOfClassID(nClassID);

	if (nIndex >= 0)
	{
		m_arrdwClassID.RemoveAt(nIndex);
	}
}

long CExBaseListTreeCtrl::GetIndexOfClassID(UINT nClassID)
{
	long nIndex = 0;
	long nIndexFind = -1;
	long nCount = m_arrdwClassID.GetSize();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (nClassID == m_arrdwClassID.GetAt(nIndex))
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

//////////////////////////////////////////////////////////////////////////
/*void CExBaseListTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	if (m_pOptrInterface == NULL)
	{
		return;
	}

	CExBaseObject *pSel = GetSelectObject();
	m_pOptrInterface->OnItemBDblClk(this, pSel);
}
*/

void CExBaseListTreeCtrl::slot_TreeItemClicked(QTreeWidgetItem *pTreeItem, int nCol)
{
	if (m_pOptrInterface == NULL)
	{
		return;
	}

	if (pTreeItem == NULL)//zhouhj 20220407 
	{
		return;
	}

	CExBaseObject *pSel = ((QExBaseTreeWidgetItem*)pTreeItem)->m_pItemData;
	m_pOptrInterface->OnItemSelChanged(this, pSel);
}

void CExBaseListTreeCtrl::slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol)
{
	if (m_pOptrInterface == NULL)
	{
		return;
	}

	if (pTreeItem == NULL)//zhouhj 20220407 
	{
		return;
	}

	CExBaseObject *pSel = ((QExBaseTreeWidgetItem*)pTreeItem)->m_pItemData;
	m_pOptrInterface->OnItemCheckChanged(this, pSel);
}

void CExBaseListTreeCtrl::slot_TreeItemDoubleClicked(QTreeWidgetItem *pTreeItem, int nCol)
{
	if (m_pOptrInterface == NULL)
	{
		return;
	}

	CExBaseObject *pSel = ((QExBaseTreeWidgetItem*)pTreeItem)->m_pItemData;
	m_pOptrInterface->OnItemBDblClk(this, pSel);
}
