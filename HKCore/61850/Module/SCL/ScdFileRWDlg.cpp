#include "stdafx.h"
#include "ScdFileRWDlg.h"
#include "..\..\..\Module\api\GloblaDrawFunctions.h"


CScdFileRWDlg::CScdFileRWDlg(CWnd* pParent /*=NULL*/)
: CDynDialogEx(pParent)
{
		m_bHasInitDialog = FALSE;
		CRect rect(0,0,335,28);   
		CDynDialogEx::SetDlgRect(rect);     
}

CScdFileRWDlg::~CScdFileRWDlg()
{

}


void CScdFileRWDlg::SetTitle(const CString &strTitle)
{

}

void  CScdFileRWDlg::SetMaxRange(long nMaxRange)
{
	m_prgsScdFileRead.SetRange32(0, nMaxRange);
}

void  CScdFileRWDlg::ResetProcess()
{
	m_prgsScdFileRead.SetPos(0);
}

void  CScdFileRWDlg::StepIt()
{
	m_prgsScdFileRead.StepIt();
}

void  CScdFileRWDlg::ShowMsg(const CString &strMsg)
{
	SetWindowText(strMsg);
}

void CScdFileRWDlg::StartTimer(long nTimerLong)
{

}


BEGIN_MESSAGE_MAP(CScdFileRWDlg, CDynDialogEx)	
	ON_WM_TIMER()
END_MESSAGE_MAP()





void CScdFileRWDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nTimeCout += 1;
	CString strTitle;
	strTitle.Format(_T("%d s"), m_nTimeCout);
	m_stcTime.SetWindowText(strTitle);

	CDynDialogEx::OnTimer(nIDEvent);
}

BOOL CScdFileRWDlg::OnInitDialog()
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

void CScdFileRWDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnCancel();
}

void CScdFileRWDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnOK();
}