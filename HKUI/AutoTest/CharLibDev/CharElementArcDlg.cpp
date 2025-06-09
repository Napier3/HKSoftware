// CharElementArcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementArcDlg.h"


// CCharElementArcDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementArcDlg, CDialog)

CCharElementArcDlg::CCharElementArcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementArcDlg::IDD, pParent)
	, m_strXCenter(_T(""))
	, m_strYCenter(_T(""))
	, m_strRadius(_T(""))
	, m_strAngleBegin(_T(""))
	, m_strAngleEnd(_T(""))
	, m_strClockwise(_T(""))
{

}

CCharElementArcDlg::~CCharElementArcDlg()
{
}

void CCharElementArcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARC_X, m_strXCenter);
	DDX_Text(pDX, IDC_EDIT_ARC_Y, m_strYCenter);
	DDX_Text(pDX, IDC_EDIT_ARC_RADIUS, m_strRadius);
	DDX_Text(pDX, IDC_EDIT_ARC_STARTANGLE, m_strAngleBegin);
	DDX_Text(pDX, IDC_EDIT_ARC_ENDANGLE, m_strAngleEnd);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cmbDir);
	DDX_Control(pDX, IDC_COMBO_CLOCKWISE, m_cmbClockwise);
}


BEGIN_MESSAGE_MAP(CCharElementArcDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementArcDlg 消息处理程序
void CCharElementArcDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD_DIALOG_ARC, pParent);
	m_pDialog = this;

	m_cmbDir.ShowBaseList(CCharacteristicConstGlobal::DirDataType());
	m_cmbClockwise.ShowBaseList(CCharacteristicConstGlobal::ClockwiseDataType());
}

void CCharElementArcDlg::ShowData()
{
	CCharElementArc * pCharData= (CCharElementArc *) m_pCharElementBase;

	m_strXCenter = pCharData->m_strXCenter;
	m_strYCenter = pCharData->m_strYCenter;
	m_strRadius = pCharData->m_strRadius;
	m_strAngleBegin = pCharData->m_strAngleBegin;
	m_strAngleEnd = pCharData->m_strAngleEnd;
	m_cmbDir.SetSelByID(pCharData->m_strDir);
	m_cmbClockwise.SetSelByID(pCharData->m_strClockwise);

	UpdateData(FALSE);
}

void CCharElementArcDlg::GetData()
{
	CCharElementArc * pCharData= (CCharElementArc *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strXCenter = m_strXCenter;
	pCharData->m_strYCenter = m_strYCenter;
	pCharData->m_strRadius = m_strRadius;
	pCharData->m_strAngleBegin = m_strAngleBegin;
	pCharData->m_strAngleEnd = m_strAngleEnd;

	m_cmbDir.GetSelectID(pCharData->m_strDir);
	m_cmbClockwise.GetSelectID(pCharData->m_strClockwise);
}

BOOL CCharElementArcDlg::IsEnable()
{
	if (m_strXCenter.IsEmpty())
	{
		return FALSE;
	}

	if (m_strYCenter.IsEmpty())
	{
		return FALSE;
	}

	if (m_strRadius.IsEmpty())
	{
		return FALSE;
	}

	if (m_strAngleBegin.IsEmpty())
	{
		return FALSE;
	}

	if (m_strAngleEnd.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}
