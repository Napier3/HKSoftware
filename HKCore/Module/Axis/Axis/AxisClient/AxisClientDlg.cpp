// AxisClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "AxisClientDlg.h"
#include "DescartesAxisDlg.h"
#include "LogarithmAxisDlg.h"
#include "PolarAxisDlg.h"
#include "RulerAxisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxisClientDlg dialog

CAxisClientDlg::CAxisClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAxisClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAxisClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAxisClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAxisClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAxisClientDlg, CDialog)
	//{{AFX_MSG_MAP(CAxisClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DESCARTESAXIS, OnDescartesaxis)
	ON_BN_CLICKED(IDC_POLARAXIS, OnPolaraxis)
	ON_BN_CLICKED(IDC_LOGARITHMAXIS, OnLogarithmaxis)
	ON_BN_CLICKED(IDC_RULERAXIS, OnRuleraxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxisClientDlg message handlers

BOOL CAxisClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAxisClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAxisClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAxisClientDlg::OnDescartesaxis() 
{
	CDescartesAxisDlg dlg;
	dlg.DoModal();
}

void CAxisClientDlg::OnPolaraxis() 
{
	CPolarAxisDlg dlg1;
	dlg1.DoModal();	
}

void CAxisClientDlg::OnLogarithmaxis() 
{
	CLogarithmAxisDlg dlg1;
	dlg1.DoModal();
}

void CAxisClientDlg::OnRuleraxis() 
{
	CRulerAxisDlg dlg1;
	dlg1.DoModal();	
}
