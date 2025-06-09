#pragma once

#include "UITestGlobalDefine.h"
#include "CommCmdAttrGrid.h"
// CUICommCmdViewDlg 对话框

#define TIMER_COMMMESSAGE    1107

#ifdef _UITEST_USE_DIALOGEX
#include "..\..\..\Module\DialogBase\DynDialogEx.h"
class CUICommCmdViewDlg : public CDynDialogEx
#else
class CUICommCmdViewDlg : public CDialog
#endif
{
#ifdef _UITEST_USE_DIALOGEX
#else
	DECLARE_DYNAMIC(CUICommCmdViewDlg)
#endif

public:
	CUICommCmdViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUICommCmdViewDlg();
	CWnd *m_pTestCtrlWndRef;
	UINT m_nIDEvent;

// 对话框数据
	//enum { IDD = IDD_DLG_SYSPARAS };

private:
	CCommCmd* m_pTestItemCommCmd;
	CCommCmdAttrGrid m_gridAttr;
	CStatic m_wndTimerText;
	CString m_strCmdMessage;
	long m_nTimerLong;
	CString m_strGuideBookTitle;
	BOOL m_bEnterTimeTrigger;

public:
	void InitTestItem(CCommCmd* pTestItemCommCmd, const CString &strTitle);
	void InitTestItem(long nMaxCount, long nCurrIndex, long nTimerLong);
	void ShowCommMessage(const CString &strMsg, BOOL bCreateTimer);
	void ShowCommViewDlg(DWORD dwShow);
	void Gbs_EnterTimeTrigger();
	CString GetTimerString();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
