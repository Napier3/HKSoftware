// TestAppConfigRemoteSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SttRemoteScanConfigDlg.h"
#include "../SttTestAppConfigTool.h"

// CSttRemoteScanConfigDlg 对话框

//IMPLEMENT_DYNAMIC(CSttRemoteScanConfigDlg, CDialog)

CSttRemoteScanConfigDlg::CSttRemoteScanConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttRemoteScanConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_bConnect = FALSE;
	m_pSttTestAppConfigTool = NULL;
	m_pSttTestAppCfg = NULL;
	m_pGlobalFont11 = font_CreateNew(g_lfGlobalFont11, -11);
}

CSttRemoteScanConfigDlg::~CSttRemoteScanConfigDlg()
{
	if (m_pGlobalFont11 != NULL)
	{
		delete m_pGlobalFont11;
	}
}

void CSttRemoteScanConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSttRemoteScanConfigDlg, CDynDialogEx)
	ON_BN_CLICKED(STT_BTN_REMOTEBIND, &CSttRemoteScanConfigDlg::OnBtnClickBind)
	ON_BN_CLICKED(STT_BTN_REMOTEQUERY, &CSttRemoteScanConfigDlg::OnBtnClickQuery)
	ON_BN_CLICKED(STT_BTN_CONNECT_1, &CSttRemoteScanConfigDlg::OnBtnClickConnect)
	ON_BN_CLICKED(STT_BTN_REMOTECANCEL, &CSttRemoteScanConfigDlg::OnBtnClickCancel)

	ON_EN_CHANGE(STT_EDIT_CLOUDPORT_1, &CSttRemoteScanConfigDlg::OnEnChangeEditCloudport)
	ON_EN_CHANGE(STT_EDIT_REMOTECOP, &CSttRemoteScanConfigDlg::OnEnChangeEditCop)
	ON_EN_CHANGE(STT_EDIT_REMOTEUSER, &CSttRemoteScanConfigDlg::OnEnChangeEditUser)
END_MESSAGE_MAP()


// CSttRemoteScanConfigDlg 消息处理程序

BOOL CSttRemoteScanConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcCloudIP,_T("云端IP："), CRect(5,20,100,45), STT_STC_CLOUDIP_1, this);
	m_ctrlCloudIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(100,20,280,45), this, STT_EDIT_CLOUDIP_1); 
	CreateStatic(m_stcCloudPort,_T("云端Port："), CRect(300,20,380,45), STT_STC_CLOUDPORT_1, this);
	CreateEdit(m_edtCloudPort,   CRect(380,20,460,45), STT_EDIT_CLOUDPORT_1, this);
	CreateButton(m_btnConnect,_T("连接"), CRect(480,20,550,45), STT_BTN_CONNECT_1, this);
	CreateButton(m_btnQuery,_T("查询"), CRect(560,20,630,45), STT_BTN_REMOTEQUERY, this);

	m_grid.Create(CRect(5,50,630,205), this, STT_GRID_REMOTETESTAPP);
	m_grid.SetFont(g_pGlobalFont11);
	m_grid.InitGrid();
	m_grid.AttachDataViewOptrInterface(this);

	CreateStatic(m_stcCompany,_T("单位："), CRect(5,215,60,240), STT_STC_REMOTECOP, this);
	CreateEdit(m_editCompany,   CRect(60,215,230,240), STT_EDIT_REMOTECOP, this);
	CreateStatic(m_stcUser,_T("用户："), CRect(250,215,305,240), STT_STC_REMOTEUSER, this);
	CreateEdit(m_edtUser,   CRect(305,215,385,240), STT_EDIT_REMOTEUSER, this);
	CreateButton(m_btnCancel,_T("取消"), CRect(500,215,560,240), STT_BTN_REMOTECANCEL, this);
	CreateButton(m_btnBind,_T("绑定"), CRect(570,215,630,240), STT_BTN_REMOTEBIND, this);

	CFont *pFont = m_pGlobalFont11;
	m_stcCloudIP.SetFont(pFont);
	m_ctrlCloudIP.SetFont(pFont);
	m_stcCloudPort.SetFont(pFont);
	m_edtCloudPort.SetFont(pFont);
	m_btnConnect.SetFont(pFont);
	m_btnQuery.SetFont(pFont);

	m_stcCompany.SetFont(pFont);
	m_editCompany.SetFont(pFont);
	m_stcUser.SetFont(pFont);
	m_edtUser.SetFont(pFont);

	m_btnBind.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	

	CString strPort;
	strPort.Format(_T("%d"),m_pSttTestAppCfg->GetCloudServerPort());
	m_ctrlCloudIP.SetWindowText(m_pSttTestAppCfg->GetCloudIP());
	m_edtCloudPort.SetWindowText(strPort);
	m_editCompany.SetWindowText(m_pSttTestAppCfg->GetCopName());
	m_edtUser.SetWindowText(m_pSttTestAppCfg->GetUserName());
	EnableButtons();

	MoveWindow(CRect( 0, 0, 650, 250), TRUE);

	return TRUE;
}

