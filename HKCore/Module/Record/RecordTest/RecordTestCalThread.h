#if !defined(AFX_RecordTestCalThread_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_)
#define AFX_RecordTestCalThread_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordTestCalThread.h : header file
//
#include "RecordTest.h"
//#define WM_BEGIN_CALVALUES  WM_USER + 1010 

extern long g_nRecordTestCalState;
extern long g_nRecordTestCalCount;

/////////////////////////////////////////////////////////////////////////////
// CRecordTestCalThread thread
//参数计算线程，优先级仅次于主线程
class CRecordTestCalThread : public CWinThread
{
#ifndef _PSX_IDE_QT_
	DECLARE_DYNCREATE(CRecordTestCalThread)
#endif

protected:
	CRecordTestCalThread();           // protected constructor used by dynamic creation

public:
	static CRecordTestCalThread* CreateRecordTestCalThread()
	{
		CRecordTestCalThread* pCalThread = NULL;

#ifndef _PSX_IDE_QT_
		pCalThread = (CRecordTestCalThread*)AfxBeginThread(RUNTIME_CLASS(CRecordTestCalThread));
		pCalThread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
		return pCalThread;
#else
		pCalThread = new CRecordTestCalThread();
		pCalThread->start();
		return pCalThread;
#endif
	}

	static long g_nRecordTestCalThreadRefCount;
	static BOOL WaitExit()
	{
		return (g_nRecordTestCalThreadRefCount == 0);
	}

	void Exit()
	{
		PostThreadMessage(WM_QUIT, 0, 0);
	}

public:
	//重载函数OnWndMsg，实现消息处理
	virtual void OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);


// Attributes
public:
	CRecordTest *m_pRecordTest;
	BOOL m_bIsInCalState;

// Operations
public:
	void OnReceiveData();
	void SetRecordTest(CRecordTest *pRecordTest);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordTestCalThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRecordTestCalThread();

	//消息处理函数
	void OnCalValues(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CRecordTestCalThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

#ifndef _PSX_IDE_QT_
	DECLARE_MESSAGE_MAP()
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RecordTestCalThread_H__52C1CDFA_18A9_48FA_B5B2_D4CB54C4B201__INCLUDED_)
