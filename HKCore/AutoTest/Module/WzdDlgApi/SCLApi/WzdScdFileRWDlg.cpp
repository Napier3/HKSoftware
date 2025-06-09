#include "stdafx.h"
#include "WzdScdFileRWDlg.h"
#include "../../../../Module/api/GloblaDrawFunctions.h"


CWzdScdFileRWDlg::CWzdScdFileRWDlg(CWnd* pParent /*=NULL*/)
: CDynDialogEx(pParent)
{
		m_bHasInitDialog = FALSE;
		CRect rect(0,0,335,28);   
		CDynDialogEx::SetDlgRect(rect);     
}

CWzdScdFileRWDlg::~CWzdScdFileRWDlg()
{

}


void CWzdScdFileRWDlg::SetTitle(const CString &strTitle)
{

}

void  CWzdScdFileRWDlg::SetMaxRange(long nMaxRange)
{
	m_prgsScdFileRead.SetRange32(0, nMaxRange);
}

void  CWzdScdFileRWDlg::ResetProcess()
{
	m_prgsScdFileRead.SetPos(0);
}

void  CWzdScdFileRWDlg::StepIt()
{
	m_prgsScdFileRead.StepIt();
}

void  CWzdScdFileRWDlg::ShowMsg(const CString &strMsg)
{
	SetWindowText(strMsg);
}

void CWzdScdFileRWDlg::StartTimer(long nTimerLong)
{

}

BEGIN_MESSAGE_MAP(CWzdScdFileRWDlg, CDynDialogEx)	
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CWzdScdFileRWDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nTimeCout += 1;
	CString strTitle;
	strTitle.Format(_T("%d s"), m_nTimeCout);
	m_stcTime.SetWindowText(strTitle);

	CDynDialogEx::OnTimer(nIDEvent);
}

BOOL CWzdScdFileRWDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();
	

	CreateStatic(m_stcTime,  _T("0 s"), CRect(460,13,500,35), SCDFILE_RW_TIME, this);
	CreateProgressCtrl(m_prgsScdFileRead,CRect(13,13,450,35), SCDFILE_RW_PROGCTRL, this);	

	CFont *pFont = g_pGlobalFont;
	m_stcTime.SetFont(pFont);
	m_prgsScdFileRead.SetFont(pFont);
	m_bHasInitDialog = TRUE;

	CenterWindow();
	m_nTimeCout = 0;
	m_prgsScdFileRead.SetRange32(1,100);
	m_prgsScdFileRead.SetStep(1);
	SetTimer(1, 1000, NULL);
	SetWindowText(_T(""));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWzdScdFileRWDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnCancel();
}

void CWzdScdFileRWDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnOK();
}