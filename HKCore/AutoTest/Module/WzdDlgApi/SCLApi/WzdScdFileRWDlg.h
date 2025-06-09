#pragma once
#include "../StepCtrl/WzdDlgProgressCtrl.h"
#include "../../../../Module/DialogBase/DynDialogEx.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"

#define SCDFILE_RW_TIME     0X00002005
#define SCDFILE_RW_PROGCTRL     0X00002006

class CWzdScdFileRWDlg : public CDynDialogEx, public CThreadProgressInterface
{
public:
	CWzdScdFileRWDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzdScdFileRWDlg();
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
	CWzdDlgProgressCtrl m_prgsScdFileRead;
	CStatic m_stcTime;
protected:
	virtual void OnCancel();
	virtual void OnOK();
};