// CharElementLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementLineDlg.h"


// CCharElementLineDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementLineDlg, CDialog)

CCharElementLineDlg::CCharElementLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementLineDlg::IDD, pParent)
	, m_strXb(_T(""))
	, m_strYb(_T(""))
	, m_strAngle(_T(""))
{

}

CCharElementLineDlg::~CCharElementLineDlg()
{
}

void CCharElementLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_strXb);
	DDX_Text(pDX, IDC_EDIT_Y, m_strYb);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_strAngle);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cmbDir);
}


BEGIN_MESSAGE_MAP(CCharElementLineDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementLineDlg 消息处理程序
void CCharElementLineDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD_DIALOG_LINE, pParent);
	m_pDialog = this;
	m_cmbDir.ShowBaseList(CCharacteristicConstGlobal::DirDataType());
}

void CCharElementLineDlg::ShowData()
{
	CCharElementLine * pCharData= (CCharElementLine *) m_pCharElementBase;

	m_strAngle = pCharData->m_strAngle;
	m_strXb = pCharData->m_strX;
	m_strYb = pCharData->m_strY;
	m_cmbDir.SetSelByID(pCharData->m_strDir);

	UpdateData(FALSE);
}

void CCharElementLineDlg::GetData()
{
	CCharElementLine * pCharData= (CCharElementLine *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strX = m_strXb;
	pCharData->m_strY = m_strYb;
	pCharData->m_strAngle = m_strAngle;
	m_cmbDir.GetSelectID(pCharData->m_strDir);
}

BOOL CCharElementLineDlg::IsEnable()
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