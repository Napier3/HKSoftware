// ThreadProgrssDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadProgrssDlg.h"
#include "..\API\GloblaDrawFunctions.h"

// CThreadProgrssDlg dialog

CThreadProgrssDlg::CThreadProgrssDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
}

CThreadProgrssDlg::~CThreadProgrssDlg()
{
	
}

void CThreadProgrssDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if (!::IsWindow(m_ProgressCtrl.m_hWnd))
	{
		return;
	}

	DDX_Control(pDX, XIDC_PROGRESS_CTRL, m_ProgressCtrl);
	DDX_Control(pDX, XIDC_STATIC_TITLE, m_stcTitle);
}


BEGIN_MESSAGE_MAP(CThreadProgrssDlg, CDynDialogEx)
END_MESSAGE_MAP()


// CThreadProgrssDlg message handlers
BOOL CThreadProgrssDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();
	
	CreateProgressCtrl(m_ProgressCtrl, CRect (12, 12, 542, 31), XIDC_PROGRESS_CTRL, this);
	CreateStatic(m_stcTitle, _T(""), CRect (12, 43, 542, 57), XIDC_STATIC_TITLE, this);

	m_stcTitle.SetFont(g_pGlobalFont);

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CThreadProgrssDlg::StartProgress()
{
	ShowWindow(SW_SHOW);
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	SetWindowPos(&wndTopMost, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_SHOWWINDOW);
	CenterWindow();
}


int CThreadProgrssDlg::DoModal()   
{   
	CRect rect(0,0,368,47);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST_DATAS);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNCREATE(CThreadProgressBase, CWinThread)

CThreadProgressBase::CThreadProgressBase()
{
	m_pProgressDlg = NULL;
	memset(m_pszMessage, 0, 4096);
	m_nMaxRange = 100;
	m_pParentWnd = NULL;
}


CThreadProgressBase::~CThreadProgressBase()
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}
}


BOOL CThreadProgressBase::InitInstance()
{
	CWnd *pWnd = CWnd::GetDesktopWindow();
	CThreadProgrssDlg *pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	pProgressDlg->SetMaxRange(m_nMaxRange);

	m_pProgressDlg = pProgressDlg;
	m_pProgressDlg->ShowWindow(SW_HIDE);

	return TRUE;
}

int CThreadProgressBase::ExitInstance()
{
	int nReturn = CWinThread::ExitInstance();

	return nReturn;
}


BEGIN_MESSAGE_MAP(CThreadProgressBase, CWinThread)
	//{{AFX_MSG_MAP(CThreadProgressBase)
	ON_THREAD_MESSAGE(WM_USER + 2355, On2355)
	ON_THREAD_MESSAGE(WM_USER + 2356, On2356)
	ON_THREAD_MESSAGE(WM_USER + 2357, On2357)
	ON_THREAD_MESSAGE(WM_USER + 2358, On2358)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadProgressBase message handlers

void CThreadProgressBase::On2355(WPARAM wParam, LPARAM lParam)
{
	m_nMaxRange = wParam;

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ShowWindow(SW_SHOW);
		m_pProgressDlg->SetMaxRange(wParam);
		m_pProgressDlg->ResetProcess();
		CRect rc;
		m_pProgressDlg->GetWindowRect(&rc);
		m_pProgressDlg->SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}
}

void CThreadProgressBase::On2356(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ResetProcess();
	}
}

void CThreadProgressBase::On2357(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		//m_pProgressDlg->StepIt();
		m_pProgressDlg->StepPos(m_nStepIndex);
	}
}

void CThreadProgressBase::On2358(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		CString strMsg ;
		strMsg = m_pszMessage;
		m_pProgressDlg->ShowMsg(strMsg);
	}
}
