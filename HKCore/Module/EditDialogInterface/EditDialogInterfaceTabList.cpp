#include "StdAfx.h"
#include "EditDialogInterfaceTabList.h"


//////////////////////////////////////////////////////////////////////////
//CEditDialogInterfaceTabList

CEditDialogInterfaceTabList::CEditDialogInterfaceTabList()
{
}

CEditDialogInterfaceTabList::~CEditDialogInterfaceTabList(void)
{
}

void CEditDialogInterfaceTabList::CreateEdit(CExBaseObject* pObj, CWnd* pParent)
{
	CEditDialogInterface::CreateEdit(pObj, pParent);
	CreateTabCtrl();	
};

void CEditDialogInterfaceTabList::CreateTabCtrl()
{
	if (!::IsWindow(m_TabCtrl.m_hWnd))
	{
		m_TabCtrl.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0,0,0,0), m_pParent, 30001,CMFCTabCtrl::LOCATION_TOP);
	}
}
