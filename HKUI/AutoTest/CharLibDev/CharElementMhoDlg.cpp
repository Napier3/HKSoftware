// CharElementMhoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementMhoDlg.h"


// CCharElementMhoDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementMhoDlg, CDialog)

CCharElementMhoDlg::CCharElementMhoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementMhoDlg::IDD, pParent)
{

}

CCharElementMhoDlg::~CCharElementMhoDlg()
{
}

void CCharElementMhoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FORWARDREACH, m_strForwardReach);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_strAngle);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_strOffset);
}


BEGIN_MESSAGE_MAP(CCharElementMhoDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementMhoDlg 消息处理程序
void CCharElementMhoDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementMhoDlg::ShowData()
{
	CCharElementMho * pCharData= (CCharElementMho *) m_pCharElementBase;

	m_strForwardReach = pCharData->m_strForwardReach;
	m_strAngle = pCharData->m_strAngle;
	m_strOffset = pCharData->m_strOffset;

	UpdateData(FALSE);
}

void CCharElementMhoDlg::GetData()
{
	CCharElementMho * pCharData= (CCharElementMho *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strForwardReach = m_strForwardReach;
	pCharData->m_strAngle = m_strAngle;
	pCharData->m_strOffset = m_strOffset;
}

BOOL CCharElementMhoDlg::IsEnable()
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

	return TRUE;
}