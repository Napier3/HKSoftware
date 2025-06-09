// D:\WorkPM\Source\PMTest\Module\Safety\VmSttMacroTestSpyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VmSttMacroTestSpyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CVmSttMacroTestSpyDlg::CVmSttMacroTestSpyDlg(CWnd* pParent /*=NULL*/)
	//: CDialog(CVmSttMacroTestSpyDlg::IDD, pParent)
{

}

CVmSttMacroTestSpyDlg::~CVmSttMacroTestSpyDlg()
{

}

void CVmSttMacroTestSpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVmSttMacroTestSpyDlg, CDynDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CVmSttMacroTestSpyDlg 消息处理程序
BOOL CVmSttMacroTestSpyDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	//progress
	CRect rcWnd(5, 5, 405, 20);
	CreateProgressCtrl(m_wndPrgs, rcWnd, 0x910, this);
	
	//BIN
	
	//Time
	rcWnd.top = rcWnd.bottom + 3;
	rcWnd.bottom = rcWnd.top + 15;
	CreateStatic(m_wndTimerText, _T(""),  rcWnd,  0x911, this);

	CRect rcDlg, rcClient;
	GetWindowRect(rcDlg);
	GetClientRect(rcClient);
	long nHeight = rcDlg.Height() - rcClient.Height();
	
	rcDlg.right = rcDlg.left + 410;
	rcDlg.bottom = nHeight + rcDlg.bottom + 10;
	MoveWindow(rcDlg, FALSE);
	CenterWindow();

	return TRUE;
}

void CVmSttMacroTestSpyDlg::OnCancel()
{
	//CDialog::OnCancel();
}

void CVmSttMacroTestSpyDlg::OnOK()
{
	//CDialog::OnOK();
}

void CVmSttMacroTestSpyDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nCurrTimerID)
	{
		m_fTimerLong += 0.001 * VmSttMacroTestSpyDlg_Timer_Long; //s
		CString strTime;
		strTime.Format(_T("%.3f s"), m_fTimerLong);
		m_wndTimerText.SetWindowText(strTime);
		m_wndPrgs.StepIt();
	}

	CDynDialogEx::OnTimer(nIDEvent);
}


BOOL CVmSttMacroTestSpyDlg::PreTranslateMessage(MSG* pMsg)
{
	return CDynDialogEx::PreTranslateMessage(pMsg);
}


void CVmSttMacroTestSpyDlg::ShowSpy(long nTotalTimeLong)
{
	m_fTimerLong = 0;
	m_wndTimerText.SetWindowText(_T(""));

	if (nTotalTimeLong <= 0)
	{
		nTotalTimeLong = 600;
	}

	m_wndPrgs.SetRange32(0, nTotalTimeLong*2);
	m_wndPrgs.SetStep(1);
	m_wndPrgs.SetPos(0);
	m_nCurrTimerID = SetTimer(VmSttMacroTestSpyDlg_Timer_ID, VmSttMacroTestSpyDlg_Timer_Long, NULL);
	ShowWindow(SW_SHOW);
}

void CVmSttMacroTestSpyDlg::HideSpy()
{
	KillTimer(VmSttMacroTestSpyDlg_Timer_ID);
	m_fTimerLong = 0;
	m_wndTimerText.SetWindowText(_T(""));
	ShowWindow(SW_HIDE);
}

