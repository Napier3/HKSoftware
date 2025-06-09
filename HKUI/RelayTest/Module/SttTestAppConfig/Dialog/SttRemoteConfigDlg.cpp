// TestAppConfigRemoteConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SttRemoteConfigDlg.h"
#include "../SttTestAppConfigTool.h"


// CSttRemoteConfigDlg 对话框

//IMPLEMENT_DYNAMIC(CSttRemoteConfigDlg, CDialog)

CSttRemoteConfigDlg::CSttRemoteConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttRemoteConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_bConnect = FALSE;
	m_pSttTestAppConfigTool = NULL;
	m_pSttTestAppCfg = NULL;
	m_pGlobalFont11 = font_CreateNew(g_lfGlobalFont11, -11);
}

CSttRemoteConfigDlg::~CSttRemoteConfigDlg()
{
	if (m_pGlobalFont11 != NULL)
	{
		delete m_pGlobalFont11;
	}
}

void CSttRemoteConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSttRemoteConfigDlg, CDynDialogEx)
	ON_BN_CLICKED(STT_BTN_CONNECT, &CSttRemoteConfigDlg::OnBtnClickConnect)
	ON_BN_CLICKED(STT_BTN_BIND, &CSttRemoteConfigDlg::OnBtnClickBind)
	ON_BN_CLICKED(STT_BTN_CANCEL_2, &CSttRemoteConfigDlg::OnBtnClickCancel)
	ON_EN_CHANGE(STT_EDIT_CLOUDPORT, &CSttRemoteConfigDlg::OnEnChangeEditCloudport)
	ON_EN_CHANGE(STT_EDIT_SN, &CSttRemoteConfigDlg::OnEnChangeEditSN)
	ON_EN_CHANGE(STT_EDIT_PASSWORD, &CSttRemoteConfigDlg::OnEnChangeEditPassword)
	ON_EN_CHANGE(STT_EDIT_COP, &CSttRemoteConfigDlg::OnEnChangeEditCop)
	ON_EN_CHANGE(STT_EDIT_USER, &CSttRemoteConfigDlg::OnEnChangeEditUser)
END_MESSAGE_MAP()


// CSttRemoteConfigDlg 消息处理程序

BOOL CSttRemoteConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcCloudIP,_T("云端IP："), CRect(5,20,120,45), STT_STC_CLOUDIP, this);
	m_ctrlCloudIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(120,20,280,45), this, STT_EDIT_CLOUDIP); 
	CreateStatic(m_stcCloudPort,_T("云端Port："), CRect(300,20,380,45), STT_STC_CLOUDPORT, this);
	CreateEdit(m_edtCloudPort,   CRect(380,20,460,45), STT_EDIT_CLOUDPORT, this);
	CreateButton(m_btnConnect,_T("连接"), CRect(560,20,630,45), STT_BTN_CONNECT, this);

	CreateStatic(m_stcSN,_T("测试仪序列号："), CRect(5,100,120,125), STT_STC_SN, this);
	CreateEdit(m_edtSN,   CRect(120,100,280,125), STT_EDIT_SN, this);
	CreateStatic(m_stcPassword,_T("密码："), CRect(300,100,380,125), STT_STC_PASSWORD, this);
	CreateEdit(m_edtPassword,   CRect(380,100,460,125), STT_EDIT_PASSWORD, this);
	
	CreateStatic(m_stcCompany,_T("单位："), CRect(5,215,60,240), STT_STC_COP, this);
	CreateEdit(m_editCompany,   CRect(60,215,230,240), STT_EDIT_COP, this);
	CreateStatic(m_stcUser,_T("用户："), CRect(250,215,305,240), STT_STC_USER, this);
	CreateEdit(m_edtUser,   CRect(305,215,385,240), STT_EDIT_USER, this);
	CreateButton(m_btnCancel,_T("取消"), CRect(500,215,560,240), STT_BTN_CANCEL_2, this);
	CreateButton(m_btnBind,_T("绑定"), CRect(570,215,630,240), STT_BTN_BIND, this);

	CFont *pFont = m_pGlobalFont11;
	m_stcCloudIP.SetFont(pFont);
	m_ctrlCloudIP.SetFont(pFont);
	m_stcCloudPort.SetFont(pFont);
	m_edtCloudPort.SetFont(pFont);
	m_btnConnect.SetFont(pFont);

	m_stcSN.SetFont(pFont);
	m_edtSN.SetFont(pFont);
	m_stcPassword.SetFont(pFont);
	m_edtPassword.SetFont(pFont);
	m_stcCompany.SetFont(pFont);
	m_editCompany.SetFont(pFont);
	m_stcUser.SetFont(pFont);
	m_edtUser.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_btnBind.SetFont(pFont);

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

