// UIDeviceNodeTree.cpp : 实现文件
//

#include "stdafx.h"
#include "UIDeviceNodeTree.h"


// CUIDeviceNodeTree

IMPLEMENT_DYNAMIC(CUIDeviceNodeTree, CTreeCtrl)

CUIDeviceNodeTree::CUIDeviceNodeTree()
{

}

CUIDeviceNodeTree::~CUIDeviceNodeTree()
{
}


BEGIN_MESSAGE_MAP(CUIDeviceNodeTree, CTreeCtrl)
END_MESSAGE_MAP()



// CUIDeviceNodeTree 消息处理程序

void CUIDeviceNodeTree::ShowDevice(CPpDevice *pDevice)
{
	pDevice->InsertOwnTreeCtrl(this, TVI_ROOT);

	CExBaseObject *p = NULL;
	POS pos = pDevice->GetHeadPosition();

	while (pos != NULL)
	{
		p = pDevice->GetNext(pos);
		InsertDvObject(p, (HTREEITEM)pDevice->m_dwItemData);
	}

	Expand((HTREEITEM)pDevice->m_dwItemData, TVE_EXPAND);
}

void CUIDeviceNodeTree::InsertDeviceNode(CPpDeviceNode *pDeviceNode)
{
	CExBaseObject *pParent = (CExBaseObject*)pDeviceNode->GetParent();
	InsertDvObject(pDeviceNode, (HTREEITEM)pParent->m_dwItemData);
}

void CUIDeviceNodeTree::InsertDvObject(CExBaseObject *pObj, HTREEITEM hParent)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID == DMCLASSID_DEVICENODE)
	{
		pObj->InsertOwnTreeCtrl(this, hParent);

		CExBaseList *pList = (CExBaseList*)pObj;
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			InsertDvObject(p, (HTREEITEM)pObj->m_dwItemData);
		}
	}
	else
	{

	}
}

CExBaseObject* CUIDeviceNodeTree::GetCurrSelObject()
{
	HTREEITEM hItem = GetSelectedItem();
	CExBaseObject *pSel = NULL;

	if (hItem != NULL)
	{
		pSel = (CExBaseObject*)GetItemData(hItem);
	}

	return pSel;
}

