// SttTestAppConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SttTestAppConfigDlg.h"
#include "../../../Module/SttGlobalDef.h"
#include "../SttTestAppConfigTool.h"

// CSttTestAppConfigDlg 对话框

//IMPLEMENT_DYNAMIC(CSttTestAppConfigDlg, CDialog)

CSttTestAppConfigDlg::CSttTestAppConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttTestAppConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_pSttLocalConfigDlg = NULL;
	m_pSttLocalScanConfigDlg = NULL;
	m_pSttRemoteConfigDlg = NULL;
	m_pSttRemoteScanConfigDlg = NULL;

	SetConfigDlgUse();
	m_nLocalServerPort = STT_PORT_TEST_SERVER;

	m_pSttTestAppConfigTool = NULL;
	m_pSttTestAppCfg = NULL;

}

CSttTestAppConfigDlg::~CSttTestAppConfigDlg()
{
	if (m_pSttLocalConfigDlg != NULL)
	{
		delete m_pSttLocalConfigDlg;
	}

	if (m_pSttLocalScanConfigDlg != NULL)
	{
		delete m_pSttLocalScanConfigDlg;
	}

	if (m_pSttRemoteConfigDlg != NULL)
	{
		delete m_pSttRemoteConfigDlg;
	}

	if (m_pSttRemoteScanConfigDlg != NULL)
	{
		delete m_pSttRemoteScanConfigDlg;
	}
}

void CSttTestAppConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSttTestAppConfigDlg, CDynDialogEx)
	ON_WM_CLOSE()
	ON_MESSAGE(TESTAPPCONFIG_OK_MSG, &CSttTestAppConfigDlg::OnTestAppConfigOKMsg)
	ON_MESSAGE(TESTAPPCONFIG_LOCKTAB_MSG, &CSttTestAppConfigDlg::OnTestAppConfigLockTabMsg)
END_MESSAGE_MAP()


// CSttTestAppConfigDlg 消息处理程序

BOOL CSttTestAppConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CreateMFCTabCtrl(m_tabRM, CRect(0,0,650,300), STT_TABCTRL_TESTAPPCONFIG,this,CMFCTabCtrl::STYLE_3D_ROUNDED,CMFCTabCtrl::LOCATION_TOP);

	if (m_bSttLocalConfigDlg)
	{
		m_pSttLocalConfigDlg = new CSttLocalConfigDlg();
		m_pSttLocalConfigDlg->m_pSttTestAppConfigTool = m_pSttTestAppConfigTool;
		m_pSttLocalConfigDlg->m_pSttTestAppCfg = m_pSttTestAppCfg;

		if (m_pSttTestAppConfigTool->m_strServerID == STT_SOFT_ID_ATS)
		{
			m_pSttLocalConfigDlg->m_nSvrPort = m_pSttTestAppCfg->GetNativeServerPort();
		}
		else
		{
			m_pSttLocalConfigDlg->m_nSvrPort = m_pSttTestAppCfg->GetTestServerPort();
		}

		CreateChildDynDlg(m_pSttLocalConfigDlg);
		m_tabRM.AddTab(m_pSttLocalConfigDlg, _T("测试仪配置"));
	}

	if (m_bSttLocalScanConfigDlg)
	{
		m_pSttLocalScanConfigDlg = new CSttLocalScanConfigDlg();
		m_pSttLocalScanConfigDlg->m_pSttTestAppConfigTool = m_pSttTestAppConfigTool;
		m_pSttLocalScanConfigDlg->m_pSttTestAppCfg = m_pSttTestAppCfg;

		if (m_pSttTestAppConfigTool->m_strServerID == STT_SOFT_ID_ATS)
		{
			m_pSttLocalScanConfigDlg->m_nSvrPort = m_pSttTestAppCfg->GetNativeServerPort();
		}
		else
		{
			m_pSttLocalScanConfigDlg->m_nSvrPort = m_pSttTestAppCfg->GetTestServerPort();
		}
		
		CreateChildDynDlg(m_pSttLocalScanConfigDlg);
		m_tabRM.AddTab(m_pSttLocalScanConfigDlg, _T("扫描局域网测试仪"));
	}

	if (m_bSttRemoteConfigDlg)
	{
		m_pSttRemoteConfigDlg = new CSttRemoteConfigDlg();
		m_pSttRemoteConfigDlg->m_pSttTestAppConfigTool = m_pSttTestAppConfigTool;
		m_pSttRemoteConfigDlg->m_pSttTestAppCfg = m_pSttTestAppCfg;
		CreateChildDynDlg(m_pSttRemoteConfigDlg);
		m_tabRM.AddTab(m_pSttRemoteConfigDlg, _T("直接配置远程测试仪"));
	}

	if (m_bSttRemoteScanConfigDlg)
	{
		m_pSttRemoteScanConfigDlg = new CSttRemoteScanConfigDlg();
		m_pSttRemoteScanConfigDlg->m_pSttTestAppConfigTool = m_pSttTestAppConfigTool;
		m_pSttRemoteScanConfigDlg->m_pSttTestAppCfg = m_pSttTestAppCfg;
		CreateChildDynDlg(m_pSttRemoteScanConfigDlg);
		m_tabRM.AddTab(m_pSttRemoteScanConfigDlg, _T("扫描远程测试仪"));
	}

	MoveWindow(CRect( 0, 0, 650, 300), TRUE);
	CenterWindow();
	SetWindowText(_T("测试仪配置"));

	return TRUE;
}

void CSttTestAppConfigDlg::CreateChildDynDlg(CDynDialogEx *pDynDlg)
{
	pDynDlg->SetUseModeless(TRUE);
	pDynDlg->DoModal();
	pDynDlg->ModifyStyle(WS_VISIBLE | WS_POPUP | WS_CAPTION | WS_SYSMENU, WS_CHILD , 0);	
	pDynDlg->SetParent(&m_tabRM);
}


//lParam=0/1/2/3:不同
LRESULT CSttTestAppConfigDlg::OnTestAppConfigOKMsg(WPARAM wParam,LPARAM lParam)
{
	if (wParam == IDOK)
	{
		CDynDialogEx::OnOK();
	}
	else
	{//取消，则销毁临时创建的对象
		m_pSttTestAppConfigTool->FreeClientEngine();
		CDynDialogEx::OnCancel();
	}

	return 0;
}

//lParam=0/1/2/3:锁住指定tab,ff：显示所有tab
LRESULT CSttTestAppConfigDlg::OnTestAppConfigLockTabMsg(WPARAM wParam,LPARAM lParam)
{
	int nTab = (int)lParam;

	if (nTab == STT_REMOTESCANCONFIG_DLG_ALLINDEX)
	{
		ShowAllTabs();
	}
	else
	{
		ShowSingleFixedTab(nTab);
	}

	return 0;
}

void CSttTestAppConfigDlg::ShowAllTabs()
{
	int nCnt = m_tabRM.GetTabsNum();

	for (int i=0; i<nCnt; i++)
	{
		m_tabRM.ShowTab(i,TRUE);
	}
}

void CSttTestAppConfigDlg::ShowSingleFixedTab(int nTab)
{
	int nCnt = m_tabRM.GetTabsNum();

	for (int i=0; i<nCnt; i++)
	{
		if (i == nTab)
		{
			continue;
		}
		m_tabRM.ShowTab(i,FALSE);
	}
}

void CSttTestAppConfigDlg::OnClose()
{//配置未完成结束

	CDynDialogEx::OnClose();
}