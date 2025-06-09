// D:\WorkLiJQ\Source\Module\EpProtocolCap\Config\EpCapConfigTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapConfigTreeCtrl.h"


// CEpCapConfigTreeCtrl

IMPLEMENT_DYNAMIC(CEpCapConfigTreeCtrl, CTreeCtrl)

CEpCapConfigTreeCtrl::CEpCapConfigTreeCtrl()
{

}

CEpCapConfigTreeCtrl::~CEpCapConfigTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CEpCapConfigTreeCtrl, CTreeCtrl)
END_MESSAGE_MAP()



// CEpCapConfigTreeCtrl 消息处理程序

BOOL CEpCapConfigTreeCtrl::CanShow(UINT nClassID)
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

BOOL CEpCapConfigTreeCtrl::CanShow(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	return CanShow(nClassID);
}

void CEpCapConfigTreeCtrl::ShowObj(CExBaseObject *pObj, HTREEITEM hParent)
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

void CEpCapConfigTreeCtrl::ShowCapConfig(CMonitorCapConfig *pCapConfig)
{
	m_pCapConfig = pCapConfig;
	ShowObj(pCapConfig, TVI_ROOT);
	Expand((HTREEITEM)m_pCapConfig->m_dwItemData, TVE_EXPAND);
}

void CEpCapConfigTreeCtrl::UpdateObj(CExBaseObject *pObj)
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

void CEpCapConfigTreeCtrl::ShowObj(CExBaseObject *pObj)
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

void CEpCapConfigTreeCtrl::DeleteObj(CExBaseObject *pObj)
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

