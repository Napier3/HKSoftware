#include "stdafx.h"
#include "WzdDlg_ConnectTip.h"
#include "../../iSmartTestWzd/iSmartTestWzdDlg.h"

IMPLEMENT_DYNAMIC(CWzdDlg_ConnectTip, CDialog)

CWzdDlg_ConnectTip::CWzdDlg_ConnectTip(CWnd* pParent /*=NULL*/)
: CDialog(CWzdDlg_ConnectTip::IDD, pParent)
{

}

CWzdDlg_ConnectTip::~CWzdDlg_ConnectTip()
{
}

void CWzdDlg_ConnectTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ICON_TIP, m_btnIcon);
	DDX_Control(pDX, IDC_STATIC_TIP, m_txtTitle);
}

void CWzdDlg_ConnectTip::OnInitialUpdate()
{
	XUI_InitAdjust();
}

void CWzdDlg_ConnectTip::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_txtTitle, 0, 0, 1, 0);
	XUI_AddWnd(&m_btnIcon, 0, 0, 1, 1);

	CXUIAdjItem_Area::XUI_OnSize();
}

BEGIN_MESSAGE_MAP(CWzdDlg_ConnectTip, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CWzdDlg_ConnectTip::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}
