// D:\WorkLiJQ\Source\Module\EpProtocolCap\Config\EpQueryConfigTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EpQueryConfigTreeCtrl.h"


// CEpQueryConfigTreeCtrl

IMPLEMENT_DYNAMIC(CEpQueryConfigTreeCtrl, CTreeCtrl)

CEpQueryConfigTreeCtrl::CEpQueryConfigTreeCtrl()
{

}

CEpQueryConfigTreeCtrl::~CEpQueryConfigTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CEpQueryConfigTreeCtrl, CTreeCtrl)
END_MESSAGE_MAP()



// CEpQueryConfigTreeCtrl 消息处理程序

BOOL CEpQueryConfigTreeCtrl::CanShow(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCNETCONFIG
		|| nClassID == EMCCLASSID_CEMCQUERYADDRMAP
		|| nClassID == EMCCLASSID_CEMCSERIALCONFIG
		|| nClassID == EMCCLASSID_CEMCDEVICEMODELFILE
		|| nClassID == EMCCLASSID_CEMCNETDEVICE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CEpQueryConfigTreeCtrl::CanShow(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	return CanShow(nClassID);
}

void CEpQueryConfigTreeCtrl::ShowObj(CExBaseObject *pObj, HTREEITEM hParent)
{
	if (!CanShow(pObj))
	{
		return;
	}

	pObj->InsertOwnTreeCtrl(this, hParent);

	if (!pObj->IsBaseList())
	{
		return;
	}


	CExBaseList *pList = (CExBaseList *)pObj;
	CExBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();
	long nCount = 0;

	while (pos)
	{
		p = pList->GetNext(pos);
		ShowObj(p,(HTREEITEM)pObj->m_dwItemData);
	}
}

void CEpQueryConfigTreeCtrl::ShowCapConfig(CMonitorQueryConfig *pCapConfig)
{
	m_pCapConfig = pCapConfig;
	ShowObj(pCapConfig, TVI_ROOT);
	Expand((HTREEITEM)m_pCapConfig->m_dwItemData, TVE_EXPAND);
}

void CEpQueryConfigTreeCtrl::UpdateObj(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return;
	}

	if (pObj->m_dwItemData == 0)
	{
		return;
	}

	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();
	SetItemText((HTREEITEM)pObj->m_dwItemData, pObj->m_strName);
}

void CEpQueryConfigTreeCtrl::ShowObj(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return;
	}

	if (!CanShow(pObj))
	{
		return;
	}

	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();
	ShowObj(pObj, (HTREEITEM)pParent->m_dwItemData);
}

void CEpQueryConfigTreeCtrl::DeleteObj(CExBaseObject *pObj)
{
	if (!CanShow(pObj))
	{
		return;
	}
	
	if (pObj->m_dwItemData == 0)
	{
		return;
	}

	DeleteItem((HTREEITEM)pObj->m_dwItemData);
}

