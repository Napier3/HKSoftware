// TestAppConfigRemoteSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttRemoteScanConfigDlg.h"
#include "../SttTestAppConfigTool.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../XLangResource_Native.h"
#endif
// CSttRemoteScanConfigDlg �Ի���

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


// CSttRemoteScanConfigDlg ��Ϣ�������

BOOL CSttRemoteScanConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();
#ifndef NOT_USE_XLANGUAGE
	CreateStatic(m_stcCloudIP,/*_T("�ƶ�IP��")*/g_sLangTxt_Native_CloudIP, CRect(5,20,100,45), STT_STC_CLOUDIP_1, this);
	m_ctrlCloudIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(100,20,280,45), this, STT_EDIT_CLOUDIP_1); 
	CreateStatic(m_stcCloudPort,/*_T("�ƶ�Port��")*/g_sLangTxt_Native_CloudPort, CRect(300,20,380,45), STT_STC_CLOUDPORT_1, this);
	CreateEdit(m_edtCloudPort,   CRect(380,20,460,45), STT_EDIT_CLOUDPORT_1, this);
	CreateButton(m_btnConnect,/*_T("����")*/g_sLangTxt_Native_Connect, CRect(480,20,550,45), STT_BTN_CONNECT_1, this);
	CreateButton(m_btnQuery,/*_T("��ѯ")*/g_sLangTxt_Native_Query, CRect(560,20,630,45), STT_BTN_REMOTEQUERY, this);

	m_grid.Create(CRect(5,50,630,205), this, STT_GRID_REMOTETESTAPP);
	m_grid.SetFont(g_pGlobalFont11);
	m_grid.InitGrid();
	m_grid.AttachDataViewOptrInterface(this);

	CreateStatic(m_stcCompany,/*_T("��λ��")*/g_sLangTxt_Unit, CRect(5,215,60,240), STT_STC_REMOTECOP, this);
	CreateEdit(m_editCompany,   CRect(60,215,230,240), STT_EDIT_REMOTECOP, this);
	CreateStatic(m_stcUser,/*_T("�û���")*/g_sLangTxt_User2, CRect(250,215,305,240), STT_STC_REMOTEUSER, this);
	CreateEdit(m_edtUser,   CRect(305,215,385,240), STT_EDIT_REMOTEUSER, this);
	CreateButton(m_btnCancel,/*_T("ȡ��")*/g_sLangTxt_Cancel, CRect(500,215,560,240), STT_BTN_REMOTECANCEL, this);
	CreateButton(m_btnBind,/*_T("��")*/g_sLangTxt_Native_Bind, CRect(570,215,630,240), STT_BTN_REMOTEBIND, this);
#else
	CreateStatic(m_stcCloudIP,_T("�ƶ�IP��"), CRect(5,20,100,45), STT_STC_CLOUDIP_1, this);
	m_ctrlCloudIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(100,20,280,45), this, STT_EDIT_CLOUDIP_1); 
	CreateStatic(m_stcCloudPort,_T("�ƶ�Port��"), CRect(300,20,380,45), STT_STC_CLOUDPORT_1, this);
	CreateEdit(m_edtCloudPort,   CRect(380,20,460,45), STT_EDIT_CLOUDPORT_1, this);
	CreateButton(m_btnConnect,_T("����"), CRect(480,20,550,45), STT_BTN_CONNECT_1, this);
	CreateButton(m_btnQuery,_T("��ѯ"), CRect(560,20,630,45), STT_BTN_REMOTEQUERY, this);

	m_grid.Create(CRect(5,50,630,205), this, STT_GRID_REMOTETESTAPP);
	m_grid.SetFont(g_pGlobalFont11);
	m_grid.InitGrid();
	m_grid.AttachDataViewOptrInterface(this);

	CreateStatic(m_stcCompany,_T("��λ��"), CRect(5,215,60,240), STT_STC_REMOTECOP, this);
	CreateEdit(m_editCompany,   CRect(60,215,230,240), STT_EDIT_REMOTECOP, this);
	CreateStatic(m_stcUser,_T("�û���"), CRect(250,215,305,240), STT_STC_REMOTEUSER, this);
	CreateEdit(m_edtUser,   CRect(305,215,385,240), STT_EDIT_REMOTEUSER, this);
	CreateButton(m_btnCancel,_T("ȡ��"), CRect(500,215,560,240), STT_BTN_REMOTECANCEL, this);
	CreateButton(m_btnBind,_T("��"), CRect(570,215,630,240), STT_BTN_REMOTEBIND, this);
#endif
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
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("��������Ϣ���û���Ϣ�������")*/g_sLangTxt_Native_TestInstrumentUserInfoError);
#else
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��������Ϣ���û���Ϣ�������"));
#endif
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
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("IPΪ��")*/g_sLangTxt_Native_IPIsEmpty);
#else
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("IPΪ��"));
#endif
		return;
	}

	m_bConnect = m_pSttTestAppConfigTool->Remote_ConnectServer(m_pSttTestAppCfg, strIP,nPort);
	EnableButtons();

	if(!m_bConnect)
	{
#ifndef NOT_USE_XLANGUAGE
		//MessageBox(/*_T("�����ƶ�ʧ��")*/g_sLangTxt_CloudConnectionFailed,/*_T("��ʾ")*/g_sLangID_Message,MB_OK);
		CLogPrint::LogString(XLOGLEVEL_INFOR, /*_T("�����ƶ�ʧ��")*/g_sLangTxt_Native_CloudConnectionFailed);
#else
		MessageBox(_T("�����ƶ�ʧ��"),_T("��ʾ"),MB_OK);
#endif
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
#ifndef NOT_USE_XLANGUAGE
		m_btnConnect.SetWindowText(/*_T("����")*/g_sLangTxt_Native_Disconnection);
#else
		m_btnConnect.SetWindowText(_T("����"));
#endif

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
#ifndef NOT_USE_XLANGUAGE
		m_btnConnect.SetWindowText(/*_T("����")*/g_sLangTxt_Native_Connect);
#else
		m_btnConnect.SetWindowText(_T("����"));
#endif
		m_btnBind.EnableWindow(FALSE);
		m_btnQuery.EnableWindow(FALSE);

		pParentWnd->PostMessage(TESTAPPCONFIG_LOCKTAB_MSG,0,STT_REMOTESCANCONFIG_DLG_ALLINDEX);
	}
}