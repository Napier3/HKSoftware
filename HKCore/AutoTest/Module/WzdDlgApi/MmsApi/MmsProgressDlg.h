#pragma once
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"
#include "../../../../Module/XLanguage/XLanguageTextWnd.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/WzdDlgProgressCtrl.h"

#define PRGSS_TIMER_ID  127

class COutputList : public CEdit, public CLogBase
{
	// 构造
public:
	COutputList();

	virtual void LogString(long nLevel, const char *strMsg);
	virtual void LogString(long nLevel, const CString &strMsg);

	// 实现
public:
	virtual ~COutputList();

protected:
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();

	DECLARE_MESSAGE_MAP()
};


class CMmsProgressDlg : public CDialogEx, public CThreadProgressInterface
{
	DECLARE_DYNAMIC(CMmsProgressDlg)
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
	virtual void StartTimer(long nTimerLong);

	void CreateThreadDlg(CWnd *pParent, const CString &strTitle)
	{
		Create(IDD_DIALOG_PROGRESS, pParent);
		SetTitle(strTitle);
	}

	void SetTitle(const CString &strTitle)
	{
		//CRect rcWnd;
		//GetWindowRect(rcWnd);
		//SetWindowPos(&wndTopMost, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_SHOWWINDOW);
		SetWindowText(strTitle);
		m_stcTimer.SetWindowText(_T(""));
	}
	void ShowMsg(const CString &strMsg)
	{
		m_stcTitle.SetWindowText(strMsg);
	}

	void StartProgress();
	long m_iTimerLongTotal;
	long m_iTimerLongCounter;

public:
	CMmsProgressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMmsProgressDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_PROGRESS };
	CWzdDlgProgressCtrl m_ProgressCtrl;
	CXLanguageTextWnd m_stcTitle;
	void xlang_InitAndAdjust(); 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CStatic m_stcTimer;
	COutputList m_editLog;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
