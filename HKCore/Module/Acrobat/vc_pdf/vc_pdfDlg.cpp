// vc_pdfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vc_pdf.h"
#include "vc_pdfDlg.h"
#include "../acrobat.h"
#include <string>

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
// CVc_pdfDlg dialog

CVc_pdfDlg::CVc_pdfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVc_pdfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVc_pdfDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVc_pdfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVc_pdfDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVc_pdfDlg, CDialog)
	//{{AFX_MSG_MAP(CVc_pdfDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVc_pdfDlg message handlers

BOOL CVc_pdfDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVc_pdfDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVc_pdfDlg::OnPaint() 
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
HCURSOR CVc_pdfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#include "../PdfFileToText.h"


bool PdfToTxt(const CString &strPdfFile)
{	
	int i = 0;
	i = strPdfFile.ReverseFind('.');

	if (i < 0)
	{
		return false;
	}

	CString TxtFileName;
	TxtFileName = strPdfFile.Left(i+1);
	TxtFileName += _T("txt");
	
		FILE *fp = fopen(TxtFileName,"wb");
		if (fp==NULL)
			return false;

		COleException e;

		Adobe::CAcroApp app;
		app.CreateDispatch("AcroExch.App",&e);

		Adobe::CAcroHiliteList hl;
		hl.CreateDispatch("AcroExch.HiliteList",&e);
		hl.Add(0,32767);//范围是从0到最大

		Adobe::CAcroPDDoc pddoc;
		pddoc.CreateDispatch("AcroExch.PDDoc",&e);

		try{

			if(!pddoc.Open(strPdfFile))  
			{   
				app.ReleaseDispatch();
				pddoc.ReleaseDispatch();
				return false;
			}

			Adobe::CAcroPDPage pdp;
			Adobe::CAcroPDTextSelect pdts;
			long pagenums = pddoc.GetNumPages();//页数
			CString strText;

			for(i=0; i<pagenums; i++)
			{
				pdp = pddoc.AcquirePage(i);
				pdts = pdp.CreateWordHilite(hl);
				long n = pdts.GetNumText();	/*char buf[32];	MessageBox(itoa(n,buf,10));	显示选中的字符数*/

				for(long j=0; j<n; j++)
				{
					strText = pdts.GetText(j);
					//AfxMessageBox((LPSTR)(LPCTSTR)pdts.GetText(j));
					fputs((LPSTR)(LPCTSTR)strText, fp);
				}
			}
		}
		catch (...) {
			fclose(fp);
			pddoc.Close();
			pddoc.ReleaseDispatch();
			hl.ReleaseDispatch();
			app.Exit();
			app.ReleaseDispatch();
			return false;
		}

		fclose(fp);
		pddoc.Close();
		pddoc.ReleaseDispatch();
		hl.ReleaseDispatch();
		app.Exit();
		app.ReleaseDispatch();
		return true;
}

void CVc_pdfDlg::OnButton1() 
{
	CString strPath;
	CFileDialog dlg(TRUE, _T("pdf"), NULL
		, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST
		, _T("pdf文件(*.pdf)|*.pdf||"), this); 

	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	
	strPath = dlg.GetPathName();

		if (PdfToTxt(strPath)) 
			MessageBox("OK.");
		else
			MessageBox("failed.");
}

void CVc_pdfDlg::OnOK() 
{
	CDialog::OnOK();
}

void CVc_pdfDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
