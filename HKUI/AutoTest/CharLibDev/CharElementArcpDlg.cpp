// CharElementArcpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementArcpDlg.h"


// CCharElementArcpDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementArcpDlg, CDialog)

CCharElementArcpDlg::CCharElementArcpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementArcpDlg::IDD, pParent)
	, m_strZ(_T(""))
	, m_strPh(_T(""))
	, m_strRadius(_T(""))
	, m_strAngleBegin(_T(""))
	, m_strAngleEnd(_T(""))
	, m_strDir(_T(""))
{

}

CCharElementArcpDlg::~CCharElementArcpDlg()
{
}

void CCharElementArcpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARC_Z, m_strZ);
	DDX_Text(pDX, IDC_EDIT_ARC_PH, m_strPh);
	DDX_Text(pDX, IDC_EDIT_ARC_RADIUS, m_strRadius);
	DDX_Text(pDX, IDC_EDIT_ARC_STARTANGLE, m_strAngleBegin);
	DDX_Text(pDX, IDC_EDIT_ARC_ENDANGLE, m_strAngleEnd);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cmbDir);
	DDX_Control(pDX, IDC_COMBO_CLOCKWISE, m_cmbClockwise);
}


BEGIN_MESSAGE_MAP(CCharElementArcpDlg, CDialog)
END_MESSAGE_MAP()


// CCharElementArcpDlg 消息处理程序
void CCharElementArcpDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD_DIALOG_ARCP, pParent);
	m_pDialog = this;

	m_cmbDir.ShowBaseList(CCharacteristicConstGlobal::DirDataType());
	m_cmbClockwise.ShowBaseList(CCharacteristicConstGlobal::ClockwiseDataType());
}

void CCharElementArcpDlg::ShowData()
{
	CCharElementArcp * pCharData= (CCharElementArcp *) m_pCharElementBase;

	m_strZ = pCharData->m_strZ;
	m_strPh = pCharData->m_strPh;
	m_strRadius = pCharData->m_strRadius;
	m_strAngleBegin = pCharData->m_strAngleBegin;
	m_strAngleEnd = pCharData->m_strAngleEnd;

	m_cmbDir.SetSelByID(pCharData->m_strDir);
	m_cmbClockwise.SetSelByID(pCharData->m_strClockwise);

	UpdateData(FALSE);
}

void CCharElementArcpDlg::GetData()
{
	CCharElementArcp * pCharData= (CCharElementArcp *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strZ = m_strZ;
	pCharData->m_strPh = m_strPh;
	pCharData->m_strRadius = m_strRadius;
	pCharData->m_strAngleBegin = m_strAngleBegin;
	pCharData->m_strAngleEnd = m_strAngleEnd;

	m_cmbDir.GetSelectID(pCharData->m_strDir);
	m_cmbClockwise.GetSelectID(pCharData->m_strClockwise);
}

BOOL CCharElementArcpDlg::IsEnable()
{
	if (m_strZ.IsEmpty())
	{
		return FALSE;
	}

	if (m_strPh.IsEmpty())
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

