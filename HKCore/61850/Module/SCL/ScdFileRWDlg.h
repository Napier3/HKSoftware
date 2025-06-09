#pragma once
#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\..\..\Module\BaseClass\ThreadProgressInterface.h"

#define SCDFILE_RW_TIME     0X00002005
#define SCDFILE_RW_PROGCTRL     0X00002006



class CScdFileRWDlg : public CDynDialogEx, public CThreadProgressInterface
{
public:
	CScdFileRWDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScdFileRWDlg();
	long m_nTimeCout;
public:
	virtual void SetTitle(const CString &strTitle);
	virtual void SetMaxRange(long nMaxRange);
	virtual void ResetProcess();
	virtual void StepIt();
	virtual void ShowMsg(const CString &strMsg);
	virtual void StartTimer(long nTimerLong);
	

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();	
	CProgressCtrl m_prgsScdFileRead;
	CStatic m_stcTime;
protected:
	virtual void OnCancel();
	virtual void OnOK();
};