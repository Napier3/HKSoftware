#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\Grid\RemoteScan_TestAppGrid.h"
#include "../SttTestAppConfigTool.h"

#define STT_STC_CLOUDIP_1		0x000002040
#define STT_EDIT_CLOUDIP_1		0x000002041
#define STT_STC_CLOUDPORT_1		0x000002042
#define STT_EDIT_CLOUDPORT_1	0x000002043
#define STT_BTN_CONNECT_1		0x000002044
#define STT_BTN_REMOTEQUERY		0x000002045

#define STT_STC_REMOTECOP		0x000002046
#define STT_EDIT_REMOTECOP		0x000002047
#define STT_STC_REMOTEUSER		0x000002048
#define STT_EDIT_REMOTEUSER		0x000002049

#define STT_BTN_REMOTECANCEL	0x00000204a
#define STT_BTN_REMOTEBIND		0x00000204b


#define STT_GRID_REMOTETESTAPP	0x000002047

// CSttRemoteScanConfigDlg 对话框

class CSttRemoteScanConfigDlg : public CDynDialogEx, public CExBaseListGridOptrInterface
{
//	DECLARE_DYNAMIC(CSttRemoteScanConfigDlg)

public:
	CSttRemoteScanConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttRemoteScanConfigDlg();

	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CSttTestAppCfg *m_pSttTestAppCfg;
	CFont *m_pGlobalFont11;

// 对话框数据
//	enum { IDD = IDD_TESTAPPCONFIG_REMOTESERACJH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar){return TRUE;}
public:
	CRemoteScan_TestAppGrid m_grid;
	afx_msg void OnBtnClickConnect();
	afx_msg void OnBtnClickQuery();
	afx_msg void OnBtnClickCancel();
	afx_msg void OnBtnClickBind();

	afx_msg void OnEnChangeEditCloudport();
	afx_msg void OnEnChangeEditCop();
	afx_msg void OnEnChangeEditUser();
public:
	BOOL m_bConnect;
	void EnableButtons();
//	long m_nSvrPort;

	CStatic m_stcCloudIP;
	CIPAddressCtrl m_ctrlCloudIP;
	CStatic m_stcCloudPort;
	CEdit m_edtCloudPort;
	CButton m_btnConnect;
	CButton m_btnQuery;

	CStatic m_stcCompany;
	CEdit m_editCompany;
	CStatic m_stcUser;
	CEdit m_edtUser;

	CButton m_btnBind;
	CButton m_btnCancel;
};
