// XFileTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XFileMngrTreeCtrl.h"
#include "XFileDlgDefine.h"

// CXFileMngrTreeCtrl

CXFileMngrTreeCtrl::CXFileMngrTreeCtrl()
{

}

CXFileMngrTreeCtrl::~CXFileMngrTreeCtrl()
{
}

CXFile* CXFileMngrTreeCtrl::GetCurrSelFile()
{
	CXFile *pFile = NULL;
	CExBaseObject *pSel = GetSelObject();

	if (pSel->GetClassID() == CLASSID_XFILE)
	{
		pFile = (CXFile *)pSel; 
	}

	return pFile;
}


BOOL CXFileMngrTreeCtrl::CanInsert(CExBaseObject* pObj)
{
#ifndef exbase_not_use_m_dwReserved
	return (pObj->m_dwReserved > 0);
#else
	return 1;
#endif
}

void CXFileMngrTreeCtrl::InitContextMenuTree(CMenu &menu,CExBaseObject* pObj)
{
	if (m_pFrameWnd != NULL)
	{
		m_pFrameWnd->SendMessage(WM_INIT_XFILEMNGR_MENU, (WPARAM)(&menu), (LPARAM)pObj);
	}
	
}

