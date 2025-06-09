// WndMsgRegisterMngr.h: interface for the CWndMsgRegisterMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WNDMSGREGISTERMNGR_H__)
#define _WNDMSGREGISTERMNGR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "TLinkList.h"

class CWndMsgRegisterMngr;

class CWndMsgRegister : public CExBaseObject
{
public:
	CWndMsgRegister();
	CWndMsgRegister(CWnd *pWndRcvMsg, UINT  nMsg, WPARAM wParam, LPARAM lParam);
	virtual ~CWndMsgRegister();
	
public:
	void PostMsg(WPARAM wParam, LPARAM lParam);
	void PostMsg();
	void SendMsg(WPARAM wParam, LPARAM lParam);
	void SendMsg();

protected:
	CWnd *m_pWndRcvMsg;
	UINT  m_nMsg;
	WPARAM m_wParam;
	LPARAM m_lParam;
	
	friend class CWndMsgRegisterMngr;
};

class CWndMsgRegisterMngr : public CExBaseList
{
public:
	CWndMsgRegisterMngr();
	virtual ~CWndMsgRegisterMngr();

public:
//属性定义

//方法
public:
	CWndMsgRegister* Register(CWnd *pWndRcvMsg, UINT  nMsg, WPARAM wParam=0, LPARAM lParam=0, const CString &strID=_T(""));
	void PostMsg(const CString &strID, WPARAM wParam, LPARAM lParam);
	void PostMsg(const CString &strID);
	void PostMsg(CWnd *pWnd, WPARAM wParam, LPARAM lParam);
	void PostMsg(CWnd *pWnd);
	void PostMsg(UINT  nMsg, WPARAM wParam, LPARAM lParam);
	void PostMsg(UINT  nMsg);
	
	void SendMsg(const CString &strID, WPARAM wParam, LPARAM lParam);
	void SendMsg(const CString &strID);
	void SendMsg(CWnd *pWnd, WPARAM wParam, LPARAM lParam);
	void SendMsg(CWnd *pWnd);
	void SendMsg(UINT  nMsg, WPARAM wParam, LPARAM lParam);
	void SendMsg(UINT  nMsg);
	
protected:
	
};

#endif // !defined(_WNDMSGREGISTERMNGR_H__)
