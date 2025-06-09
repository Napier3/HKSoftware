// RulerAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "RulerAxisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerAxisDlg dialog


CRulerAxisDlg::CRulerAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRulerAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRulerAxisDlg)
	m_bBorder = TRUE;
	m_bHalfScale = TRUE;
	m_bScaleText = TRUE;
	m_bTenthScale = TRUE;
	m_bWorkArea = TRUE;
	//}}AFX_DATA_INIT
	m_IRulerAxis = NULL;
}

void CRulerAxisDlg::InitAxis()
{
	if (!CreateRulerAxisInterface(&m_IRulerAxis))
	{
		MessageBox("create IAxis failed!");
		return;
	}
	
	m_IRulerAxis->SetScaleTextDrawStyle(1);
	COLORREF m_crBack = RGB(255,255,255);
	m_IRulerAxis->SetRulerBackColor((long)m_crBack);

	fHorzRulerValue[0] = fVertRulerValue[0] = -5;
	fHorzRulerValue[1] = fVertRulerValue[1] = 5;
	m_IRulerAxis->SetMinMaxVal(fHorzRulerValue[0],fHorzRulerValue[1],0);

	m_stcHorzFrame.GetWindowRect(&m_rectHorzAxis);
	ScreenToClient(&m_rectHorzAxis);
	m_stcVertFrame.GetWindowRect(&m_rectVertAxis);
	ScreenToClient(&m_rectVertAxis);
	
//	m_IRulerAxis->SetBoder(m_rectVertAxis.left,m_rectVertAxis.top,m_rectVertAxis.right,m_rectVertAxis.bottom);
}

void CRulerAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRulerAxisDlg)
	DDX_Control(pDX, IDC_VERTFRAME, m_stcVertFrame);
	DDX_Control(pDX, IDC_HORZFRAME, m_stcHorzFrame);
	DDX_Check(pDX, IDC_BORDER, m_bBorder);
	DDX_Check(pDX, IDC_HALFSCALE, m_bHalfScale);
	DDX_Check(pDX, IDC_SCALETEXT, m_bScaleText);
	DDX_Check(pDX, IDC_TENTHSCALE, m_bTenthScale);
	DDX_Check(pDX, IDC_WORKAREA, m_bWorkArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRulerAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CRulerAxisDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BORDER, OnBorder)
	ON_BN_CLICKED(IDC_WORKAREA, OnWorkarea)
	ON_BN_CLICKED(IDC_SCALETEXT, OnScaleText)
	ON_BN_CLICKED(IDC_TENTHSCALE, OnTenthScale)
	ON_BN_CLICKED(IDC_HALFSCALE, OnHalfScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRulerAxisDlg message handlers

void CRulerAxisDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_IRulerAxis != NULL)
	{
		CDC *pDC = GetDC();
		long lDC = (long)pDC;
		m_IRulerAxis->SetRulerType(1);
		m_IRulerAxis->SetBoder(m_rectVertAxis.left,m_rectVertAxis.top,m_rectVertAxis.right,m_rectVertAxis.bottom);		
		m_IRulerAxis->DrawAxis(lDC,1,0,0);
		m_IRulerAxis->SetRulerType(0);
		m_IRulerAxis->SetBoder(m_rectHorzAxis.left,m_rectHorzAxis.top,m_rectHorzAxis.right,m_rectHorzAxis.bottom);		
		m_IRulerAxis->DrawAxis(lDC,1,0,0);
		ReleaseDC(pDC);			
	}
}

BOOL CRulerAxisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitAxis();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRulerAxisDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_IRulerAxis != NULL)
	{
		m_IRulerAxis->Release();
	}
	
}

void CRulerAxisDlg::ChangeDrawStype(BOOL bSet,long nStyle)
{
	if (m_IRulerAxis == NULL)
	{
		return ;
	}
	
	if (bSet)
	{
		m_IRulerAxis->SetDrawStyleBit(nStyle);
	}
	else
	{
		m_IRulerAxis->ClearDrawStyleBit(nStyle);
	}
	CRect rectHorz = m_rectHorzAxis;
	rectHorz.InflateRect(2,2,2,2);

	CRect rectVert = m_rectVertAxis;
	rectVert.InflateRect(2,2,2,2);
	
	InvalidateRect(m_rectHorzAxis,true);
	InvalidateRect(m_rectVertAxis,true);
	
}

void CRulerAxisDlg::OnBorder() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bBorder,RULERDRAW_BODER);
	
}

void CRulerAxisDlg::OnWorkarea() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bWorkArea,RULERDRAW_WORKAREA);
	
}

void CRulerAxisDlg::OnScaleText() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bScaleText,RULERDRAW_SCALETEXT);
	
}

void CRulerAxisDlg::OnTenthScale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bTenthScale,RULERDRAW_TENTHSCALE);
	
}

void CRulerAxisDlg::OnHalfScale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bHalfScale,RULERDRAW_HALFSCCALE);
	
}
