#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"

#include "../SttTestAppConfigTool.h"

#define STT_STC_CLOUDIP		0x000002030
#define STT_EDIT_CLOUDIP	0x000002031
#define STT_STC_CLOUDPORT	0x000002032
#define STT_EDIT_CLOUDPORT	0x000002033
#define STT_BTN_CONNECT		0x000002034

#define STT_STC_SN			0x000002035
#define STT_EDIT_SN			0x000002036
#define STT_STC_PASSWORD	0x000002037
#define STT_EDIT_PASSWORD	0x000002038

#define STT_STC_COP			0x000002039
#define STT_EDIT_COP		0x00000203a
#define STT_STC_USER		0x00000203b
#define STT_EDIT_USER		0x00000203c

#define STT_BTN_BIND		0x00000203d
#define STT_BTN_CANCEL_2	0x00000203e




// CSttRemoteConfigDlg 对话框

class CSttRemoteConfigDlg : public CDynDialogEx
{
//	DECLARE_DYNAMIC(CSttRemoteConfigDlg)

public:
	CSttRemoteConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttRemoteConfigDlg();

	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CSttTestAppCfg *m_pSttTestAppCfg;
	CFont *m_pGlobalFont11;

// 对话框数据
//	enum { IDD = IDD_TESTAPPCONFIG_REMOTECONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickConnect();
	afx_msg void OnBtnClickBind();
	afx_msg void OnBtnClickCancel();

	afx_msg void OnEnChangeEditCloudport();
	afx_msg void OnEnChangeEditSN();
	afx_msg void OnEnChangeEditPassword();
	afx_msg void OnEnChangeEditCop();
	afx_msg void OnEnChangeEditUser();

public:
	BOOL m_bConnect;
	void EnableButtons();

	CStatic m_stcCloudIP;
	CIPAddressCtrl m_ctrlCloudIP;
	CStatic m_stcCloudPort;
	CEdit m_edtCloudPort;
	CButton m_btnConnect;

	CStatic m_stcSN;
	CEdit m_edtSN;
	CStatic m_stcPassword;
	CEdit m_edtPassword;

	CStatic m_stcCompany;
	CEdit m_editCompany;
	CStatic m_stcUser;
	CEdit m_edtUser;

	CButton m_btnBind;
	CButton m_btnCancel;
};
