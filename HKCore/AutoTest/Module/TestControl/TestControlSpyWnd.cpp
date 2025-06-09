// tttctrltestspywnd.cpp : implementation file
//

#include "stdafx.h"
#include "tttctrltestspywnd.h"
#include "TCtrlCntrBaseApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long g_nItemSpyWidth = 5;
const long g_nItemSpyHeight = 6;
const long g_nItemSpyGap = 1;
/////////////////////////////////////////////////////////////////////////////
// CTttCtrlTestSpyWnd

CTttCtrlTestSpyWnd::CTttCtrlTestSpyWnd()
{
	m_TestItemTestContainer.RemoveAll();
	m_nOldItemIndexShowTip = -1;
	m_pCurrItem = NULL;
	m_nTimerIDEvent = 1;

	m_pBitmap = NULL;
	m_pOldBitmap = NULL;
	m_pMemDC = NULL;
	
	m_nTopGap = 0;
}

CTttCtrlTestSpyWnd::~CTttCtrlTestSpyWnd()
{
	if (m_pMemDC != NULL)
	{
		//m_pMemDC->SelectObject(m_pOldBitmap);
		delete m_pMemDC;
		m_pBitmap->DeleteObject();
		delete m_pBitmap;
	}
	m_pMemDC = NULL;
	m_pBitmap = NULL;
	
	m_TestItemTestContainer.RemoveAll();
}


BEGIN_MESSAGE_MAP(CTttCtrlTestSpyWnd, CButton)
	//{{AFX_MSG_MAP(CTttCtrlTestSpyWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, OnDoubleclicked)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTttCtrlTestSpyWnd message handlers

void CTttCtrlTestSpyWnd::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CRect rectClient;
	static long snTestingItemStateFlag;

	GetClientRect(rectClient);
	
	CDC *pDC = GetDC();
		
	long nItemCount = m_TestItemTestContainer.GetCount();
	long nItemWidth = g_nItemSpyWidth+g_nItemSpyGap+1;
	long nItemsPerRow = rectClient.Width() / nItemWidth;
	long nRows = nItemCount / nItemsPerRow;
	long nTop,nBottom,nLeft,nRight;
	if (nRows*nItemWidth < rectClient.Width())
	{
		nRows++;
	}
	
	nTop = 0;
	if (nRows == 1)
	{
		nTop = (rectClient.Height() - g_nItemSpyHeight) / 2;
	}
	nBottom = nTop + g_nItemSpyHeight;
	m_nTopGap = nTop;
	
	nLeft = 1;
	long nRow = 0;
	long nIndex = 0;
	CTestItemBaseClass *pItem = NULL;
	COLORREF color;
	long nItemIndex = 0;
	CTCtrlCntrBaseApp *pApp = (CTCtrlCntrBaseApp*)AfxGetApp();
	long nCurrTestItemIndex = pApp->GetCurrTestItemIndex();
	BOOL bIsNowTesting = pApp->IsNowTesting();
	
	for (nRow=0;nRow<nRows;nRow++)
	{
		for (nIndex=0;nIndex<nItemsPerRow;nIndex++)
		{
			if (nItemIndex >= nItemCount)
			{
				break;
			}
			nLeft = 1+nIndex*(g_nItemSpyWidth+1+1);
			nRight = nLeft + g_nItemSpyWidth;
			DrawRectBorder(m_pMemDC,nLeft,nTop,nRight,nBottom,RGB(0,0,0));
			pItem = (CTestItemBaseClass*)m_TestItemTestContainer.GetAtIndex(nItemIndex);
			color = pItem->GetTestItemStateColor();
			if (color == 0)
			{
				color = RGB(255,255,255);
			}
			if (bIsNowTesting && nCurrTestItemIndex == nItemIndex)
			{
				if (snTestingItemStateFlag == 0)
				{
					snTestingItemStateFlag = 1;
					m_pMemDC->FillSolidRect(CRect(nLeft+1,nTop+1,nRight,nBottom),RGB(255,255,255));
				}
				else
				{
					snTestingItemStateFlag = 0;
					m_pMemDC->FillSolidRect(CRect(nLeft+1,nTop+1,nRight,nBottom),color);
				}
			}
			else
			{
				m_pMemDC->FillSolidRect(CRect(nLeft+1,nTop+1,nRight,nBottom),color);
			}
			nItemIndex++;
		}
		nTop += g_nItemSpyHeight;
		nTop += 2;
		nBottom = nTop + g_nItemSpyHeight;
	}
/*
	const long g_nItemSpyWidth = 6;
	const long g_nItemSpyHeight = 7;
	const long g_nItemSpyGap = 1;
*/
	
	pDC->BitBlt(0,0,rectClient.Width(),rectClient.Height(),m_pMemDC,0,0,SRCCOPY);
	
	
	ReleaseDC(pDC);
}

