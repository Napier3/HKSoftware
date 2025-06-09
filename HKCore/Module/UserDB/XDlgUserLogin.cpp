// XDlgUserLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XDlgUserLogin.h"


// CXDlgUserLogin �Ի���

CXDlgUserLogin::CXDlgUserLogin(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{

}

CXDlgUserLogin::~CXDlgUserLogin()
{
}

void CXDlgUserLogin::OpenUserLoginHistoryFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("UserLoginHistory.xml");

	m_oUserLoginHistory.OpenXmlFile(strFile);
}

void CXDlgUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_CBString(pDX, XUSRID_COMBO_USERNAME, m_strName);
	DDX_Text(pDX, XUSRID_EDIT_USERPSW, m_strPSW);
}


BEGIN_MESSAGE_MAP(CXDlgUserLogin, CDialog)
END_MESSAGE_MAP()


// CXDlgUserLogin ��Ϣ�������

BOOL CXDlgUserLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateStatic(m_stcUserName,  _T("�û���"), CRect(10,24,70,44), XUSRID_STC_USERNAME, this);
	CreateStatic(m_stcUserPsw,  _T("����"),    CRect(10,54,70,74), XUSRID_STC_USERPSW, this);
	CreateComboBox_DropDown(m_cmbUserFilter,   CRect(71,24,242,124), XUSRID_COMBO_USERNAME, this);
	CreateEdit(m_edtUserPsw,                   CRect(71,54,242,74), XUSRID_EDIT_USERPSW, this);

	CreateButton(m_btnOK, _T("ȷ��"), CRect(51,97,121,117), IDOK, this);
	CreateButton(m_btnCancel, _T("ȡ��"), CRect(130,97,200,117), IDCANCEL, this);

	CFont *pFont = g_pGlobalFont;
	m_stcUserName.SetFont(pFont);
	m_cmbUserFilter.SetFont(pFont);
	m_stcUserPsw.SetFont(pFont);
	m_edtUserPsw.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	MoveWindow(CRect( 0, 0, 270, 160), TRUE);
	CenterWindow();
	SetWindowText(_T("�û���¼"));

	OpenUserLoginHistoryFile();
	m_cmbUserFilter.ShowBaseList(&m_oUserLoginHistory);
	m_cmbUserFilter.SetCurSel(0);

	m_bHasInitDialog = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CXDlgUserLogin::OnOK()
{
	UpdateData(TRUE);
	CXUser *pUser = CUserDBConstGlobal::Login(m_strName, m_strPSW);

	if (pUser == NULL)
	{
		MessageBox(CUserDBConstGlobal::GetLoginError(), _T("��¼����"), MB_OK | MB_ICONERROR);
		return;
	}

	CFilterText *pText = m_oUserLoginHistory.AddText(m_strName);
	m_oUserLoginHistory.BringToHead(pText);
	m_oUserLoginHistory.SaveXmlFile();

	CDialog::OnOK();
}
