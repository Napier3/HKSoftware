#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"

#include "SttLocalConfigDlg.h"
#include "SttLocalScanConfigDlg.h"
#include "SttRemoteConfigDlg.h"
#include "SttRemoteScanConfigDlg.h"

#include "../../../Module/Engine/SttTestEngineBase.h"

#define STT_TABCTRL_TESTAPPCONFIG	0x000002050

// CSttTestAppConfigDlg 对话框

class CSttTestAppConfigDlg : public CDynDialogEx
{
//	DECLARE_DYNAMIC(CSttTestAppConfigDlg)

public:
	CSttTestAppConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttTestAppConfigDlg();

	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CSttTestAppCfg *m_pSttTestAppCfg;

	void SetConfigDlgUse(BOOL bLocal=TRUE, BOOL bLocalScan=TRUE, BOOL bRemote=TRUE, BOOL bRemoteScan=TRUE)
	{
		m_bSttLocalConfigDlg = bLocal;
		m_bSttLocalScanConfigDlg = bLocalScan;
		m_bSttRemoteConfigDlg = bRemote;
		m_bSttRemoteScanConfigDlg = bRemoteScan;
	}

// 对话框数据
//	enum { IDD = IDD_TESTAPPCONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	CRect m_rcCtrl;
	CMFCTabCtrl m_tabRM;

	//2020-4-28  lijq 在有些场合下，只需要本地测试仪，例如：AT02测试
	CSttLocalConfigDlg *m_pSttLocalConfigDlg;
	CSttLocalScanConfigDlg *m_pSttLocalScanConfigDlg;
	CSttRemoteConfigDlg *m_pSttRemoteConfigDlg;
	CSttRemoteScanConfigDlg *m_pSttRemoteScanConfigDlg;

	BOOL m_bSttLocalConfigDlg;
	BOOL m_bSttLocalScanConfigDlg;
	BOOL m_bSttRemoteConfigDlg;
	BOOL m_bSttRemoteScanConfigDlg;
	long m_nLocalServerPort;

	void CreateChildDynDlg(CDynDialogEx *pDynDlg);

public:
	LRESULT OnTestAppConfigOKMsg(WPARAM wParam,LPARAM lParam);
	LRESULT OnTestAppConfigLockTabMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();

	void ShowAllTabs();
	void ShowSingleFixedTab(int nTab);
};