void CTttCtrlTestSpyWnd::AddTestItemToContainer(CTestItemBaseClass *pItem)
{
	if (pItem->IsTestItemBaseClassObject())
	{
		m_TestItemTestContainer.AddTail(pItem);
		return;
	}
	CTestItemListClass *pList = (CTestItemListClass*)pItem;
	CTestItemBaseClass *pChild = NULL;

	POSITION pos = pList->GetHeadPosition();
	while (pos != NULL)
	{
		pChild = pList->GetNext(pos);
		AddTestItemToContainer(pChild);
	}
}

void CTttCtrlTestSpyWnd::SetTestProject(CTestProject *pProject)
{
	m_TestItemTestContainer.RemoveAll();

	if (pProject == NULL)
	{
		return;
	}
	AddTestItemToContainer(pProject);

	_OnSize();
	
	Invalidate(FALSE);
}

void CTttCtrlTestSpyWnd::UpdateTestProjectSpy()
{
	Invalidate(FALSE);
}


void CTttCtrlTestSpyWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnLButtonDblClk(nFlags, point);
}

void CTttCtrlTestSpyWnd::OnMouseMove(UINT nFlags, CPoint point) 
{

}

void CTttCtrlTestSpyWnd::OnClicked() 
{
	long n = 0;
}

void CTttCtrlTestSpyWnd::OnDoubleclicked() 
{
	long n = 0;
	
}

void CTttCtrlTestSpyWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CButton::OnLButtonDown(nFlags, point);
}

void CTttCtrlTestSpyWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnLButtonUp(nFlags, point);
}

void CTttCtrlTestSpyWnd::_OnLButtonDblClk(UINT nFlags, CPoint point)
{
	KillTimer(m_nTimerIDEvent);	
	
	CTestItemBaseClass *pItem = GetTestItemAtPoint(point);
	if (pItem != NULL)
	{
		CTCtrlCntrBaseApp *pApp = (CTCtrlCntrBaseApp*)AfxGetApp();
		pApp->SetCurrSelTestItemEx(pItem);
	}
}

void CTttCtrlTestSpyWnd::_OnMouseMove(UINT nFlags, CPoint point)
{
	KillTimer(m_nTimerIDEvent);

	m_pCurrItem = GetTestItemAtPoint(point);
	if (m_pCurrItem == NULL)
	{
		return;
	}
	
	if (!::IsWindow(m_TitleTip.m_hWnd))
	{
		return;
	}
	
	SetTimer(m_nTimerIDEvent,500,NULL);
}

void CTttCtrlTestSpyWnd::_OnClicked()
{
	KillTimer(m_nTimerIDEvent);	
}

void CTttCtrlTestSpyWnd::_OnDoubleclicked()
{
	KillTimer(m_nTimerIDEvent);	
}

void CTttCtrlTestSpyWnd::_OnLButtonDown(UINT nFlags, CPoint point)
{
	KillTimer(m_nTimerIDEvent);	
}

void CTttCtrlTestSpyWnd::_OnLButtonUp(UINT nFlags, CPoint point)
{
	KillTimer(m_nTimerIDEvent);	
}

void CTttCtrlTestSpyWnd::_OnSize()
{
	if (!::IsWindow(m_hWnd))
	{
		return;
	}
	CRect rectClient;
	GetClientRect(&rectClient);
	
	if (rectClient.Width() <= 0 || rectClient.Height() <= 0)
	{
		return;
	}
	if (m_pMemDC != NULL)
	{
		//m_pMemDC->SelectObject(m_pOldBitmap);
		delete m_pMemDC;
		m_pBitmap->DeleteObject();
		delete m_pBitmap;
	}

	CDC *pDC = GetDC();

	m_pMemDC=new CDC;
	m_pBitmap=new CBitmap;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC,rectClient.Width(),rectClient.Height());
	m_pOldBitmap = m_pMemDC->SelectObject(m_pBitmap);
	m_pMemDC->FillSolidRect(rectClient,RGB(255,255,255));
	ReleaseDC(pDC);
	
	long nItemWidth = g_nItemSpyWidth+g_nItemSpyGap+1;
	long nItemCount = m_TestItemTestContainer.GetCount();
	long nItemsPerRow = rectClient.Width() / nItemWidth;
	if (nItemsPerRow == 0)
	{
		return;
	}
	long nRows = nItemCount / nItemsPerRow;
	if (nRows*nItemWidth < rectClient.Width())
	{
		nRows++;
	}
	
	if (nRows <= 2)
	{
		nRows = 2;
	}
	
	CWnd *pWnd = GetParent();
	CRect rectParent;
	pWnd->GetWindowRect(rectParent);
	long nHeightGap = rectParent.Height() - rectClient.Height();
	long nMinHeight = (g_nItemSpyHeight+1) * nRows + nHeightGap;
	nMinHeight += 4;
	if (nMinHeight < 14)
	{
		nMinHeight = 14;
	}

	pWnd->SendMessage(SB_SETMINHEIGHT,nMinHeight,nMinHeight);
	
	CFrameWnd *pFrameWnd = (CFrameWnd*)AfxGetMainWnd();
	pFrameWnd->RecalcLayout(TRUE);	
}

