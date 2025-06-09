//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewBase.cpp  CXScdDrawViewBase


#include "stdafx.h"
#include "XScdDrawViewBase.h"

//////////////////////////////////////////////////////////////////////////
//CXScdIedGroup
CXScdIedGroup::CXScdIedGroup()
{

}

CXScdIedGroup::~CXScdIedGroup()
{
	RemoveAll();
}

CSize CXScdIedGroup::Layout(CPoint &ptTopLeft)
{
	m_ptTopLeft = ptTopLeft;
	POS pos = GetHeadPosition();
	CXScdDrawViewBase *pXDrawElement = NULL;
	CPoint pt;
	pt = ptTopLeft;
	CSize szElement;
	m_nWidth = 0;
	m_nHeight = 0;

	//CExBaseListXGridCtrlBase *pIedNameTemp=NULL;
	/*	pIedNameTemp->Create()*/
	//HDC hdc=GetDC(HWND);
	//CPaintDC dc(this);

	while (pos != NULL)
	{
		pXDrawElement = (CXScdDrawViewBase *)GetNext(pos);
		//TextOut()

		szElement = pXDrawElement->Layout(pt);

		pt.y += szElement.cy;
		m_nHeight += szElement.cy;
		//pt.y += XSCDDRAW_VIEW_GAP;
		pt.y =pt.y+ XSCDDRAW_VIEW_GAP+20;
		m_nWidth = max(m_nWidth, szElement.cx);
	}	

	return CSize(m_nWidth, m_nHeight);
}


//////////////////////////////////////////////////////////////////////////
//CXScdIedGroupThumb
CXScdIedGroupThumb::CXScdIedGroupThumb()
{

}

CXScdIedGroupThumb::~CXScdIedGroupThumb()
{

}

CSize CXScdIedGroupThumb::Layout(CPoint &ptTopLeft)
{
	m_ptTopLeft = ptTopLeft;
	POS pos = GetHeadPosition();
	CXDrawElement *pXDrawElement = NULL;
	CPoint pt;
	pt = ptTopLeft;
	CSize szElement;
	m_nWidth = 0;
	m_nHeight = 0;

	while (pos != NULL)
	{
		pXDrawElement = (CXDrawElement *)GetNext(pos);
		szElement = pXDrawElement->Layout(pt);
		m_nHeight = max(m_nHeight, szElement.cy);

		pt.x += szElement.cx+XSCDDRAW_THUMBNAIL_GAP_IED_X;
		m_nWidth +=szElement.cx+XSCDDRAW_THUMBNAIL_GAP_IED_X;		
	}	

	return CSize(m_nWidth, m_nHeight);
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawViewBase
CXScdDrawViewBase::CXScdDrawViewBase()
{
	//初始化属性

	//初始化成员变量
	m_pActiveElement = NULL;
	m_pSclIed = NULL;
}

CXScdDrawViewBase::~CXScdDrawViewBase()
{
}
void CXScdDrawViewBase::AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow)
{
	CXScdDrawIedBase *pIedBase = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pIedBase = (CXScdDrawIedBase *)GetNext(pos);
		pIedBase->AttachViewWindow(pViewWindow);
	}
}
void CXScdDrawViewBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset);
	m_oScdDrawLines.Draw(pDC, fZoomRatio, ptOffset);
}


void CXScdDrawViewBase::DrawActiveElement(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	if (m_pActiveElement == NULL)
	{
		return;
	}

	m_pActiveElement->Draw(pDC, fZoomRatio, ptOffset);
}

void CXScdDrawViewBase::LayoutLines()
{
	
}


void CXScdDrawViewBase::InitLinesBeginElement()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLineBase *pLine = NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLineBase *)m_oScdDrawLines.GetNext(pos);
		pLine->m_pBeginElement = QueryByXDrawDataRef(pLine->m_pBeginObj);
	}
}

void CXScdDrawViewBase::OnOnlyShowUsedChsChanged()
{

}

void CXScdDrawViewBase::RemoveErrorLines()
{

}

