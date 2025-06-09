// XDlgUser.cpp : 实现文件
//

#include "stdafx.h"
#include "AtsStudio.h"
#include "XDlgUser.h"


// CXDlgUser 对话框

IMPLEMENT_DYNAMIC(CXDlgUser, CDialog)

CXDlgUser::CXDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(CXDlgUser::IDD, pParent)
	, m_strName(_T(""))
	, m_strID(_T(""))
	, m_strPSW(_T(""))
{
	m_pCurrUser = NULL;
}

CXDlgUser::~CXDlgUser()
{
}

void CXDlgUser::EnableOK()
{
	UpdateData(TRUE);

	BOOL bEnable = TRUE;

	if (m_strName.GetLength() == 0 || m_strID.GetLength() == 0)
	{
		bEnable = FALSE;
	}

	m_btnOK.EnableWindow(bEnable);
}

void CXDlgUser::EnableByUser()
{
	CXUser *pUser = CUserDBConstGlobal::GetCurrUser();

	if (pUser->IsAdmin())
	{//是Admin，可以修改任何用户信息，但是只能修改Admin的密码
		//Admin
		if (m_strID == pUser->GetID())
		{
			m_edtName.EnableWindow(FALSE);
			m_edtID.EnableWindow(FALSE);
		}
		else
		{
			m_edtName.EnableWindow(TRUE);
			m_edtID.EnableWindow(TRUE);
		}
	}
	else
	{//不是Amin，只能修改自己的密码
		m_edtName.EnableWindow(FALSE);
		m_edtID.EnableWindow(FALSE);

		if (m_strID == pUser->GetID())
		{
			m_edtPSW.EnableWindow(TRUE);
		}
		else
		{
			m_edtPSW.EnableWindow(FALSE);
		}
	}
}

void CXDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtName);
	DDX_Control(pDX, IDC_EDIT_ID, m_edtID);
	DDX_Control(pDX, IDC_EDIT_PSW, m_edtPSW);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PSW, m_strPSW);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CXDlgUser, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CXDlgUser::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_ID, &CXDlgUser::OnEnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_PSW, &CXDlgUser::OnEnChangeEditPsw)
END_MESSAGE_MAP()


// CXDlgUser 消息处理程序

BOOL CXDlgUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT (m_pCurrUser != NULL);

	m_strName = m_pCurrUser->GetName();
	m_strID   = m_pCurrUser->GetID();
	m_strPSW  = m_pCurrUser->GetPSW();
	UpdateData(FALSE);

	EnableByUser();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXDlgUser::OnOK()
{
	UpdateData(TRUE);
	m_pCurrUser->SetName(m_strName);
	m_pCurrUser->SetID(m_strID);
	m_pCurrUser->SetPSW(m_strPSW);

	CXUserMngr *pUserMngr = CUserDBConstGlobal::GetUserMngr();

	//判断用户名
	CXUser *pFind = pUserMngr->FindUserByName(m_strName);

	if (pFind != NULL)
	{
		if (pFind != m_pCurrUser)
		{
			MessageBox(_T("存在相同的用户名"), _T("提示"), MB_OK | MB_ICONWARNING);
			return;
		}
	}

	//判断用户ID
	pFind = pUserMngr->FindUserByID(m_strID);

	if (pFind != NULL)
	{
		if (pFind != m_pCurrUser)
		{
			MessageBox(_T("存在相同的用户名"), _T("提示"), MB_OK | MB_ICONWARNING);
			return;
		}
	}

	CDialog::OnOK();
}

void CXDlgUser::OnEnChangeEditName()
{
	EnableOK();
}

void CXDlgUser::OnEnChangeEditId()
{
	EnableOK();
}

void CXDlgUser::OnEnChangeEditPsw()
{
	EnableOK();
}
