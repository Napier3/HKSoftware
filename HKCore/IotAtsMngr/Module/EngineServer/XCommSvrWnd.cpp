//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "XCommSvrWnd.h"

CXCommSvrWnd::CXCommSvrWnd()
{
	m_pInterfaceRef = NULL;
}

CXCommSvrWnd::~CXCommSvrWnd()
{
}

void CXCommSvrWnd::CreateXCommSvrWnd(CXCommSvrWndInterface *pInterface)
{
	static int nIndex = 0;
	CString strWndID;
	strWndID.Format(_T("_XComm_Svr_Wnd_%d"),nIndex++);

	m_pInterfaceRef = pInterface;

	CreateEx(0, AfxRegisterWndClass(0), strWndID, WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
}


BEGIN_MESSAGE_MAP(CXCommSvrWnd, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(XCOMM_WND_MSG, &CXCommSvrWnd::OnXCommMsg)
END_MESSAGE_MAP()


LRESULT CXCommSvrWnd::OnXCommMsg(WPARAM wParam, LPARAM lParam)
{
	if (m_pInterfaceRef != NULL)
	{
		m_pInterfaceRef->OnXCommMsg(wParam,lParam);
	}

	return 0;
}

void CXCommSvrWnd::OnTimer(UINT nIDEvent)
{
	if (m_pInterfaceRef != NULL)
	{
		m_pInterfaceRef->OnXTimer(nIDEvent);
	}	
}