// CharElementLinerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementLinerDlg.h"


// CCharElementLinerDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementLinerDlg, CDialog)

CCharElementLinerDlg::CCharElementLinerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementLinerDlg::IDD, pParent)
{

}

CCharElementLinerDlg::~CCharElementLinerDlg()
{
}

void CCharElementLinerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XB, m_strXb);
	DDX_Text(pDX, IDC_EDIT_YB, m_strYb);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_strAngle);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cmbDir);
}


BEGIN_MESSAGE_MAP(CCharElementLinerDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementLinerDlg 消息处理程序
void CCharElementLinerDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
	m_cmbDir.ShowBaseList(CCharacteristicConstGlobal::DirDataType());
}

void CCharElementLinerDlg::ShowData()
{
	CCharElementLiner * pCharData= (CCharElementLiner *) m_pCharElementBase;

	m_strXb = pCharData->m_strXb;
	m_strYb = pCharData->m_strYb;
	m_strAngle = pCharData->m_strAngle;
	m_cmbDir.SetSelByID(pCharData->m_strDir);

	UpdateData(FALSE);
}

void CCharElementLinerDlg::GetData()
{
	CCharElementLiner * pCharData= (CCharElementLiner *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strXb = m_strXb;
	pCharData->m_strYb = m_strYb;
	pCharData->m_strAngle = m_strAngle;
	m_cmbDir.GetSelectID(pCharData->m_strDir);
}

BOOL CCharElementLinerDlg::IsEnable()
{
	if (m_strAngle.IsEmpty())
	{
		return FALSE;
	}

	if (m_strXb.IsEmpty())
	{
		return FALSE;
	}

	if (m_strYb.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

