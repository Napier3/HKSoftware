#pragma once

#include "../../../../Module/DialogBase/DynDialogEx.h"
#include "afxcmn.h"
#include "afxwin.h"

#define VmSttMacroTestSpyDlg_Timer_ID  25
#define VmSttMacroTestSpyDlg_Timer_Long  500

class CVmSttMacroTestSpyDlg : public CDynDialogEx
{
public:
	CVmSttMacroTestSpyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVmSttMacroTestSpyDlg();

	void ShowSpy(long nTotalTimeLong);
	void HideSpy();
	
private:
	CProgressCtrl m_wndPrgs;
	CStatic m_wndTimerText;
	double m_fTimerLong;
	UINT m_nCurrTimerID;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnCancel();
	virtual void OnOK();
};