void CSttRemoteConfigDlg::OnBtnClickBind()
{
	CString strCode_Register = _T(""),strSN_TestApp = _T("");
	CString strUser = _T(""),strCop = _T("");
	m_edtSN.GetWindowText(strSN_TestApp);
	m_edtPassword.GetWindowText(strCode_Register);
	m_editCompany.GetWindowText(strCop);
	m_edtUser.GetWindowText(strUser);
	
	if (strSN_TestApp.IsEmpty() || strCode_Register.IsEmpty()
		|| strCop.IsEmpty() || strUser.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("测试仪信息、用户信息输出错误"));
		return;
	}
		
	CSttTestRemoteRegister oRegister;
	CSttTestClientUser oUser;
	oRegister.Code_Register(strCode_Register);
	oRegister.SN_TestApp(strSN_TestApp);

	oUser.id_soft(m_pSttTestAppConfigTool->m_strSoftID);
	oUser.Name_User(strUser);
	oUser.Name_Cop(strCop);
	oUser.SN_TestApp(strSN_TestApp);
	oUser.Code_Register(strCode_Register);

	if (!m_pSttTestAppConfigTool->Remote_BindAndLogin(m_pSttTestAppCfg, &oRegister,&oUser))
	{
		return;
	}

	m_pSttTestAppCfg->SetCopName(strCop);
	m_pSttTestAppCfg->SetUserName(strUser);

	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDOK,STT_REMOTECONFIG_DLG_INDEX);
}

void CSttRemoteConfigDlg::OnEnChangeEditCloudport()
{
	EnableButtons();
}

void CSttRemoteConfigDlg::OnEnChangeEditSN()
{
	EnableButtons();
}

void CSttRemoteConfigDlg::OnEnChangeEditPassword()
{
	EnableButtons();
}

void CSttRemoteConfigDlg::OnEnChangeEditCop()
{
	EnableButtons();
}

void CSttRemoteConfigDlg::OnEnChangeEditUser()
{
	EnableButtons();
}

void CSttRemoteConfigDlg::OnBtnClickConnect()
{
	if(m_bConnect)
	{
		m_bConnect = !m_pSttTestAppConfigTool->Remote_DisconnectServer();
		EnableButtons();
		return;
	}

	CString strIP = _T(""),strPort = _T("");
	long nPort = 0;
	m_ctrlCloudIP.GetWindowText(strIP);
	m_edtCloudPort.GetWindowText(strPort);
	nPort = _ttoi(strPort);

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

void CSttRemoteConfigDlg::OnBtnClickCancel()
{
	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDCANCEL,0);
}

void CSttRemoteConfigDlg::EnableButtons()
{
	UpdateData(TRUE);

	CString strIP = _T(""),strPort = _T(""),strSN = _T(""),strPsd = _T(""),strCop = _T(""),strUser = _T("");
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
		m_edtSN.GetWindowText(strSN);
		m_edtPassword.GetWindowText(strPsd);
		m_editCompany.GetWindowText(strCop);
		m_edtUser.GetWindowText(strUser);

		if (strSN.IsEmpty()
			|| strPsd.IsEmpty()
			|| strCop.IsEmpty()
			|| strUser.IsEmpty())
		{
			m_btnBind.EnableWindow(FALSE);
		}
		else
		{
			m_btnBind.EnableWindow(TRUE);
		}

		pParentWnd->PostMessage(TESTAPPCONFIG_LOCKTAB_MSG,0,STT_REMOTECONFIG_DLG_INDEX);
	}
	else
	{
		m_btnConnect.SetWindowText(_T("连接"));
		m_btnBind.EnableWindow(FALSE);

		pParentWnd->PostMessage(TESTAPPCONFIG_LOCKTAB_MSG,0,STT_REMOTESCANCONFIG_DLG_ALLINDEX);
	}
}