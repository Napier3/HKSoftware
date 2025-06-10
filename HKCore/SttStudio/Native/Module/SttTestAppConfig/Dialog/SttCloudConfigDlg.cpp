// SttCloudConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttCloudConfigDlg.h"
#include "../SttTestAppConfigTool.h"


// CSttCloudConfigDlg �Ի���

//IMPLEMENT_DYNAMIC(CSttCloudConfigDlg, CDialog)

CSttCloudConfigDlg::CSttCloudConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttCloudConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_nSvrPort = 0;
}

CSttCloudConfigDlg::~CSttCloudConfigDlg()
{
}

void CSttCloudConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!::IsWindow(m_edtCloudIP.m_hWnd))
	{
		return;
	}

	DDX_Text(pDX, STT_EDIT_CLOUDIP, m_strIP);
	DDX_Text(pDX, STT_EDIT_CLOUDSVRPORT, m_nSvrPort);
}


BEGIN_MESSAGE_MAP(CSttCloudConfigDlg, CDynDialogEx)
	ON_BN_CLICKED(STT_BTN_OK, &CSttCloudConfigDlg::OnBtnClickOK)
	ON_BN_CLICKED(STT_BTN_CANCEL, &CSttCloudConfigDlg::OnBtnClickCancel)
END_MESSAGE_MAP()


// CSttCloudConfigDlg ��Ϣ�������

BOOL CSttCloudConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcCloudIP,_T("�ƶ�IP��"), CRect(10,10,90,35), STT_STC_CLOUDIP, this);
	CreateEdit(m_edtCloudIP,   CRect(90,10,200,35), STT_EDIT_CLOUDIP, this);
	CreateStatic(m_stcCloudSvrPort,_T("�˿ںţ�"), CRect(10,45,90,70), STT_STC_CLOUDSVRPORT, this);
	CreateEdit(m_edtCloudSvrPort,   CRect(90,45,200,70), STT_EDIT_CLOUDSVRPORT, this);
	
	CreateButton(m_btnCancel,_T("ȡ��"), CRect(20,90,100,115), STT_BTN_CANCEL, this);
	CreateButton(m_btnOK,_T("ȷ��"), CRect(110,90,190,115), STT_BTN_OK, this);

	CFont *pFont = g_pGlobalFont12;
	m_stcCloudIP.SetFont(pFont);
	m_edtCloudIP.SetFont(pFont);
	m_stcCloudSvrPort.SetFont(pFont);
	m_edtCloudSvrPort.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_btnOK.SetFont(pFont);

	m_strIP = CSttTestAppCfg::GetCloudIP();
	m_nSvrPort = CSttTestAppCfg::GetCloudServerPort();
	UpdateData(FALSE);

	MoveWindow(CRect( 0, 0, 220, 160), TRUE);
	CenterWindow();
	SetWindowText(_T("�ƶ�����"));
	return TRUE;
}

void CSttCloudConfigDlg::OnBtnClickOK()
{
	UpdateData(TRUE);

	if(m_strIP.IsEmpty() || m_nSvrPort <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("IP���˿ں��������"));
		return;
	}

	CDynDialogEx::OnOK();	
}

void CSttCloudConfigDlg::OnBtnClickCancel()
{
	CDynDialogEx::OnCancel();	
}