// CharElementInvIACDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementInvIACDlg.h"


// CCharElementInvIACDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementInvIACDlg, CDialog)

CCharElementInvIACDlg::CCharElementInvIACDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementInvIACDlg::IDD, pParent)
	, m_strTp(_T(""))
	, m_strA(_T(""))
	, m_strB(_T(""))
	, m_strC(_T(""))
	, m_strD(_T(""))
	, m_strE(_T(""))
	, m_strBeta(_T(""))
{

}

CCharElementInvIACDlg::~CCharElementInvIACDlg()
{
}

void CCharElementInvIACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IAC_TP, m_strTp);
	DDX_Text(pDX, IDC_IAC_A, m_strA);
	DDX_Text(pDX, IDC_IAC_B, m_strB);
	DDX_Text(pDX, IDC_IAC_C, m_strC);
	DDX_Text(pDX, IDC_IAC_D, m_strD);
	DDX_Text(pDX, IDC_IAC_E, m_strE);
	DDX_Text(pDX, IDC_IAC_BETA, m_strBeta);
}


BEGIN_MESSAGE_MAP(CCharElementInvIACDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCharElementInvIACDlg 消息处理程序
BOOL CCharElementInvIACDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if( m_bmp.m_hObject != NULL )//判断
		m_bmp.DeleteObject();
	/////////载入图片
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), 
		_T("res/IAC.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if( hbmp == NULL ) 
	{
		return FALSE;
	}
	///////////////////////该断程序用来取得加载的BMP的信息////////////////////////
	m_bmp.Attach( hbmp );
	DIBSECTION ds;
	BITMAPINFOHEADER &bminfo = ds.dsBmih; 
	m_bmp.GetObject( sizeof(ds), &ds );
	int cx=bminfo.biWidth;  //得到图像宽度
	int cy=bminfo.biHeight; //得到图像高度
	/////////////////// ////////////////////////////////
	/////////////得到了图像的宽度和高度后,我们就可以对图像大小进行适应,即调整控件的大小,让它正好显示一张图片///////////////////////////
	CRect rect;
	GetDlgItem(IDC_IAC_PIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	GetDlgItem(IDC_IAC_PIC)->MoveWindow(rect.left,rect.top,cx,cy,true);//调整大小
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCharElementInvIACDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementInvIACDlg::ShowData()
{
	CCharElementIAC * pCharData= (CCharElementIAC *) m_pCharElementBase;

	m_strTp = pCharData->m_strTp;
	m_strA = pCharData->m_strA;
	m_strB = pCharData->m_strB;
	m_strC = pCharData->m_strC;
	m_strD = pCharData->m_strD;
	m_strE = pCharData->m_strE;
	m_strBeta = pCharData->m_strBeta;

	UpdateData(FALSE);
}

void CCharElementInvIACDlg::GetData()
{
	CCharElementIAC * pCharData= (CCharElementIAC *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strTp = m_strTp;
	pCharData->m_strA = m_strA;
	pCharData->m_strB = m_strB;
	pCharData->m_strC = m_strC;
	pCharData->m_strD = m_strD;
    pCharData->m_strE = m_strE;
	pCharData->m_strBeta = m_strBeta;
}

BOOL CCharElementInvIACDlg::IsEnable()
{
	if (m_strTp.IsEmpty())
	{
		return FALSE;
	}

	if (m_strA.IsEmpty())
	{
		return FALSE;
	}

	if (m_strB.IsEmpty())
	{
		return FALSE;
	}

	if (m_strC.IsEmpty())
	{
		return FALSE;
	}

	if (m_strD.IsEmpty())
	{
		return FALSE;
	}

	if (m_strE.IsEmpty())
	{
		return FALSE;
	}

	if (m_strBeta.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

void CCharElementInvIACDlg::OnPaint() 
{
	//////////////以下三种情况任选一种会是不同效果(只能一种存在)///////////
	//CPaintDC dc(this);      //若用此句,得到的是对话框的DC,图片将被绘制在对话框上.
	CPaintDC dc(GetDlgItem(IDC_IAC_PIC)); //用此句,得到picture控件的DC,图像将被绘制在控件上  
	//  CDC dc;
	//  dc.m_hDC=::GetDC(NULL);  //若用此两句,得到的是屏幕的DC,图片将被绘制在屏幕上///////////////////////////////////////////////////////
	CRect rcclient;
	GetDlgItem(IDC_IAC_PIC)->GetClientRect(&rcclient);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);  
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
	memdc.SelectObject( &bitmap );
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC , 0);
	CDC maskdc;
	maskdc.CreateCompatibleDC(&dc);
	CBitmap maskbitmap;
	maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL);
	maskdc.SelectObject( &maskbitmap );
	maskdc.BitBlt( 0, 0, rcclient.Width(), rcclient.Height(), &memdc, 
		rcclient.left, rcclient.top, SRCCOPY);
	CBrush brush;
	brush.CreatePatternBrush(&m_bmp);
	dc.FillRect(rcclient, &brush);  
	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), 
		&memdc, rcclient.left, rcclient.top,SRCPAINT);
	brush.DeleteObject();
	// Do not call CDialog::OnPaint() for painting messages
}
