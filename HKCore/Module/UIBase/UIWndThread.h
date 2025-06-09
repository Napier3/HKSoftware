#if !defined(AFX_UIWNDTHREAD_H__492A915F_2A91_4C11_8057_25398860070A__INCLUDED_)
#define AFX_UIWNDTHREAD_H__492A915F_2A91_4C11_8057_25398860070A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UIWndThread.h : header file
//
#include "UIWndMain.h"
//#define WM_BEGINDRAWPAGES  WM_USER + 4000

/////////////////////////////////////////////////////////////////////////////
// CUIWndThread thread

class CUIWndThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIWndThread)
protected:
	CUIWndThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CUIWndMain        *m_pUIWndPages;
	CWnd              *m_pProcMainWnd;
// 	CSystemMessageMngr* m_pSystemMessageMngr;

// Operations
private:	
	//静态成员
	static long g_nCUIWndThreadRefCount;
	static CUIWndThread *g_pUIWndThread;
	static CWnd *g_pWnd_WM_COMMAND;

public:
	static BOOL WaitExit()
	{
		return (g_nCUIWndThreadRefCount == 0);
	}

	static CUIWndThread* CreateUIWndThread()
	{
		if (g_pUIWndThread != NULL)
		{
			return g_pUIWndThread;
		}
		else
		{
			g_pUIWndThread = (CUIWndThread*)AfxBeginThread(RUNTIME_CLASS(CUIWndThread));
			return g_pUIWndThread;
		}
	}

	static CUIWndPage* FindPage(const char *pszPage);
	static BOOL ShowPage(LPCTSTR pszPageID, long nShow);
	static BOOL ClosePage(LPCTSTR pszPageID);

	static CUIWndPage* FindPage(const CString &strPage);
	static BOOL ShowPage(const CString &strPageID, long nShow);
	static BOOL ClosePage(const CString &strPageID);
	static void Attach_Wnd_WM_COMMAND(CWnd *pWnd)	{	g_pWnd_WM_COMMAND = pWnd;	}
	static void PostProcMainWndMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);
	static void Attach_ProcMainWnd(CWnd *pWnd)	{	g_pUIWndThread->m_pProcMainWnd = pWnd;	}
	static CWnd* Get_ProcMainWnd()				{	return g_pUIWndThread->m_pProcMainWnd;	}

public:
	void Exit()
	{
		PostThreadMessage(WM_QUIT, 0, 0);
	}

	BOOL TranslateMessage(MSG* pMsg);
	UINT  m_nTimerID;
	void FireAdStartButtonMsg();
	long m_nCanDeletePageRef;

	DWORD m_dwAnalyseWndCreate;
	UINT  m_nDeletePageTimerID;
	CUIWndPage *m_pDeletePage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIWndThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUIWndThread();	

	// Generated message map functions
	//{{AFX_MSG(CUIWndThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	//消息处理函数
	LRESULT OnPageSysMessagees(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeletePage(WPARAM, LPARAM);
	LRESULT OnRecord(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIWNDTHREAD_H__492A915F_2A91_4C11_8057_25398860070A__INCLUDED_)
