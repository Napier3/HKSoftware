// SttLocalConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttLocalConfigDlg.h"
#include "../SttTestAppConfigTool.h"


// CSttLocalConfigDlg �Ի���

//IMPLEMENT_DYNAMIC(CSttLocalConfigDlg, CDialog)

CSttLocalConfigDlg::CSttLocalConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttLocalConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_nSvrPort = STT_PORT_TEST_SERVER;
	m_pSttTestAppConfigTool = NULL;
	m_pSttTestAppCfg = NULL;
	m_pGlobalFont11 = font_CreateNew(g_lfGlobalFont11, -11);
}

CSttLocalConfigDlg::~CSttLocalConfigDlg()
{
	if (m_pGlobalFont11 != NULL)
	{
		delete m_pGlobalFont11;
	}
}

void CSttLocalConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSttLocalConfigDlg, CDynDialogEx)
	ON_BN_CLICKED(STT_BTN_OK, &CSttLocalConfigDlg::OnBtnClickOK)
	ON_BN_CLICKED(STT_BTN_CANCEL, &CSttLocalConfigDlg::OnBtnClickCancel)
END_MESSAGE_MAP()


// CSttLocalConfigDlg ��Ϣ�������

BOOL CSttLocalConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcIP,_T("IP��"), CRect(10,20,35,45), STT_STC_TESTAPPIP, this);
	m_ctrlIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(40,20,240,45), this, STT_EDIT_TESTAPPIP); 
	CreateButton(m_btnCancel,_T("ȡ��"), CRect(460,215,540,240), STT_BTN_CANCEL, this);
	CreateButton(m_btnOK,_T("ȷ��"), CRect(550,215,630,240), STT_BTN_OK, this);

	m_stcIP.SetFont(m_pGlobalFont11);
	m_ctrlIP.SetFont(m_pGlobalFont11);
	m_btnCancel.SetFont(m_pGlobalFont11);
	m_btnOK.SetFont(m_pGlobalFont11);

	m_ctrlIP.SetWindowText(m_pSttTestAppCfg->GetTestAppIP());

	MoveWindow(CRect( 0, 0, 650, 250), TRUE);

	return TRUE;
}

void CSttLocalConfigDlg::OnBtnClickOK()
{
	CString strIP = _T("");
	m_ctrlIP.GetWindowText(strIP);

	if (strIP.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("IPΪ��"));
		return;
	}

	BOOL bRet = m_pSttTestAppConfigTool->Local_ConnectServer(m_pSttTestAppCfg, strIP,m_nSvrPort,m_pSttTestAppConfigTool->m_strSoftID);

	m_pSttTestAppCfg->SetTestAppIP(strIP);
	m_pSttTestAppCfg->SaveAfterConfig();

	if(!bRet)
	{
		MessageBox(_T("���Ӳ�����ʧ��"),_T("��ʾ"),MB_OK);
		return;
	}

	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDOK,STT_LOCALCONFIG_DLG_INDEX);	
}

void CSttLocalConfigDlg::OnBtnClickCancel()
{
	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDCANCEL,0);
}