#include "StdAfx.h"
#include "XUIAutoAdjTool.h"

//////////////////////////////////////////////////////////////////////////
//CXUIAdjItemBase
CXUIAdjItemBase::CXUIAdjItemBase()
{
	m_rcItem.left = 0;
	m_rcItem.top = 0;
	m_rcItem.bottom = 0;
	m_rcItem.right = 0;
	m_fXMoveCoef = 0;
	m_fXZoomCoef = 0;
	m_fYMoveCoef = 0;
	m_fYZoomCoef = 0;
	m_nMinVisibleWidth = 0;
	m_nMinVisibleHeight = 0;
	m_bCanHideShow =  0;
}

CXUIAdjItemBase::~CXUIAdjItemBase()
{

}

BOOL CXUIAdjItemBase::XUI_Validate(const CRect &rcItem)
{
	return ( (rcItem.Width() > 0) && (rcItem.Height() > 0) );
}

void CXUIAdjItemBase::XUI_Merge(CRect &rcDest, CRect &rcSrc)
{
	if (XUI_Validate(rcDest) && XUI_Validate(rcSrc))
	{
		rcDest.left = min(rcDest.left, rcSrc.left);
		rcDest.top = min(rcDest.top, rcSrc.top);
		rcDest.bottom = max(rcDest.bottom, rcSrc.bottom);
		rcDest.right = max(rcDest.right, rcSrc.right);

		return;
	}

	if (XUI_Validate(rcSrc))
	{
		rcDest = rcSrc;
	}

}

void CXUIAdjItemBase::XUI_Adjust(long xChange, long yChange)
{
	m_rcItemCurrPos = m_rcItem;
	float nLeft	= m_rcItemCurrPos.left;
	float nTop	= m_rcItemCurrPos.top;
	float nWidth	= m_rcItemCurrPos.Width();
	float nHeight	= m_rcItemCurrPos.Height();

	//设置新的位置参数
	nLeft	+= (xChange*m_fXMoveCoef);
	nTop	+= (yChange*m_fYMoveCoef);
	nWidth	+= (xChange*m_fXZoomCoef);
	nHeight	+= (yChange*m_fYZoomCoef);

	m_rcItemCurrPos.left = nLeft;
	m_rcItemCurrPos.top = nTop;
	m_rcItemCurrPos.right = m_rcItemCurrPos.left + nWidth;
	m_rcItemCurrPos.bottom = m_rcItemCurrPos.top + nHeight;
}

void CXUIAdjItemBase::XUI_CalSize()
{
	CRect rcItem;
	rcItem.SetRectEmpty();
	XUI_CalSize(rcItem);

	if (XUI_Validate(rcItem))
	{
		m_rcItem = rcItem;
	}
}

void CXUIAdjItemBase::XUI_CalSize(CRect &rcItem)
{
	CRect rcChildren(0, 0, 0, 0);
	CRect rcOwn;
	XUI_CalOwnSize(rcOwn);
	XUI_CalChildrenSize(rcChildren);

	XUI_Merge(rcItem, rcOwn);
	XUI_Merge(rcItem, rcChildren);
}

void CXUIAdjItemBase::XUI_CalOwnSize(CRect &rcItem)
{
	rcItem = m_rcItem;
}

void CXUIAdjItemBase::XUI_CalChildrenSize(CRect &rcChildren)
{
	
}

//////////////////////////////////////////////////////////////////////////
//
CXUIAdjItem_Wnd::CXUIAdjItem_Wnd()
{
}

CXUIAdjItem_Wnd::CXUIAdjItem_Wnd(CWnd *pParent, CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	ASSERT (pParent != NULL && pWnd != NULL);
	pWnd->GetWindowRect(&m_rcItem);
	pParent->ScreenToClient(&m_rcItem);

	m_pWnd = pWnd;
	m_fXMoveCoef = fXMoveCoef;
	m_fXZoomCoef = fXZoomCoef;
	m_fYMoveCoef = fYMoveCoef;
	m_fYZoomCoef = fYZoomCoef;

	//也可以使用这种模式判断
// 	CRuntimeClass *pRunClass = m_pWnd->GetRuntimeClass();
	//if (m_pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))

	TCHAR strClassName[32];
	::GetClassName(m_pWnd->m_hWnd, strClassName, 32);

#ifdef _UNICODE
	if (wcscmp(strClassName, _T("ComboBox")) == 0)
#else
	if (strcmp(strClassName, _T("ComboBox")) == 0)
#endif
	{
		m_rcItem.bottom += 200;
	}
}


CXUIAdjItem_Wnd::~CXUIAdjItem_Wnd()
{

}

void CXUIAdjItem_Wnd::XUI_Adjust(long xChange, long yChange)
{
	CXUIAdjItemBase::XUI_Adjust(xChange, yChange);
	m_pWnd->MoveWindow(m_rcItemCurrPos);
}


