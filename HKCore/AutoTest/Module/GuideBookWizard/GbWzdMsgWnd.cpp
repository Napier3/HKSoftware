// GbWzdMsgWnd.cpp: implementation of the CGbWzdMsgWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GbWzdMsgWnd.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"
#include "GuideBookWizard.h"
#include "..\XLanguageResourceAts.h"

#define IDC_BTN_OK			1045	//OK��ť
// #define IDC_BTN_CLOSE		1046	//�رհ�ť
// #define IDC_BTN_MINMIE		1047	//��С����ť
// #define IDC_BTN_PUSHPIN		1048	//�̶���ť
#define IDC_EDIT_MESSAGE		1049	//�ı���Ϣ��
// #define IDC_LISTBOX_INFOR_LIJQ	1050	//�б��
// #define IDC_TESTRESULT_SAVE_LIJQ	1051	//���水ť

#define CX_ROUNDED				12		// Tip horizontal roundness
#define CY_ROUNDED				10		// Tip vertical roundness
#define CX_LEADER				0		// Width of tip lead
#define CY_LEADER				0		// Height of tip lead
#define CX_ICON_MARGIN			5		// Width of margin between icon and tip text
#define CY_TITLEBAR				20		//������
#define CY_OKBUTTON				16		//��ť����
#define CX_CONTROLSGAP			4		//�ؼ�֮��ļ��--ˮƽ
#define CY_CONTROLSGAP			4		//�ؼ�֮��ļ��--��ֱ

#define CNLN_WIDTH				355		//����ͼ���
#define CNLN_HEIGHT				280		//����ͼ�߶�

#define WNDSIZE_MAXWIDTH		400		//��������������
#define WNDSIZE_MINWIDTH		162		//�����������С���
#define WNDSIZE_MAXEIGHT		320		//������������߶�

#define ICON_SIZE_WIDTHHEIGHT	17		//ͼ��ť�ĸ߶ȿ��

#define TIMER_MOUSELEAVE	0X65
#define TIMEVAL_MOUSELEAVE	50

#define	PWAGENTWND_TITLETXTCOLOR	(RGB(0,41,96))
#define	PWAGENTWND_TITLEFONTHEIGHT	14


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGbWzdMsgWnd::CGbWzdMsgWnd()
{
	m_szClass = AfxRegisterWndClass(0);

	m_ptOrigin.x = 0;
	m_ptOrigin.y = 0;

	m_pFont  = new CFont ;
	m_lfLogFont = InitLogFont();

#ifdef _UNICODE
	wcscpy(m_lfLogFont.lfFaceName, L"����");
#else
	strcpy(m_lfLogFont.lfFaceName,"����");
#endif

	m_lfLogFont.lfHeight = 14;
	m_lfLogFont.lfWeight = 400;
	m_pFont->CreateFontIndirect(&m_lfLogFont);

	m_bMouseOverWnd= FALSE;
	m_bMouseTracking = FALSE;
	m_ptMouseMove = CPoint(0,0);
}

CGbWzdMsgWnd::~CGbWzdMsgWnd()
{
	if(m_pFont != NULL)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
}

// Message map
BEGIN_MESSAGE_MAP(CGbWzdMsgWnd, CWnd)
	//{{AFX_MSG_MAP(CGbWzdMsgWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CGbWzdMsgWnd::Create(CWnd* pParentWnd) 
{
	BOOL	bSuccess;

	ASSERT(pParentWnd != NULL);
	bSuccess = CreateEx(NULL, m_szClass, NULL, WS_POPUP, 0, 0, 0, 0, pParentWnd->GetSafeHwnd(), NULL, NULL);


	return bSuccess;
}

void CGbWzdMsgWnd::EnableNextButton(BOOL bEnable)
{
	if (::IsWindow(m_btnOk.m_hWnd))
	{
		m_btnOk.EnableWindow(bEnable);
	}
}

