// GridCtrlClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GridCtrlClient.h"
#include "GridCtrlClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlClientDlg dialog

CGridCtrlClientDlg::CGridCtrlClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridCtrlClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridCtrlClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridCtrlClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlClientDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGridCtrlClientDlg, CDialog)
	//{{AFX_MSG_MAP(CGridCtrlClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MERGE, OnBtnMerge)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_DESTROY, OnButtonDestroy)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GVN_GRIDDBCLICK, (IDC_CUSTOM1+1000), OnGridDoubleClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlClientDlg message handlers

LRESULT CGridCtrlClientDlg::OnGridDoubleClick(WPARAM wParam, LPARAM lParam)
{
	NM_GRIDVIEW *nmgv = (NM_GRIDVIEW*)lParam;
	nmgv = (NM_GRIDVIEW*)wParam;
	CWnd *pWnd = (CWnd*)lParam;

	return 0;
}

BOOL CGridCtrlClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CreateGrid();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGridCtrlClientDlg::CreateGrid()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = 5;
	rcClient.top = 5;
	rcClient.right -= 5;
	rcClient.bottom -= 50;
	m_gridex.Create(rcClient, this, IDC_CUSTOM1+1000);
	m_gridex.InitGrid(60);
	//m_gridex.CreateTitleTip();
	m_gridex.InitData();
	m_gridex.SelectRow(4);	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridCtrlClientDlg::OnPaint() 
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
HCURSOR CGridCtrlClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGridCtrlClientDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CGridCtrlClientDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CGridCtrlClientDlg::OnBtnMerge() 
{
	CGridCellRange oRange = m_gridex.GetSelectedCellRange();
	oRange.Merge(TRUE);
	m_gridex.Invalidate();
}

void CGridCtrlClientDlg::OnButtonCreate() 
{
	// TODO: Add your control notification handler code here
	
}

void CGridCtrlClientDlg::OnButtonDestroy() 
{
	// TODO: Add your control notification handler code here
	
}
