#pragma once
#include "afxcmn.h"
#include "..\BaseClass\ThreadProgressInterface.h"
#include "..\DialogBase\DynDialogEx.h"

// CThreadProgrssDlg dialog

#define XIDC_PROGRESS_CTRL  2120
#define XIDC_STATIC_TITLE   2121

class CThreadProgrssDlg : public CDynDialogEx, public CThreadProgressInterface
{
public:
	virtual void SetMaxRange(long nMaxRange)
	{
		m_ProgressCtrl.SetStep(1);
		m_ProgressCtrl.SetRange32(0, nMaxRange);
		m_ProgressCtrl.SetPos(0);
	}

	virtual void ResetProcess()
	{
		m_ProgressCtrl.SetPos(0);
	}
	virtual void StepIt()
	{
		m_ProgressCtrl.StepIt();
	}

	virtual void StepPos(long nPos)
	{
		m_ProgressCtrl.SetPos(nPos);
	}

	void CreateThreadDlg(CWnd *pParent, const CString &strTitle)
	{
		SetUseModeless();
		DoModal();
	}

	void SetTitle(const CString &strTitle)
	{
		//CRect rcWnd;
		//GetWindowRect(rcWnd);
		//SetWindowPos(&wndTopMost, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_SHOWWINDOW);
		SetWindowText(strTitle);
	}
	void ShowMsg(const CString &strMsg)
	{
		m_stcTitle.SetWindowText(strMsg);
	}


	void StartTimer(long nTimerLong)
	{

	}

	void StartProgress();
	int DoModal();

public:
	CThreadProgrssDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CThreadProgrssDlg();

// Dialog Data
	CProgressCtrl m_ProgressCtrl;
	CStatic m_stcTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};


class CThreadProgressBase : public CWinThread, public CThreadProgressInterface
{
	DECLARE_DYNCREATE(CThreadProgressBase)

public:
	virtual void SetMaxRange(long nMaxRange)
	{
		m_nStepIndex = 0;
		m_nMaxRange = nMaxRange;
		PostThreadMessage(WM_USER + 2355, nMaxRange, nMaxRange);
	}
	virtual void ResetProcess()
	{
		m_nStepIndex = 0;
		PostThreadMessage(WM_USER + 2356, 0, 0);
	}
	virtual void StepIt()
	{
		m_nStepIndex++;
		PostThreadMessage(WM_USER + 2357, 0, 0);
	}

	virtual void ShowMsg(const CString &strMsg)
	{
		CString_to_char(strMsg, m_pszMessage);
		PostThreadMessage(WM_USER + 2358, 0, 0);
	}

	virtual void Exit()
	{
		PostThreadMessage(WM_QUIT, 0, 0);
	}

	void StartTimer(long nTimerLong)
	{

	}

	BOOL IsThreadCreated()	{	return m_pProgressDlg != NULL;}

protected:
	CThreadProgressBase();           // protected constructor used by dynamic creation

	CThreadProgrssDlg *m_pProgressDlg;
	char m_pszMessage[4096];
	long m_nMaxRange;
	CWnd *m_pParentWnd;
	long m_nStepIndex;

public:
	static CThreadProgressBase* CreateTestCtrlThread(CWnd *pWnd)
	{
		CThreadProgressBase* pThread = (CThreadProgressBase*)AfxBeginThread(RUNTIME_CLASS(CThreadProgressBase));
		pThread->m_bAutoDelete = TRUE;
		pThread->ResumeThread();
		pThread->m_pParentWnd = pWnd;
		return pThread;
	}

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CThreadProgressBase();


	// Generated message map functions
	//{{AFX_MSG(CTestWorkThread)
	afx_msg void On2355(WPARAM wParam, LPARAM lParam);
	afx_msg void On2356(WPARAM wParam, LPARAM lParam);
	afx_msg void On2357(WPARAM wParam, LPARAM lParam);
	afx_msg void On2358(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};