int CGbWzdMsgWnd::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
		return -1;

	short	shBtnColor = 30;
	//�ô���Ϊ�����ʾ
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	CRect rect(0,0,40,20);
	m_btnOk.Create(/*_T("��һ��")*/g_sLangTxt_NextStep,WS_CHILD,rect,this,IDC_BTN_OK);
	m_btnOk.SetFont(m_pFont);
	m_btnOk.SetTooltipText(/*_T("������뵽�򵼵���һ����")*/g_sLangTxt_ClickToNextStep);

	DWORD dwStyle = ES_LEFT |ES_MULTILINE|WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER;
	m_editSafety.Create(dwStyle,rect,this,IDC_EDIT_MESSAGE);
	m_editSafety.SetFont(m_pFont);

	SetAllButtonsColor();

	return 0;
}


void CGbWzdMsgWnd::SetAllButtonsColor()
{
	//BTNST_COLOR_BK_IN	= 0,		// Background color when mouse is INside
	m_btnOk.SetColor(0,RGB(255,255,204),FALSE);
	//BTNST_COLOR_FG_IN,				// Text color when mouse is INside
	m_btnOk.SetColor(1,RGB(255,0,0),FALSE);
	//BTNST_COLOR_BK_OUT,				// Background color when mouse is OUTside
	m_btnOk.SetColor(2,RGB(255,255,204),FALSE);
	//BTNST_COLOR_FG_OUT,				// Text color when mouse is OUTside
	m_btnOk.SetColor(3,RGB(0,0,0),FALSE);
	//BTNST_COLOR_BK_FOCUS,			// Background color when the button is focused
	m_btnOk.SetColor(4,RGB(255,255,204),FALSE);
	//BTNST_COLOR_FG_FOCUS,			// Text color when the button is focused
	m_btnOk.SetColor(5,RGB(255,0,0),FALSE);
	m_btnOk.DrawBorder(TRUE,FALSE);
	m_btnOk.SetFlat(TRUE,FALSE);
}


void CGbWzdMsgWnd::OnBtnOk()
{
	CGuideBookWizard::ExecNext(WZDEXEC_STEP);
}

void CGbWzdMsgWnd::OnPaint() 
{
	CPaintDC dc( this ); // device context for painting

	CRect	rc;
	CBrush	WindowBrush;
	CBrush	FrameBrush;
	CBrush	InnerFrameBrush;
	HRGN	hRegion;
	CRgn	*pRegion;

	//��ÿͻ�������
	GetClientRect(rc);
	//��������
	InnerFrameBrush.CreateSolidBrush(::GetSysColor(COLOR_SCROLLBAR));
	FrameBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
//	WindowBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
	WindowBrush.CreateSolidBrush(RGB(255,255,204));
	//��ô��ڵ�����
	GetWindowRegion(&dc, &hRegion);
	pRegion = CRgn::FromHandle(hRegion);
	//���Ʊ߿�
	dc.FillRgn(pRegion, &WindowBrush);
	dc.FrameRgn(pRegion, &InnerFrameBrush, 3, 3);
	dc.FrameRgn(pRegion, &FrameBrush, 1, 1);
	::DeleteObject(hRegion);

	{
		LOGFONT lfLogFont = InitLogFont();
#ifdef _UNICODE
		wcscpy(lfLogFont.lfFaceName, L"����");
#else
		strcpy(lfLogFont.lfFaceName, "����");
#endif
		lfLogFont.lfHeight = PWAGENTWND_TITLEFONTHEIGHT;
		lfLogFont.lfWeight = 600;
		CFont *pFont = new CFont;
		pFont->CreateFontIndirect(&lfLogFont);
		CFont *pOldFont = dc.SelectObject(pFont);
		//���Ʊ���
		int iWidth = rc.Width();
		rc.top = CY_ROUNDED/2;
		rc.bottom = rc.top + CY_TITLEBAR;
		rc.left  = CX_ROUNDED + CX_CONTROLSGAP;
		rc.right = iWidth-CX_ROUNDED;
		COLORREF crOld = dc.SetTextColor(PWAGENTWND_TITLETXTCOLOR);
		dc.SetBkMode(TRANSPARENT);
	//	dc.Rectangle(rc);
		dc.DrawText(/*_T("������ɣ��������һ������ť")*/g_sLangTxt_OperCompleteToNext,rc,DT_CENTER | DT_SINGLELINE);
		dc.SelectObject(pOldFont);
		dc.SetTextColor(crOld);
		pFont->DeleteObject();
		delete pFont;
	}		//���Ʊ���
}


