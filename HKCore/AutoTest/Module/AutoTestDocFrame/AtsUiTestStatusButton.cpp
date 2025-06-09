// AtsUiTestStatusButton.cpp : 实现文件
//

#include "stdafx.h"
#include "AtsUiTestStatusButton.h"
#include "../../Module/api/GloblaDrawFunctions.h"
#include "../TCtrlCntrDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const long g_nItemSpyWidth = 7;
const long g_nItemSpyHeight = 7;
const long g_nItemSpyGap = 1;

// CAtsUiTestStatusButton

IMPLEMENT_DYNAMIC(CAtsUiTestStatusButton, CButton)

CAtsUiTestStatusButton::CAtsUiTestStatusButton()
{
	m_pTestControl = NULL;
	m_nItemCount = 0;
	m_pCurrSelTestItem = NULL;

	m_nTopGap = 0;
	m_nTimerIDEvent = 1;

	m_bTipFlag = FALSE;
	m_clrTip = RGB(0,0,0);
	m_bRePaint = FALSE;

	m_pBitmap = NULL;
	m_pOldBitmap = NULL;
	m_pMemDC = NULL;
}

CAtsUiTestStatusButton::~CAtsUiTestStatusButton()
{
	if (m_pMemDC != NULL)
	{
		m_pMemDC->SelectObject(m_pOldBitmap);
		delete m_pMemDC;
		m_pMemDC = NULL;
		m_pBitmap->DeleteObject();
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	if (IsWindow(m_TitleTip.m_hWnd))
	{
		m_TitleTip.DestroyWindow();
	}

	m_oListMngr.RemoveAll();
}

BEGIN_MESSAGE_MAP(CAtsUiTestStatusButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CAtsUiTestStatusButton 消息处理程序

void CAtsUiTestStatusButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rectClient;
	static long snTestingItemStateFlag;
	CDC *pDC = GetDC();
	GetClientRect(rectClient);

	if(m_nItemCount == 0)
	{
		m_pMemDC->FillSolidRect(rectClient,RGB(255,255,255));
		pDC->BitBlt(0,0,rectClient.Width(),rectClient.Height(),m_pMemDC,0,0,SRCCOPY);
		ReleaseDC(pDC);		
		return;
	}

	long nItemWidth = g_nItemSpyWidth+g_nItemSpyGap+1;

	long nItemsPerRow = rectClient.Width() / nItemWidth;
	long nRows = m_nItemCount / nItemsPerRow;
	long nTop,nBottom,nLeft,nRight;

	if (nRows*nItemWidth < rectClient.Width())
	{
		nRows++;
	}

	nTop = 0;
	nBottom = nTop + g_nItemSpyHeight;
	m_nTopGap = nTop;

	nLeft = 1;
	long nRow = 0;
	long nIndex = 0;
	CGbItemBase* pItem = NULL;
	COLORREF color = RGB(0,0,0);
	long nItemIndex = 0;
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;

	for (nRow=0;nRow<nRows;nRow++)
	{
		for (nIndex=0;nIndex<nItemsPerRow;nIndex++)
		{
			if (nItemIndex >= m_nItemCount)
			{
				break;
			}
			nLeft = 1+nIndex*(g_nItemSpyWidth+1+1);
			nRight = nLeft + g_nItemSpyWidth;
			DrawRectBorder(m_pMemDC,nLeft,nTop,nRight,nBottom,RGB(0,0,0));
			pItem = (CGbItemBase*)m_oListMngr.GetAt(nItemIndex);
			color = TCC_GetItemStateColor(pItem);		//根据pItem的状态获取其对应的颜色值
		
			if (color == 0)
			{
				color = RGB(255,255,255);
			}

			m_pMemDC->FillSolidRect(CRect(nLeft+1,nTop+1,nRight,nBottom),color);		//此条语句作测试用
			nItemIndex++;
		}

		nTop += g_nItemSpyHeight;
		nTop += 2;
		nBottom = nTop + g_nItemSpyHeight;
	}

	pDC->BitBlt(0,0,rectClient.Width(),rectClient.Height(),m_pMemDC,0,0,SRCCOPY);
	ReleaseDC(pDC);
}

void CAtsUiTestStatusButton::CreateTitleTip()
{
	if (!IsWindow(m_TitleTip.m_hWnd))
	{
		m_TitleTip.Create(this);
		LOGFONT logFont = InitLogFont();
		logFont.lfHeight = -12;
#ifdef UNICODE
		lstrcpy(logFont.lfFaceName,_T("Tahoma"));
#else
		strcpy(logFont.lfFaceName,_T("Tahoma"));
#endif // UNICODE

		logFont.lfWeight = 400;
		m_TitleTip.SetLogFont(logFont);
	}
}

void CAtsUiTestStatusButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!::IsWindow(m_TitleTip.m_hWnd))
	{
		return ;
	}

	CRect   rect; 
	GetClientRect(&rect); 

	//鼠标离开控件区域
	if( ! rect.PtInRect(point))
	{
		m_TitleTip.Hide();
		ReleaseCapture(); 

		return;
	}

	SetCapture(); 
	//鼠标进入控件区域 
	m_pCurrSelTestItem = GetTestItemAtPoint(point);

	if(m_pCurrSelTestItem != NULL)
	{
		m_clrTip = TCC_GetItemStateColor(m_pCurrSelTestItem);
	}

	if (m_pCurrSelTestItem == NULL)
	{
		m_TitleTip.Hide();
		return;
	}

	CString strTip = m_pCurrSelTestItem->m_strName;
	rect = m_rectTitleTip;

	if(m_strOldSelected != strTip)
		m_TitleTip.Hide();
	m_TitleTip.Show(rect,strTip,g_nItemSpyWidth +2);

	m_strOldSelected = strTip;
	
	CButton::OnMouseMove(nFlags, point);
}