//////////////////////////////////////////////////////////////////////////
//
CXUIAdjItem_Area::CXUIAdjItem_Area(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	m_pXUI_ParentWnd = pWnd;
	m_fXMoveCoef = fXMoveCoef;
	m_fXZoomCoef = fXZoomCoef;
	m_fYMoveCoef = fYMoveCoef;
	m_fYZoomCoef = fYZoomCoef;
}

CXUIAdjItem_Area::CXUIAdjItem_Area(CWnd *pWnd, CRect rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	m_rcItem = rcArea;
	m_pXUI_ParentWnd = pWnd;
	m_fXMoveCoef = fXMoveCoef;
	m_fXZoomCoef = fXZoomCoef;
	m_fYMoveCoef = fYMoveCoef;
	m_fYZoomCoef = fYZoomCoef;
}

CXUIAdjItem_Area::CXUIAdjItem_Area()
{
	m_pXUI_ParentWnd = NULL;
}

CXUIAdjItem_Area::~CXUIAdjItem_Area()
{

}

void CXUIAdjItem_Area::XUI_SetParentWnd(CWnd *pWnd)
{
	m_pXUI_ParentWnd = pWnd;
	m_fXZoomCoef = 1;
	m_fYZoomCoef = 1;

	if (m_pXUI_ParentWnd->IsKindOf(RUNTIME_CLASS(CScrollView)))
	{
		CScrollView *pScrollView = (CScrollView*)m_pXUI_ParentWnd;
		CSize sz = pScrollView->GetTotalSize();
		m_rcItem.right = sz.cx;
		m_rcItem.bottom = sz.cy;
	}
	else
	{
		m_pXUI_ParentWnd->GetClientRect(&m_rcItem);
	}
}

void CXUIAdjItem_Area::XUI_Adjust(long xChange, long yChange)
{
	if (m_pXUI_ParentWnd == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CXUIAdjItemBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXUIAdjItemBase *)GetNext(pos);
		p->XUI_Adjust(xChange, yChange);
	}

// 	CXUIAdjItemBase::XUI_Adjust(xChange, yChange);
}

void CXUIAdjItem_Area::XUI_CalChildrenSize(CRect &rcChildren)
{
	CRect rc(0,0,0,0);
	POS pos = GetHeadPosition();
	CXUIAdjItemBase *p = NULL;
	rcChildren.SetRectEmpty();

	while (pos != NULL)
	{
		p = (CXUIAdjItemBase *)GetNext(pos);
		rc.SetRectEmpty();
		p->XUI_CalSize(rc);
		XUI_Merge(rcChildren, rc);
	}
}

CXUIAdjItem_Wnd* CXUIAdjItem_Area::XUI_AddWnd(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	CXUIAdjItem_Wnd *pXUI_Wnd = new CXUIAdjItem_Wnd(m_pXUI_ParentWnd, pWnd, fXMoveCoef, fYMoveCoef, fXZoomCoef, fYZoomCoef);
	AddTail(pXUI_Wnd);

	return pXUI_Wnd;
}

CXUIAdjItem_Wnd* CXUIAdjItem_Area::XUI_AddWnd(UINT nID, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	CWnd *pWnd = m_pXUI_ParentWnd->GetDlgItem(nID);

	if (pWnd == NULL)
	{
		return NULL;
	}
	else
	{
		return XUI_AddWnd(pWnd, fXMoveCoef, fYMoveCoef, fXZoomCoef, fYZoomCoef);
	}
}

CXUIAdjItem_Area* CXUIAdjItem_Area::XUI_AddArea(float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	CXUIAdjItem_Area *pArea = new CXUIAdjItem_Area(m_pXUI_ParentWnd, fXMoveCoef, fYMoveCoef, fXZoomCoef, fYZoomCoef);
	AddTail(pArea);
	return pArea;
}

CXUIAdjItem_Area* CXUIAdjItem_Area::XUI_AddArea(const CRect &rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef)
{
	CXUIAdjItem_Area *pArea = new CXUIAdjItem_Area(m_pXUI_ParentWnd, rcArea, fXMoveCoef, fYMoveCoef, fXZoomCoef, fYZoomCoef);
	AddTail(pArea);
	return pArea;
}

void CXUIAdjItem_Area::XUI_OnSize(long cx, long cy)
{
	if (m_pXUI_ParentWnd == NULL)
	{
		return;
	}

	long xChange = cx - m_rcItem.Width();
	long yChange = cy - m_rcItem.Height();

	if (xChange == 0 && yChange == 0)
	{
		return;
	}

	XUI_Adjust(xChange, yChange);
}

void CXUIAdjItem_Area::XUI_OnSize()
{
	ASSERT (m_pXUI_ParentWnd != NULL);

	CRect rcClient;
	m_pXUI_ParentWnd->GetClientRect(&rcClient);
	XUI_OnSize(rcClient.Width(), rcClient.Height());
}