BOOL CGbWzdMsgWnd::GetWindowRegion(CDC* pDC, HRGN* hRegion, CSize *Size /* = NULL */)
{
	CSize szEdit = GetWndSizeBySafetyData(pDC);

	CRect	rcWnd(0,0,szEdit.cx,szEdit.cy);
	CRgn	LeaderRegion;
	CRgn	CaptionRegion;
	
	ASSERT(pDC != NULL);
	ASSERT(hRegion != NULL);

	//������
	rcWnd.bottom += CY_TITLEBAR;
	//���Ӱ�ť��λ��
	rcWnd.bottom += CY_OKBUTTON;
	//Ϊ����Բ�ǵ�������
	rcWnd.InflateRect(CX_ROUNDED, CY_ROUNDED);

	//������������
	CaptionRegion.CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), CX_ROUNDED, CY_ROUNDED);
	//��������ͷָ�򡱵�����������
//	LeaderRegion.CreatePolygonRgn(ptLeader, 3, ALTERNATE);
	//������������
	LeaderRegion.CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), CX_ROUNDED, CY_ROUNDED);
	//������������
	*hRegion =  ::CreateRectRgn(0, 0, rcWnd.Width(), rcWnd.Height() + CY_LEADER);
	//���Rgn
	CombineRgn(*hRegion, CaptionRegion.operator HRGN(), LeaderRegion.operator HRGN(), RGN_OR);
//	CombineRgn(*hRegion, CaptionRegion.operator HRGN(), *hRegion, RGN_OR);
//	*hRegion = CaptionRegion.operator HRGN();
	// Set the window size
	if (Size != NULL)
	{
		Size->cx	= rcWnd.Width();
		Size->cy	= rcWnd.Height();
	}

	return TRUE;
}

CSize CGbWzdMsgWnd::GetWndSizeBySafetyData(CDC* pDC)
{
	CSize szWnd(0, 0);
	CRect rectData(0, 0, 0, 0);
	int iCharWidth = 0;
	int iWidth = 0;
	int iHeight = 0;
	int iRows = 0;
	int iTemp = 0;

	//�������ֵ��������
	CFont	*pSysFont;
	ASSERT(pDC != NULL);

	// Calculate the are for the tip text
	pSysFont = pDC->SelectObject(m_pFont);
	pDC->DrawText(m_strMsgText, &rectData, DT_CALCRECT);
	pDC->SelectObject(pSysFont);
	
	iWidth = rectData.Width();
	iCharWidth = iWidth / m_strMsgText.GetLength();
	iCharWidth *= 4;
	iHeight = rectData.Height();
	iRows = iWidth / WNDSIZE_MAXWIDTH;
	iTemp = iWidth - iRows * WNDSIZE_MAXWIDTH;
	if(iTemp > 0)
		iRows++;

	szWnd.cx = WNDSIZE_MAXWIDTH+iCharWidth;
	if(WNDSIZE_MINWIDTH > iWidth)
		szWnd.cx = WNDSIZE_MINWIDTH+iCharWidth;

	if(iRows == 1)
	{
		if(iWidth < WNDSIZE_MAXWIDTH)
			szWnd.cx = iWidth+iCharWidth;
	}

//	iRows++;
	szWnd.cy = iHeight + 14 * iRows;

	if(szWnd.cy > WNDSIZE_MAXEIGHT)
		szWnd.cy = WNDSIZE_MAXEIGHT;
	if(szWnd.cx < WNDSIZE_MAXWIDTH)
		szWnd.cx = WNDSIZE_MAXWIDTH;

	return szWnd;
}

