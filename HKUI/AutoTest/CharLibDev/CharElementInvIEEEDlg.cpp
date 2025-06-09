// CharElementInvIEEEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementInvIEEEDlg.h"


// CCharElementInvIEEEDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementInvIEEEDlg, CDialog)

CCharElementInvIEEEDlg::CCharElementInvIEEEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementInvIEEEDlg::IDD, pParent)
	, m_strTP(_T(""))
	, m_strA(_T(""))
	, m_strB(_T(""))
	, m_strP(_T(""))
	, m_strQ(_T(""))
	, m_strK1(_T(""))
	, m_strK2(_T(""))
{

}

CCharElementInvIEEEDlg::~CCharElementInvIEEEDlg()
{
}

void CCharElementInvIEEEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IEEE_TP, m_strTP);
	DDX_Text(pDX, IDC_IEEE_A, m_strA);
	DDX_Text(pDX, IDC_IEEE_B, m_strB);
	DDX_Text(pDX, IDC_IEEE_P, m_strP);
	DDX_Text(pDX, IDC_IEEE_Q, m_strQ);
	DDX_Text(pDX, IDC_IEEE_K1, m_strK1);
	DDX_Text(pDX, IDC_IEEE_K2, m_strK2);
}


BEGIN_MESSAGE_MAP(CCharElementInvIEEEDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCharElementInvIEEEDlg 消息处理程序
BOOL CCharElementInvIEEEDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if( m_bmp.m_hObject != NULL )//判断
		m_bmp.DeleteObject();
	/////////载入图片
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), 
		_T("res/IEEE.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
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
	GetDlgItem(IDC_IEEE_PIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	GetDlgItem(IDC_IEEE_PIC)->MoveWindow(rect.left,rect.top,cx,cy,true);//调整大小
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCharElementInvIEEEDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementInvIEEEDlg::ShowData()
{
	CCharElementIEEE * pCharData= (CCharElementIEEE *) m_pCharElementBase;

	m_strTP = pCharData->m_strTp;
	m_strA = pCharData->m_strA;
	m_strB = pCharData->m_strB;
	m_strP = pCharData->m_strP;
	m_strQ = pCharData->m_strQ;
	m_strK1 = pCharData->m_strK1;
	m_strK2 = pCharData->m_strK2;

	UpdateData(FALSE);
}

void CCharElementInvIEEEDlg::GetData()
{
	CCharElementIEEE * pCharData= (CCharElementIEEE *) m_pCharElementBase;

	UpdateData(TRUE);

	pCharData->m_strTp = m_strTP;
	pCharData->m_strA = m_strA;
	pCharData->m_strB = m_strB;
	pCharData->m_strP = m_strP;
	pCharData->m_strQ = m_strQ;
	pCharData->m_strK1 = m_strK1;
	pCharData->m_strK2 = m_strK2;
}

BOOL CCharElementInvIEEEDlg::IsEnable()
{
	if (m_strTP.IsEmpty())
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

	if (m_strP.IsEmpty())
	{
		return FALSE;
	}

	if (m_strQ.IsEmpty())
	{
		return FALSE;
	}

	if (m_strK1.IsEmpty())
	{
		return FALSE;
	}

	if (m_strK2.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

void CCharElementInvIEEEDlg::OnPaint() 
{
	//////////////以下三种情况任选一种会是不同效果(只能一种存在)///////////
	//CPaintDC dc(this);      //若用此句,得到的是对话框的DC,图片将被绘制在对话框上.
	CPaintDC dc(GetDlgItem(IDC_IEEE_PIC)); //用此句,得到picture控件的DC,图像将被绘制在控件上  
	//  CDC dc;
	//  dc.m_hDC=::GetDC(NULL);  //若用此两句,得到的是屏幕的DC,图片将被绘制在屏幕上///////////////////////////////////////////////////////
	CRect rcclient;
	GetDlgItem(IDC_IEEE_PIC)->GetClientRect(&rcclient);
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
