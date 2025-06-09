// CharElmentBaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElmentBaseDlg.h"


// CCharElmentBaseDlg

CCharElmentBaseDlg::CCharElmentBaseDlg()
{
	m_pDialog = NULL;
	m_pCharElementBase = NULL;
}

CCharElmentBaseDlg::~CCharElmentBaseDlg()
{
}



// CCharElmentBaseDlg 消息处理程序
void CCharElmentBaseDlg::Hide()
{
	m_pDialog->ShowWindow(SW_HIDE);
}

void CCharElmentBaseDlg::ShowCharElement(CCharElement *pObj)
{
	m_pCharElementBase = pObj;
	ShowData();
}

void CCharElmentBaseDlg::SetWindowPos(const CRect &rcWnd)
{
	ASSERT (m_pDialog != NULL);
	m_pDialog->MoveWindow(rcWnd);
	m_pDialog->ShowWindow(SW_SHOW);
}



//////////////////////////////////////////////////////////////////////////

// CCharElementMngrDlg

CCharElementMngrDlg::CCharElementMngrDlg()
{

}

CCharElementMngrDlg::~CCharElementMngrDlg()
{
}


