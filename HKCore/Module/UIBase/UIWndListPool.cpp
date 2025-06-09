// UIWndListPool.cpp : implementation file
//

#include "stdafx.h"
#include "UIWndListPool.h"

#include "..\..\..\Module\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUIWndListPool dialog


CUIWndListPool::CUIWndListPool(CWnd* pParent /*=NULL*/)//: CDialog(CUIWndListPool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUIWndListPool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bHasInited = FALSE;

	m_crBkColorFrom = RGB(192, 192, 192);
	m_crBkColorTo   = RGB(240, 240, 240);
	m_pDibBack      = NULL;
}


void CUIWndListPool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUIWndListPool)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUIWndListPool, CDialog)
	//ON_WM_SIZE()
	//{{AFX_MSG_MAP(CUIWndListPool)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()	
	//}}AFX_MSG_MAP
	ON_WM_NCHITTEST()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIWndListPool message handlers

BOOL CUIWndListPool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bHasInited = TRUE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUIWndListPool::CreateUIMenDC()
{
//	CDC *pDC = GetDC();
//	CRect	rect;
//	GetClientRect(&rect);
//	
//	if (m_oUIMemDC.Create(pDC, rect))
//	{
//	}
//	else
//	{
//	}
//	
//	GradientFill(m_oUIMemDC.GetDC(), &rect, m_crBkColorFrom, m_crBkColorTo, TRUE);
//	ReleaseDC(pDC);
}

void CUIWndListPool::SetType(const CString &strType)
{
	if (strType == _T("dialog"))
	{
		m_dwPoolType = POOLTYPE_DIALOG;
	}
	else if (strType == _T("child"))
	{
		m_dwPoolType = POOLTYPE_CHILD;
	}
	else 
	{
		m_dwPoolType = POOLTYPE_CHILD;
	}

}

BOOL CUIWndListPool::CreatePool(CWnd *pParent, BOOL &bNeedCenterWnd)
{
	UINT nIDD = UI_GetWndListPoolID(m_dwPoolType);

	Create(nIDD, pParent);

	if (m_dwPoolType == POOLTYPE_DIALOG)
	{
		bNeedCenterWnd = TRUE;
	}
	else
	{
		bNeedCenterWnd = FALSE;
	}

	return bNeedCenterWnd;
}

void CUIWndListPool::OnOK() 
{
	// TODO: Add extra validation here	
//	CDialog::OnOK();
}

void CUIWndListPool::OnCancel() 
{
	// TODO: Add extra cleanup here	
//	CDialog::OnCancel();
}

void CUIWndListPool::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (m_pDibBack == NULL)
	{
		CRect	rect;
		GetClientRect(&rect);
		CUIMemDC oUIMemDC;
		oUIMemDC.Create(&dc, rect);
		
		if (oUIMemDC.GetDC() != NULL)
		{
			GradientFill(oUIMemDC.GetDC(), &rect, m_crBkColorFrom, m_crBkColorTo, TRUE);
			oUIMemDC.Draw(&dc);
		}
	}
	else
	{
		m_pDibBack->Draw(&dc, 0, 0);
	}
}

void CUIWndListPool::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
}

void CUIWndListPool::OnDestroy() 
{
	CDialog::OnDestroy();
}

LRESULT CUIWndListPool::OnNcHitTest(CPoint point)
{
	if (m_dwPoolType == POOLTYPE_DIALOG)
	{
		CDialog::OnNcHitTest(point);
		return HTCAPTION;
	}

	return CDialog::OnNcHitTest(point);
}

void CUIWndListPool::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if (m_dwPoolType == POOLTYPE_DIALOG)
	{
		nHitTest = HTCAPTION;
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CUIWndListPool::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (m_dwPoolType == POOLTYPE_DIALOG)
	{
		nHitTest = HTCAPTION;
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}
