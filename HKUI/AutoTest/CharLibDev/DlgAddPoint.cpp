// DlgCharElement.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAddPoint.h"

// CDlgAddPoint 对话框

IMPLEMENT_DYNAMIC(CDlgAddPoint, CDialog)

CDlgAddPoint::CDlgAddPoint(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAddPoint::IDD, pParent)
, m_strX(_T("0.0"))
, m_strY(_T("0.0"))
{
	m_pPoint = new CCharElementPoint;
}

CDlgAddPoint::~CDlgAddPoint()
{
}


void CDlgAddPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IOWNDEF_X_EDIT, m_strX);
	DDX_Text(pDX, IDC_IOWNDEF_Y_EDIT, m_strY);
}


BEGIN_MESSAGE_MAP(CDlgAddPoint, CDialog)
END_MESSAGE_MAP()


// CDlgAddPoint 消息处理程序
BOOL CDlgAddPoint::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgAddPoint::OnOK()
{
	UpdateData(TRUE);

	m_pPoint->m_strX = m_strX;
	m_pPoint->m_strY = m_strY;
	m_pPoint->CalByExpression(TRUE);
	
	CDialog::OnOK();

}
