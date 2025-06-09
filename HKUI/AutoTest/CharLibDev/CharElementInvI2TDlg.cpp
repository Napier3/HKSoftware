// CharElementInvI2TDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementInvI2TDlg.h"


// CCharElementInvI2TDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementInvI2TDlg, CDialog)

CCharElementInvI2TDlg::CCharElementInvI2TDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementInvI2TDlg::IDD, pParent)
	, m_strTp(_T(""))
	, m_strA(_T(""))
{

}

CCharElementInvI2TDlg::~CCharElementInvI2TDlg()
{
}

void CCharElementInvI2TDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TP, m_strTp);
	DDX_Text(pDX, IDC_EDIT_A, m_strA);
}


BEGIN_MESSAGE_MAP(CCharElementInvI2TDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementInvI2TDlg 消息处理程序
void CCharElementInvI2TDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementInvI2TDlg::ShowData()
{
	CCharElementI2T * pCharData= (CCharElementI2T *) m_pCharElementBase;

	m_strTp = pCharData->m_strTp;
	m_strA = pCharData->m_strA;

	UpdateData(FALSE);
}

void CCharElementInvI2TDlg::GetData()
{
	CCharElementI2T * pCharData= (CCharElementI2T *) m_pCharElementBase;
	UpdateData(TRUE);

	pCharData->m_strTp = m_strTp;
	pCharData->m_strA = m_strA;
}

BOOL CCharElementInvI2TDlg::IsEnable()
{
 	if (m_strTp.IsEmpty())
 	{
 		return FALSE;
 	}
 
 	if (m_strA.IsEmpty())
 	{
 		return FALSE;
 	}

	return TRUE;
}

