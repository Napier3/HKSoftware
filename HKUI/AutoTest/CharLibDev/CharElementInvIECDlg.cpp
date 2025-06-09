// CharElementInvIECDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementInvIECDlg.h"


// CCharElementInvIECDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementInvIECDlg, CDialog)

CCharElementInvIECDlg::CCharElementInvIECDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementInvIECDlg::IDD, pParent)
	, m_strTp(_T(""))
	, m_strK(_T(""))
	, m_strAlpha(_T(""))
{

}

CCharElementInvIECDlg::~CCharElementInvIECDlg()
{
}

void CCharElementInvIECDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IEC_TP, m_strTp);
	DDX_Text(pDX, IDC_IEC_K, m_strK);
	DDX_Text(pDX, IDC_IEC_ALPHA, m_strAlpha);
}


BEGIN_MESSAGE_MAP(CCharElementInvIECDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementInvIECDlg 消息处理程序
void CCharElementInvIECDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementInvIECDlg::ShowData()
{
	CCharElementIEC * pCharData= (CCharElementIEC *) m_pCharElementBase;

	m_strTp = pCharData->m_strTp;
	m_strK = pCharData->m_strK;
	m_strAlpha = pCharData->m_strAlpha;

	UpdateData(FALSE);
}

void CCharElementInvIECDlg::GetData()
{
	CCharElementIEC * pCharData= (CCharElementIEC *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strTp = m_strTp;
	pCharData->m_strK = m_strK;
	pCharData->m_strAlpha = m_strAlpha;
}

BOOL CCharElementInvIECDlg::IsEnable()
{
	if (m_strTp.IsEmpty())
	{
		return FALSE;
	}

	if (m_strK.IsEmpty())
	{
		return FALSE;
	}

	if (m_strAlpha.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

