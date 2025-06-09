#pragma once

#include "../DialogBase/DynDialogEx.h"
#include "XSafenetXUser.h"
// CXSafenetXUserDlg 对话框

#define XSAFENET_XUSER_TCPCLIENT_TIMER_ID    2117
#define XSAFENET_XUSER_TCPCLIENT_TIMER_LONG  200

#define XSAFENET_XUSER_OVERTIMER_ID    2118
#define XSAFENET_XUSER_OVERTIMER_LONG  5000

class CXSafenetXUserDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXSafenetXUserDlg)

public:
	CXSafenetXUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXSafenetXUserDlg();

	CSafenet_XUser *m_pSafenet_XUser;
	DWORD m_dwCurrXUserCmd;

public:
	//virtual int DoModal(); 

// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditDestName();
	CEdit m_edtInfor;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	HRESULT OnXUserCmdResult(WPARAM wParam, LPARAM lParam);

};