long CAtsUiTestStatusButton::GetTestItemIndexAtPoint(CPoint point)
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

	nRowIndex = (point.y - m_nTopGap) / nItemHeight;

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

CGbItemBase* CAtsUiTestStatusButton::GetTestItemAtPoint(CPoint point)
{
	long nItemIndex = GetTestItemIndexAtPoint(point);

	if (m_oListMngr.GetCount() == 0)
	{
		return NULL;
	}

	return (CGbItemBase*)m_oListMngr.GetAt(nItemIndex);
}

void CAtsUiTestStatusButton::_OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CGbItemBase* pItem = GetTestItemAtPoint(point);
	if(pItem != NULL)
	{
		ASSERT(m_pTestControl != NULL);
		m_pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);
	}
	m_bRePaint = FALSE;
}

void CAtsUiTestStatusButton::_OnMouseMove(UINT nFlags, CPoint point)
{
	//m_oCurrTestItem = GetTestItemAtPoint(point);
	//if (m_oCurrTestItem == NULL)
	//{
	//	return;
	//}

	//if(!::IsWindow(m_TitleTip.m_hWnd))
	//{
	//	return ;
	//}
}

void CAtsUiTestStatusButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	_OnLButtonDblClk(nFlags,point);
	
	//CButton::OnLButtonDblClk(nFlags, point);
}

void CAtsUiTestStatusButton::OnSize(UINT nType, int cx, int cy)
{
	CButton::OnSize(nType, cx, cy);
	
	_OnSize();
}

int CAtsUiTestStatusButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_bRePaint = TRUE;

	return 0;
}

void CAtsUiTestStatusButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CButton::OnLButtonDown(nFlags, point);
}

void CAtsUiTestStatusButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	//CButton::OnLButtonUp(nFlags, point);
}

void CAtsUiTestStatusButton::_OnSize()
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
		delete m_pMemDC;
		m_pMemDC = NULL;
		m_pBitmap->DeleteObject();
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	CDC *pDC = GetDC();

	m_pMemDC = new CDC;
	m_pBitmap = new CBitmap;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC,rectClient.Width(),rectClient.Height());
	m_pOldBitmap = m_pMemDC->SelectObject(m_pBitmap);
	m_pMemDC->FillSolidRect(rectClient,RGB(255,255,255));
	ReleaseDC(pDC);

	long nItemWidth = g_nItemSpyWidth+g_nItemSpyGap+1;
	long nItemCount = 0;
	if (m_pTestControl != NULL)
	{
		nItemCount = m_nItemCount;
	}

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

	if (pWnd != NULL)
	{
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
	}

	CFrameWnd *pFrameWnd = (CFrameWnd*)AfxGetMainWnd();

	if (pFrameWnd != NULL)
	{
		pFrameWnd->RecalcLayout(TRUE);	
	}
}

void CAtsUiTestStatusButton::SetTestControl(CTestControl* pTestControl)
{
	m_pTestControl = pTestControl;
	m_nItemCount = GetTestItemCount(pTestControl);
	Invalidate(FALSE);
}

//以下两个函数获取TestItem的个数，并将测试项目对象存放在临时链表m_oListMngr中
long CAtsUiTestStatusButton::GetTestItemCount(CTestControl* pTestControl)
{
	m_oListMngr.RemoveAll();
	long nItemCount = 0;

	m_pTestControl = pTestControl;

	if (m_pTestControl == NULL)
	{
		return 0;
	}

	POS pos = m_pTestControl->m_pGuideBook->GetHeadPosition();

	CExBaseObject* pObj = NULL;
	while(pos != NULL)
	{
		pObj = m_pTestControl->m_pGuideBook->GetNext(pos);
		if(Gb_IsItemBaseClassID(pObj->GetClassID()))
		{
			m_oListMngr.AddTail(pObj);
			nItemCount ++;
			nItemCount += GetChildrenItemCount((CGbItemBase*)pObj);
		}
	}

	return nItemCount;
}

long CAtsUiTestStatusButton::GetChildrenItemCount(CGbItemBase* pTestItem)
{
	long nChildrenCount = 0;
	POS pos = pTestItem->GetHeadPosition();
	
	CExBaseObject* pObj = NULL;
	while(pos != NULL)
	{
		pObj = pTestItem->GetNext(pos);

		if(Gb_IsItemBaseClassID(pObj->GetClassID()))
		{
			m_oListMngr.AddTail(pObj);
			nChildrenCount ++;
			nChildrenCount += GetChildrenItemCount((CGbItemBase*)pObj);
		}
	}

	return nChildrenCount;
}


void CAtsUiTestStatusButton::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}
