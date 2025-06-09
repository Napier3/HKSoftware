// WndMsgRegisterMngr.cpp: implementation of the CWndMsgRegisterMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WndMsgRegisterMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndMsgRegister::CWndMsgRegister()
{
	m_pWndRcvMsg = NULL;
	m_nMsg = NULL;
	m_wParam = NULL;
	m_lParam = NULL;
}

CWndMsgRegister::CWndMsgRegister(CWnd *pWndRcvMsg, UINT  nMsg, WPARAM wParam, LPARAM lParam)
{
	m_pWndRcvMsg = pWndRcvMsg;
	m_nMsg = nMsg;
	m_wParam = wParam;
	m_lParam = lParam;
}
CWndMsgRegister::~CWndMsgRegister()
{

}

void CWndMsgRegister::PostMsg(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pWndRcvMsg != NULL);

	if (::IsWindow(m_pWndRcvMsg->m_hWnd))
	{
		m_pWndRcvMsg->PostMessage(m_nMsg, wParam, lParam);
	}
}

void CWndMsgRegister::PostMsg()
{
	PostMsg(m_wParam, m_lParam);
}

void CWndMsgRegister::SendMsg(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pWndRcvMsg != NULL);

	if (::IsWindow(m_pWndRcvMsg->m_hWnd))
	{
		m_pWndRcvMsg->SendMessage(m_nMsg, wParam, lParam);
	}
}

void CWndMsgRegister::SendMsg()
{
	SendMsg(m_wParam, m_lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndMsgRegisterMngr::CWndMsgRegisterMngr()
{

}

CWndMsgRegisterMngr::~CWndMsgRegisterMngr()
{
	
}

CWndMsgRegister* CWndMsgRegisterMngr::Register(CWnd *pWndRcvMsg, UINT  nMsg, WPARAM wParam, LPARAM lParam, const CString &strID)
{
	CWndMsgRegister *pWndMsg = new CWndMsgRegister(pWndRcvMsg, nMsg, wParam, lParam);
	SetParent(this);
	AddTail(pWndMsg);
	return pWndMsg;
}


void CWndMsgRegisterMngr::PostMsg(const CString &strID, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_strID == strID)
		{
			pWndMsg->PostMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::PostMsg(const CString &strID)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_strID == strID)
		{
			pWndMsg->PostMsg();
		}
	}
}


void CWndMsgRegisterMngr::PostMsg(CWnd *pWnd, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_pWndRcvMsg == pWnd)
		{
			pWndMsg->PostMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::PostMsg(CWnd *pWnd)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_pWndRcvMsg == pWnd)
		{
			pWndMsg->PostMsg();
		}
	}
}

void CWndMsgRegisterMngr::PostMsg(UINT  nMsg, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_nMsg == nMsg)
		{
			pWndMsg->PostMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::PostMsg(UINT  nMsg)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_nMsg == nMsg)
		{
			pWndMsg->PostMsg();
		}
	}
}

void CWndMsgRegisterMngr::SendMsg(const CString &strID, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_strID == strID)
		{
			pWndMsg->SendMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::SendMsg(const CString &strID)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_strID == strID)
		{
			pWndMsg->SendMsg();
		}
	}
}


void CWndMsgRegisterMngr::SendMsg(CWnd *pWnd, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_pWndRcvMsg == pWnd)
		{
			pWndMsg->SendMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::SendMsg(CWnd *pWnd)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_pWndRcvMsg == pWnd)
		{
			pWndMsg->SendMsg();
		}
	}
}

void CWndMsgRegisterMngr::SendMsg(UINT  nMsg, WPARAM wParam, LPARAM lParam)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_nMsg == nMsg)
		{
			pWndMsg->SendMsg(wParam, lParam);
		}
	}
}

void CWndMsgRegisterMngr::SendMsg(UINT  nMsg)
{
	POS pos = GetHeadPosition();
	CWndMsgRegister *pWndMsg = NULL;

	while (pos != NULL)
	{
		pWndMsg = (CWndMsgRegister*)GetNext(pos);

		if (pWndMsg->m_nMsg == nMsg)
		{
			pWndMsg->SendMsg();
		}
	}
}