long CTttCtrlTestSpyWnd::GetTestItemIndexAtPoint(CPoint point)
{
	CRect rectClient;
	GetClientRect(&rectClient);
	if (!rectClient.PtInRect(point))
	{
		return -1;
	}

	long nWidth = rectClient.Width();
	long nHeight = rectClient.Height();
	long nRowIndex = 0;
	long nColIndex = 0;
	long nItemWidth = g_nItemSpyWidth+g_nItemSpyGap+1;
	long nItemHeight = g_nItemSpyHeight+2;
	long nItemsPerRow = nWidth / nItemWidth;
	nColIndex = point.x / nItemWidth;
/*
	if (point.x - nColIndex*nItemWidth > 0)
	{
		nColIndex++;
	}
*/
	nRowIndex = (point.y - m_nTopGap) / nItemHeight;
/*
	if (point.y - nRowIndex * nItemHeight > 0)
	{
		nRowIndex++;
	}
	nRowIndex--;
*/

	m_rectTitleTip.left = 1 + nColIndex*(g_nItemSpyWidth+1+1);
	m_rectTitleTip.right = m_rectTitleTip.left + g_nItemSpyWidth;
	m_rectTitleTip.top = nRowIndex*(g_nItemSpyHeight+2) + m_nTopGap;
	m_rectTitleTip.bottom = m_rectTitleTip.top + g_nItemSpyHeight;
	m_rectTitleTip.InflateRect(1,1,1,1);
	if (!m_rectTitleTip.PtInRect(point))
	{
		return -1;
	}
	
	long nItemIndex = nItemsPerRow * nRowIndex + nColIndex;
	return nItemIndex;
}

CTestItemBaseClass* CTttCtrlTestSpyWnd::GetTestItemAtPoint(CPoint point)
{
	long nItemIndex = GetTestItemIndexAtPoint(point);
	CTestItemBaseClass *pItem = NULL;
	pItem = m_TestItemTestContainer.GetAtIndex(nItemIndex);
	return pItem;
}

void CTttCtrlTestSpyWnd::CreateTitleTip()
{
	if (!IsWindow(m_TitleTip.m_hWnd))
	{
		m_TitleTip.Create(this);
		LOGFONT logFont = InitLogFont();
		logFont.lfHeight = -12;
		strcpy(logFont.lfFaceName,"Tahoma");
		logFont.lfWeight = 400;
		m_TitleTip.SetLogFont(logFont);
	}
}

void CTttCtrlTestSpyWnd::GetTestItemTipString(CString &strTip,CTestItemBaseClass *pItem)
{
	CTestItemRelay *pTestItemRelay = NULL;
	
	long nClassID = pItem->GetClassID();
	switch(nClassID)
	{
	case CLASSID_METERS:
	case CLASSID_STUFFS:
	case CLASSID_STANDBYS:
	case CLASSID_SETS:
	case CLASSID_SYSTEMPARAS:
	case CLASSID_DEVICEPARAS:
	case CLASSID_CONNECT:
		strTip = pItem->m_strName;
		break;
	case CLASSID_SAFETY:
		strTip = pItem->m_strName;
		break;
	case CLASSID_PROTCMD:
		strTip = pItem->m_strName;
		break;
	case CLASSID_HDCHKITEM:
		strTip = pItem->m_strName;
		break;
	case CLASSID_POINT:
		pTestItemRelay = GetTestItemRelay(pItem);
		strTip.Format("%s:%s",pTestItemRelay->m_strName,pItem->m_strName);
		break;
	default:
		strTip = pItem->m_strName;
		break;
	}
}


void CTttCtrlTestSpyWnd::OnTimer(UINT nIDEvent) 
{
	KillTimer(m_nTimerIDEvent);
	CString strTip;
	GetTestItemTipString(strTip,m_pCurrItem);
	CRect rect = m_rectTitleTip;

	m_TitleTip.Show(rect, strTip, 0);

	CButton::OnTimer(nIDEvent);
}
