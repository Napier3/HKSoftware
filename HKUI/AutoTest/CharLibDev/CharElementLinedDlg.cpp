// CharElementLinedDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementLinedDlg.h"


// CCharElementLinedDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementLinedDlg, CDialog)

CCharElementLinedDlg::CCharElementLinedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementLinedDlg::IDD, pParent)
{

}

CCharElementLinedDlg::~CCharElementLinedDlg()
{
}

void CCharElementLinedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XB, m_strXb);
	DDX_Text(pDX, IDC_EDIT_YB, m_strYb);
	DDX_Text(pDX, IDC_EDIT_XE, m_strXe);
	DDX_Text(pDX, IDC_EDIT_YE, m_strYe);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cmbDir);
}


BEGIN_MESSAGE_MAP(CCharElementLinedDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementLinedDlg 消息处理程序
void CCharElementLinedDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD_DIALOG_LINED, pParent);
	m_pDialog = this;
	m_cmbDir.ShowBaseList(CCharacteristicConstGlobal::DirDataType());
}

void CCharElementLinedDlg::ShowData()
{
	CCharElementLined * pCharData= (CCharElementLined *) m_pCharElementBase;

	m_strXe = pCharData->m_strXe;
	m_strXb = pCharData->m_strXb;
	m_strYe = pCharData->m_strYe;
	m_strYb = pCharData->m_strYb;
	m_cmbDir.SetSelByID(pCharData->m_strDir);

	UpdateData(FALSE);
}

void CCharElementLinedDlg::GetData()
{
	CCharElementLined * pCharData= (CCharElementLined *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strXe = m_strXe;
	pCharData->m_strXb = m_strXb;
	pCharData->m_strYe = m_strYe;
	pCharData->m_strYb = m_strYb;
	m_cmbDir.GetSelectID(pCharData->m_strDir);
}

BOOL CCharElementLinedDlg::IsEnable()
{
	if (m_strXe.IsEmpty())
	{
		return FALSE;
	}

	if (m_strYe.IsEmpty())
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