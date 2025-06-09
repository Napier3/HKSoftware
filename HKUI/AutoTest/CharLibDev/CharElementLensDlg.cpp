// CharElementLensDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementLensDlg.h"


// CCharElementLensDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementLensDlg, CDialog)

CCharElementLensDlg::CCharElementLensDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementLensDlg::IDD, pParent)
{

}

CCharElementLensDlg::~CCharElementLensDlg()
{
}

void CCharElementLensDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FORWARDREACH, m_strForwardReach);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_strAngle);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_strOffset);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_strWidth);
}


BEGIN_MESSAGE_MAP(CCharElementLensDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementLensDlg 消息处理程序
void CCharElementLensDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementLensDlg::ShowData()
{
	CCharElementLens * pCharData= (CCharElementLens *) m_pCharElementBase;

	m_strForwardReach = pCharData->m_strForwardReach;
	m_strAngle = pCharData->m_strAngle;
	m_strOffset = pCharData->m_strOffset;
	m_strWidth = pCharData->m_strWidth;

	UpdateData(FALSE);
}

void CCharElementLensDlg::GetData()
{
	CCharElementLens * pCharData= (CCharElementLens *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strForwardReach = m_strForwardReach;
	pCharData->m_strAngle = m_strAngle;
	pCharData->m_strOffset = m_strOffset;
	pCharData->m_strWidth = m_strWidth;
}

BOOL CCharElementLensDlg::IsEnable()
{
	if (m_strForwardReach.IsEmpty())
	{
		return FALSE;
	}

	if (m_strOffset.IsEmpty())
	{
		return FALSE;
	}

	if (m_strAngle.IsEmpty())
	{
		return FALSE;
	}

	if (m_strWidth.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

