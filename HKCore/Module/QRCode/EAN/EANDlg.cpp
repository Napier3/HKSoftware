// EANDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EAN.h"
#include "EANDlg.h"

#include "..\XBarcodeEan13.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEANDlg dialog

CEANDlg::CEANDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEANDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEANDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEANDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEANDlg)
	DDX_Control(pDX, IDC_COMBO_RATIO, m_cbRatio);
	DDX_Control(pDX, IDC_EDIT_CHECKDIGIT, m_editCheckDigit);
	DDX_Control(pDX, IDC_EDIT_PRODUCT, m_editProduct);
	DDX_Control(pDX, IDC_EDIT_MANUFACTURER, m_editManufacturer);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_editHeight);
	DDX_Control(pDX, IDC_EDIT_GUARDBAR, m_editGuardbarHeight);
	DDX_Control(pDX, IDC_EDIT_COUNTRYCODE, m_editCountryCode);
	DDX_Control(pDX, IDC_COMBO_SYMBOLOGY, m_cbSymbology);
	DDX_Control(pDX, IDC_BITMAPBARCODE, m_staticBitmapBarcode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEANDlg, CDialog)
	//{{AFX_MSG_MAP(CEANDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, OnButtonDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEANDlg message handlers

BOOL CEANDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_cbSymbology.SetCurSel(0);
	m_cbRatio.SetCurSel(m_cbRatio.GetCurSel());

	m_editCountryCode.SetWindowText("75");
	m_editManufacturer.SetWindowText("12345");
	m_editProduct.SetWindowText("67890");

	m_editHeight.SetWindowText("1.5");
	m_editGuardbarHeight.SetWindowText("20");
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEANDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEANDlg::OnPaint() 
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
HCURSOR CEANDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEANDlg::OnButtonDraw() 
{
	// TODO: Add your control notification handler code here

	CXBarcodeEan13 CodeEAN13;
	CString strMessage, strTemp;

	strMessage.Empty();

	m_editCountryCode.GetWindowText(strTemp);
	strMessage += strTemp;

	m_editManufacturer.GetWindowText(strTemp);
	strMessage += strTemp;

	m_editProduct.GetWindowText(strTemp);
	strMessage += strTemp;

	m_editHeight.GetWindowText(strTemp);
	double dHeight = atof(strTemp);

	m_editGuardbarHeight.GetWindowText(strTemp);
	long nGuardbarHeight = atol(strTemp);

	m_cbRatio.GetWindowText(strTemp);
	double dRatio = atof(strTemp);

	HDC hDC = m_staticBitmapBarcode.GetDC()->m_hDC;
	CodeEAN13.LoadData(strMessage,0.02,dHeight,nGuardbarHeight,hDC,0,0,dRatio);

	CodeEAN13.DrawBitmap();
	strTemp.Format("%d",CodeEAN13.CalculateCheckSumDigit());
	m_editCheckDigit.SetWindowText(strTemp);


	xena_WriteXEna13File(_T("D:\\BarcodeEna13.bmp"), strMessage,0.02,dHeight,nGuardbarHeight,dRatio);
}
