#if !defined(AFX_SMDBWRITETHREAD_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_)
#define AFX_SMDBWRITETHREAD_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmDbWriteThread.h : header file
//

#include "CapFrameDbFile.h"
#include "..\CapGlobalDef.h"

/////////////////////////////////////////////////////////////////////////////
// CSmDbWriteThread thread

class CSmDbWriteThread : public CWinThread
{
	DECLARE_DYNCREATE(CSmDbWriteThread)
	
protected:
	CSmDbWriteThread();           // protected constructor used by dynamic creation
	long m_nExitState;

public:
	static long g_nSmDbWriteThreadRefCount;

	static CSmDbWriteThread* CreateSmDbWriteThread()
	{
		return (CSmDbWriteThread*)AfxBeginThread(RUNTIME_CLASS(CSmDbWriteThread));
	}
	
	BOOL WaitForExit()
	{
		return (g_nSmDbWriteThreadRefCount == 0);
	}
	
	BOOL Exit()
	{
		if (IsNowOnlineWrite())
		{
			return FALSE;
		}

		if (m_nExitState == 0)
		{
			m_nExitState = 1;
			PostThreadMessage(WM_CAP_WRITE_SMDB, 0, 0);
		}
		else if (m_nExitState == 1)
		{
			PostThreadMessage(WM_QUIT, 0, 0);
		}

		return TRUE;
	}

	void InitThread(CFrameMemBufferMngr *pCapThreadMngr, CCapFrameDbFile *pCapSmDbFile)
	{
		m_pFrameMemBufferMngr = pCapThreadMngr;
		m_pCapSmDbFile = pCapSmDbFile;
	}

	void FreeThread();

// Attribut
private:
	UINT m_nWriteTimerID;
	BOOL m_bIsNowWritting;
	BOOL m_bIsInWrittingLastData;

	//互斥区域
	CAutoCriticSection m_oSection;
	CFrameMemBufferMngr *m_pFrameMemBufferMngr;
	CCapFrameDbFile *m_pCapSmDbFile;
	

private:
	BOOL CanWriteNow();

// Operations
public:
	BOOL IsNowOnlineWrite()  {   return m_bIsNowWritting;	}
	void WriteSmDB();
	BOOL WriteSmDBEx();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmDbWriteThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSmDbWriteThread();
	BOOL EmptyInfoShareMem();

	// Generated message map functions
	//{{AFX_MSG(CSmDbWriteThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	//消息处理函数
	void OnWriteSmDb(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(WPARAM wParam, LPARAM lParam);	

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMDBWRITETHREAD_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_)





