void CGbWzdMsgWnd::RepositionAllButtons(CRect rectWnd)
{
	CRect rectPos(rectWnd);

	//ȷ����ť
	CPoint ptCenter = rectPos.CenterPoint();
	rectPos.bottom = rectPos.bottom - CY_ROUNDED / 2;
	rectPos.top = rectPos.bottom - CY_OKBUTTON;
	rectPos.left = ptCenter.x - 30;
	rectPos.right = ptCenter.x + 30;
	m_btnOk.MoveWindow(&rectPos,TRUE);
	m_btnOk.ShowWindow(SW_SHOW);
	//��ȫ��ʩEdit�ؼ�
	rectPos = rectWnd;
	rectPos.left = CX_ROUNDED;
	rectPos.top = CY_ROUNDED+CY_TITLEBAR;
	rectPos.bottom = rectWnd.bottom - CY_ROUNDED - CY_OKBUTTON - CY_CONTROLSGAP;
	rectPos.right = rectWnd.right - CX_ROUNDED;
	m_editSafety.MoveWindow(&rectPos,TRUE);
	m_editSafety.ShowWindow(SW_SHOW);	
}

void CGbWzdMsgWnd::ShowMsgString(const CString &strMsg)
{
	if (!::IsWindowVisible(m_hWnd))
	{	
		ShowWindow(SW_SHOW);
		//CenterWindow();
	}

	m_strMsgText.Empty();
	InitMsgString(strMsg);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	Show(rcWnd.TopLeft());
}

void CGbWzdMsgWnd::InitRight(long nRight)
{
	CRect rc;
	if (nRight >= WNDSIZE_MAXWIDTH )
	{
		rc.left = nRight - WNDSIZE_MAXWIDTH;
	}

	rc.top = 10;
	rc.right = rc.left + WNDSIZE_MAXWIDTH;
	rc.bottom = CY_TITLEBAR + CY_OKBUTTON + CY_ROUNDED * 2;
	MoveWindow(&rc, FALSE);
}

void CGbWzdMsgWnd::InitMsgString(const CString &strData)
{
	m_strMsgText += strData;
	//m_strMsgText += _T("\r\n");
	m_editSafety.SetWindowText(m_strMsgText);
}

void CGbWzdMsgWnd::Show(CPoint ptOrigin)
{
	HRGN	hRegion;
	CSize	WindowSize;
	CDC		*pDC;
	int x, y;

	m_ptOrigin = ptOrigin;
	pDC = GetDC();
	GetWindowRegion(pDC, &hRegion, &WindowSize);
	ReleaseDC(pDC);
	::SetWindowRgn(m_hWnd, hRegion, TRUE);
	/* Added */
	x = m_ptOrigin.x - WindowSize.cx + CX_ROUNDED;
	y = m_ptOrigin.y - WindowSize.cy + CY_ROUNDED;

	if (x < 0)
		m_ptOrigin.x = 20;
	if (y < 0)
		m_ptOrigin.y = 20;

	SetWindowPos(&wndTopMost, m_ptOrigin.x, m_ptOrigin.y, WindowSize.cx, 
		WindowSize.cy, SWP_NOACTIVATE);

	//CenterWindow();
	RepositionAllButtons(CRect(0,0,WindowSize.cx,WindowSize.cy));

	Invalidate(TRUE);
}

void CGbWzdMsgWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bMouseTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		if(::_TrackMouseEvent(&tme))
		{
			m_bMouseTracking = TRUE;
			if(!m_bMouseOverWnd)
			{
				m_bMouseOverWnd = TRUE;
			}
		}
	}
	m_ptMouseMove = point;
	CWnd::OnMouseMove(nFlags, point);
	//SetCursor(m_hLoadCursor);
}

LRESULT CGbWzdMsgWnd::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	m_bMouseTracking = FALSE;
	SetTimer(TIMER_MOUSELEAVE,TIMEVAL_MOUSELEAVE,NULL);
	return TRUE;
}

void CGbWzdMsgWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

void CGbWzdMsgWnd::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case TIMER_MOUSELEAVE:
		{
			CRect rectWnd;
			GetWindowRect(&rectWnd);
			CPoint point;
			GetCursorPos(&point);
			if(!rectWnd.PtInRect(point))
			{
				m_bMouseOverWnd = FALSE;
				KillTimer(TIMER_MOUSELEAVE);
			}
		}
		break;
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}


void CGbWzdMsgWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == 27)
	{
	}
	if(nChar == 20)
	{
	}
}

BOOL CGbWzdMsgWnd::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bClose = FALSE;
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
	case WM_KEYLAST:
		bClose = TRUE;
		break;
	default:
		break;
	}

	return CWnd::PreTranslateMessage(pMsg);
}


