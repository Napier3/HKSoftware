#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"
#include "../SttTestAppConfigTool.h"

#define STT_STC_TESTAPPTYPE		0x000002010
#define STT_EDIT_TESTAPPTYPE	0x000002011
#define STT_STC_TESTAPPIP		0x000002012
#define STT_EDIT_TESTAPPIP		0x000002013
#define STT_BTN_OK				0x000002014
#define STT_BTN_CANCEL			0x000002015

// CSttLocalConfigDlg 对话框

class CSttLocalConfigDlg : public CDynDialogEx
{
//	DECLARE_DYNAMIC(CSttLocalConfigDlg)

public:
	CSttLocalConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttLocalConfigDlg();

	CFont *m_pGlobalFont11;
	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CSttTestAppCfg *m_pSttTestAppCfg;
// 对话框数据
//	enum { IDD = IDD_TESTAPPCONFIG_LOCALCONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickOK();
	afx_msg void OnBtnClickCancel();

public:
	CStatic m_stcIP;
	CIPAddressCtrl m_ctrlIP;
	CButton m_btnOK;
	CButton m_btnCancel;

	long m_nSvrPort;
};
