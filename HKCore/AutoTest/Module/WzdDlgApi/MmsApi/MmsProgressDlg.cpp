#include "stdafx.h"
#include "MmsProgressDlg.h"
#include "afxdialogex.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/XLanguage/XLangWndAdjust.h"

COutputList::COutputList()
{

}

COutputList::~COutputList()
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序
void COutputList::OnEditCopy()
{
}

void COutputList::OnEditClear()
{
	SetWindowText(_T(""));
}

void COutputList::LogString(long nLevel, const char *strMsg)
{
	CString strTemp;
	strTemp = strMsg;
	LogString(nLevel, strTemp);
}

void COutputList::LogString(long nLevel, const CString &strMsg)
{
	UINT nMaxLen = GetLimitText();
	long nLen = strMsg.GetLength();
	long nTotalLen = nLen +   GetWindowTextLength();

	if (nMaxLen <= nTotalLen)
	{
		SetWindowText(_T(""));
	}

	nLen = GetWindowTextLength();
	SetSel(nLen, -1, TRUE);

	CString strTime;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strTime.Format(_T("%d-%d-%d %d:%d:%d-%d : "), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	ReplaceSel(strTime);

	ReplaceSel(strMsg);
	ReplaceSel(_T("\r\n"));
}

IMPLEMENT_DYNAMIC(CMmsProgressDlg, CDialogEx)

CMmsProgressDlg::CMmsProgressDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMmsProgressDlg::IDD, pParent)
{
}

CMmsProgressDlg::~CMmsProgressDlg()
{

}

void CMmsProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_CTRL, m_ProgressCtrl);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_TIMER, m_stcTimer);
	DDX_Control(pDX, IDC_LOG, m_editLog);
}


BEGIN_MESSAGE_MAP(CMmsProgressDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMmsProgressDlg message handlers
BOOL CMmsProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CenterWindow();
	xlang_InitAndAdjust();

	CLogPrint::Create(&m_editLog);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMmsProgressDlg::StartProgress()
{
	ShowWindow(SW_SHOW);
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	SetWindowPos(&wndTopMost, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_SHOWWINDOW);
	CenterWindow();
}

void CMmsProgressDlg::StartTimer(long nTimerLong)
{
	KillTimer(PRGSS_TIMER_ID);

	m_iTimerLongTotal = nTimerLong;
	m_iTimerLongCounter = 0;

	if (m_iTimerLongTotal > 1)
	{
		SetTimer(PRGSS_TIMER_ID, 500, NULL);
	}
}


void CMmsProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_iTimerLongCounter += 500;

	if (m_iTimerLongCounter >= m_iTimerLongTotal)
	{
		KillTimer(PRGSS_TIMER_ID);
	}

	CString strText;
	strText.Format(_T("%d ms"), m_iTimerLongCounter);
	m_stcTimer.SetWindowText(strText);
	// 	CLogPrint::LogString(XLOGLEVEL_TRACE, strText);

	__super::OnTimer(nIDEvent);
}
void CMmsProgressDlg::xlang_InitAndAdjust()
{
	m_stcTitle.SetWindowText("数据操作中...");
	CXLangWndAdjMngr oWndAdjMngr;
	oWndAdjMngr.RegisterCols(); 
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_ProgressCtrl); 
	oWndAdjMngr.RegisterCols(); 
	oWndAdjMngr.RegisterXCol(&m_stcTitle); 
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_stcTimer); 
	oWndAdjMngr.Adjust(this, TRUE);
	SetWindowText("数据操作中...");
}