////////////////////////////////////////////////////////////////////////
CXDrawElement* CXScdDrawViewBase::UI_GetActiveXDrawElement(const CPoint &point)
{
	CExBaseList oList;
	Pick(point, oList);

	CXDrawElement *pActiveElement = NULL;

	if (oList.GetCount() > 0)
	{
		pActiveElement = (CXDrawElement *)oList.GetHead();
	}

	oList.RemoveAll();

	return pActiveElement;
}

void CXScdDrawViewBase::UI_OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXScdDrawViewBase::UI_OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXScdDrawViewBase::UI_OnSize(UINT nType, int cx, int cy)
{

}

void CXScdDrawViewBase::UI_OnLButtonUp(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);

	if (pActiveElement != m_pActiveElement)
	{
	
	}
	else
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonUp(nFlags, point);
		}
	}
}

BOOL CXScdDrawViewBase::UI_OnLButtonDown(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);
	BOOL bChanged = FALSE;

	if (pActiveElement != m_pActiveElement)
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_KillFocus();
			bChanged = TRUE;
		}

		m_pActiveElement = pActiveElement;

		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonDown(nFlags, point);
			bChanged = TRUE;
		}
	}
	else
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonDown(nFlags, point);
		}
	}

	return bChanged;
}

void CXScdDrawViewBase::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);

	if (pActiveElement != NULL)
	{
		pActiveElement->UI_OnMouseMove(nFlags, point);
	}
}

void CXScdDrawViewBase::UI_OnTimer(UINT nIDEvent)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnTimer(nIDEvent);
	}
}

UINT CXScdDrawViewBase::UI_OnGetDlgCode()
{
	return 0;
}

BOOL CXScdDrawViewBase::UI_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnKeyDown(nChar, nRepCnt, nFlags);
	}

	return FALSE;
}

BOOL CXScdDrawViewBase::UI_OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnChar(nChar, nRepCnt, nFlags);
	}

	return FALSE;
}

void CXScdDrawViewBase::UI_OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);

	if (pActiveElement != m_pActiveElement)
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_KillFocus();
		}

		m_pActiveElement = pActiveElement;

		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonDblClk(nFlags, point);
		}
	}
	else
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonDblClk(nFlags, point);
		}
	}
}

void CXScdDrawViewBase::UI_OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnRButtonDblClk(nFlags, point);
	}
}

BOOL CXScdDrawViewBase::UI_OnEraseBkgnd(CDC* pDC)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnEraseBkgnd(pDC);
	}

	return FALSE;
}

BOOL CXScdDrawViewBase::UI_OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return FALSE;
}

void CXScdDrawViewBase::UI_OnSysColorChange()
{

}

void CXScdDrawViewBase::UI_OnCaptureChanged(CWnd *pWnd)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnCaptureChanged(pWnd);
	}
}

void CXScdDrawViewBase::UI_OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{

}

void CXScdDrawViewBase::UI_OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnRButtonUp(nFlags, point);
	}
}

void CXScdDrawViewBase::UI_OnKillFocus(CWnd* pNewWnd)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnKillFocus(pNewWnd);
	}
}


#if _MFC_VER >= 0x0421
void CXScdDrawViewBase::UI_OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{

}

BOOL CXScdDrawViewBase::UI_OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return FALSE;
}
#endif

LRESULT CXScdDrawViewBase::UI_OnSetFont(WPARAM hFont, LPARAM lParam)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnSetFont(hFont, lParam);
	}

	return 0;
}

LRESULT CXScdDrawViewBase::UI_OnGetFont(WPARAM hFont, LPARAM lParam)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnGetFont(hFont, lParam);
	}

	return 0;
}

void CXScdDrawViewBase::UI_OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXScdDrawViewBase::UI_OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXScdDrawViewBase::UI_OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

LRESULT CXScdDrawViewBase::UI_OnFillComboBox(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXScdDrawViewBase::UI_OnFillList(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXScdDrawViewBase::UI_OnFillTree(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXScdDrawViewBase::UI_OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

void CXScdDrawViewBase::UI_OnRButtonDown(UINT nFlags, CPoint point)
{

}
