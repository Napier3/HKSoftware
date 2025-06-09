// XDlgUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AtsStudio.h"
#include "XDlgUser.h"


// CXDlgUser �Ի���

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
	{//��Admin�������޸��κ��û���Ϣ������ֻ���޸�Admin������
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
	{//����Amin��ֻ���޸��Լ�������
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


// CXDlgUser ��Ϣ�������

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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CXDlgUser::OnOK()
{
	UpdateData(TRUE);
	m_pCurrUser->SetName(m_strName);
	m_pCurrUser->SetID(m_strID);
	m_pCurrUser->SetPSW(m_strPSW);

	CXUserMngr *pUserMngr = CUserDBConstGlobal::GetUserMngr();

	//�ж��û���
	CXUser *pFind = pUserMngr->FindUserByName(m_strName);

	if (pFind != NULL)
	{
		if (pFind != m_pCurrUser)
		{
			MessageBox(_T("������ͬ���û���"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
			return;
		}
	}

	//�ж��û�ID
	pFind = pUserMngr->FindUserByID(m_strID);

	if (pFind != NULL)
	{
		if (pFind != m_pCurrUser)
		{
			MessageBox(_T("������ͬ���û���"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
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