void CSttRemoteScanConfigDlg::OnBtnClickBind()
{
	CSttTestRemoteRegister *pSelRegister = (CSttTestRemoteRegister *)m_grid.GetCurrSelData();

	CString strUser = _T(""),strCop = _T("");
	m_editCompany.GetWindowText(strCop);
	m_edtUser.GetWindowText(strUser);

	if (strCop.IsEmpty() || strUser.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("测试仪信息、用户信息输出错误"));
		return;
	}

	CSttTestClientUser oUser;
	oUser.id_soft(m_pSttTestAppConfigTool->m_strSoftID);
	oUser.Name_User(strUser);
	oUser.Name_Cop(strCop);
	oUser.SN_TestApp(pSelRegister->SN_TestApp());
	oUser.Code_Register(pSelRegister->Code_Register());

	if (!m_pSttTestAppConfigTool->Remote_BindAndLogin(m_pSttTestAppCfg, pSelRegister,&oUser))
	{
		return;
	}

	m_pSttTestAppCfg->SetCopName(strCop);
	m_pSttTestAppCfg->SetUserName(strUser);

	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDOK,STT_REMOTESCANCONFIG_DLG_INDEX);
}

void CSttRemoteScanConfigDlg::OnBtnClickQuery()
{
	CSttCmdData oRetData;
	long nExecStatus = m_pSttTestAppConfigTool->m_pClientEngine->Remote_Query(_T(""),TRUE,&oRetData);
	if (Stt_Is_ExecStatus_Success(nExecStatus))
	{
		CSttTestEngineRemoteClientData *pRemoteEngine = (CSttTestEngineRemoteClientData *)m_pSttTestAppConfigTool->m_pClientEngine;

		if (pRemoteEngine != NULL)
		{
			m_grid.ShowDatas(&pRemoteEngine->m_oSttRemoteRegList);
		}
	}
}

void CSttRemoteScanConfigDlg::OnEnChangeEditCloudport()
{
	EnableButtons();
}

void CSttRemoteScanConfigDlg::OnEnChangeEditCop()
{
	EnableButtons();
}

void CSttRemoteScanConfigDlg::OnEnChangeEditUser()
{
	EnableButtons();
}

void CSttRemoteScanConfigDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	EnableButtons();
}

void CSttRemoteScanConfigDlg::OnBtnClickConnect()
{
	if(m_bConnect)
	{
		m_bConnect = !m_pSttTestAppConfigTool->Remote_DisconnectServer();
		EnableButtons();

		if(!m_bConnect)
		{
			CSttTestEngineRemoteClientData *pRemoteEngine = (CSttTestEngineRemoteClientData *)m_pSttTestAppConfigTool->m_pClientEngine;

			if (pRemoteEngine != NULL)
			{
				pRemoteEngine->m_oSttRemoteRegList.DeleteAll();
				m_grid.ShowDatas(NULL);
			}
		}
		return;
	}

	CString strIP = _T(""),strPort = _T("");
	long nPort = 0;
	m_ctrlCloudIP.GetWindowText(strIP);
	m_edtCloudPort.GetWindowText(strPort);
	nPort = _ttoi(strPort);

	if (strIP.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("IP为空"));
		return;
	}

	m_bConnect = m_pSttTestAppConfigTool->Remote_ConnectServer(m_pSttTestAppCfg, strIP,nPort);
	EnableButtons();

	if(!m_bConnect)
	{
		MessageBox(_T("连接云端失败"),_T("提示"),MB_OK);
		return;
	}

	m_pSttTestAppCfg->SetCloudIP(strIP);
	m_pSttTestAppCfg->SetCloudServerPort(nPort);
}

void CSttRemoteScanConfigDlg::OnBtnClickCancel()
{
	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDCANCEL,0);
}

void CSttRemoteScanConfigDlg::EnableButtons()
{
	UpdateData(TRUE);

	CString strIP = _T(""),strPort = _T(""),strCop = _T(""),strUser = _T("");
	long nPort = 0;
	m_ctrlCloudIP.GetWindowText(strIP);
	m_edtCloudPort.GetWindowText(strPort);
	nPort = _ttoi(strPort);

	if (strIP.IsEmpty() || nPort <= 0)
	{
		m_btnConnect.EnableWindow(FALSE);
	}
	else
	{
		m_btnConnect.EnableWindow(TRUE);
	}

	CWnd *pParentWnd = this->GetParentOwner();

	if (m_bConnect)
	{
		m_btnConnect.SetWindowText(_T("断链"));

		BOOL bEnable = (m_grid.GetCurrSelData() != NULL);
		m_editCompany.GetWindowText(strCop);
		m_edtUser.GetWindowText(strUser);

		if (!bEnable
			|| strCop.IsEmpty()
			|| strUser.IsEmpty())
		{
			m_btnBind.EnableWindow(FALSE);
		}
		else
		{
			m_btnBind.EnableWindow(TRUE);
		}

		m_btnQuery.EnableWindow(TRUE);

		pParentWnd->PostMessage(TESTAPPCONFIG_LOCKTAB_MSG,0,STT_REMOTESCANCONFIG_DLG_INDEX);
	}
	else
	{
		m_btnConnect.SetWindowText(_T("连接"));
		m_btnBind.EnableWindow(FALSE);
		m_btnQuery.EnableWindow(FALSE);

		pParentWnd->PostMessage(TESTAPPCONFIG_LOCKTAB_MSG,0,STT_REMOTESCANCONFIG_DLG_ALLINDEX);
	}
}