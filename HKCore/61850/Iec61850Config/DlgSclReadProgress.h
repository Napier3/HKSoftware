#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "..\..\Module\BaseClass\ThreadProgressInterface.h"

// CDlgSclReadProgress �Ի���

class CDlgSclReadProgress : public CDialog, public CThreadProgressInterface
{
	DECLARE_DYNAMIC(CDlgSclReadProgress)

public:
	virtual void SetTitle(const CString &strTitle);
	virtual void SetMaxRange(long nMaxRange);
	virtual void ResetProcess();
	virtual void StepIt();
	virtual void ShowMsg(const CString &strMsg);
	virtual void StartTimer(long nTimerLong);

public:
	CDlgSclReadProgress(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSclReadProgress();
	long m_nTimeCout;

// �Ի�������
	enum { IDD = IDD_DLG_SCL_READ_PROGRESS };
	void xlang_InitAndAdjust(); 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CProgressCtrl m_prgsSclRead;
	CStatic m_stcTime;
protected:
	virtual void OnCancel();
	virtual void OnOK();
};
