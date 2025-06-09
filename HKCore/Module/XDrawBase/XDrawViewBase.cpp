//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawViewBase.cpp  CXDrawViewBase


#include "stdafx.h"
#include "XDrawViewBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXDrawViewBase
CXDrawViewBase::CXDrawViewBase()
{
	//初始化属性

	//初始化成员变量
	m_pActiveElement = NULL;
}

CXDrawViewBase::~CXDrawViewBase()
{
}

void CXDrawViewBase::AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow)
{

}

BOOL CXDrawViewBase::CreateDrawMemDC(CDC *pDC, const CRect &rcClient)
{
	BOOL b = m_oDrawMemDC.Create(pDC, rcClient);
	m_oDrawMemDC->GetDC();

	if (b)
	{
		m_oDrawMemDC.FillSolidRect(m_crBkColor);
	}

	return b;
}

void CXDrawViewBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset);
}


void CXDrawViewBase::DrawActiveElement(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	if (m_pActiveElement == NULL)
	{
		return;
	}

	m_pActiveElement->Draw(pDC, fZoomRatio, ptOffset);
}

DWORD CXDrawViewBase::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	return 0;
}

////////////////////////////////////////////////////////////////////////
CXDrawElement* CXDrawViewBase::UI_GetActiveXDrawElement(const CPoint &point)
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

BOOL CXDrawViewBase::UI_SetActiveElement(CXDrawElement *pElement)
{
	BOOL bChanged = FALSE;

	if (pElement != m_pActiveElement)
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_KillFocus();
			bChanged = TRUE;
		}

		m_pActiveElement = pElement;

		if (m_pActiveElement != NULL)
		{
 			m_pActiveElement->SetPickState(TRUE);
			bChanged = TRUE;
		}
	}
	else
	{
// 		if (m_pActiveElement != NULL)
// 		{
// 			m_pActiveElement->UI_OnLButtonDown(nFlags, point);
// 		}
	}

	return bChanged;
}

void CXDrawViewBase::UI_OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXDrawViewBase::UI_OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXDrawViewBase::UI_OnSize(UINT nType, int cx, int cy)
{

}

void CXDrawViewBase::UI_OnLButtonUp(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);

	if (pActiveElement != m_pActiveElement)
	{
		// 		if (m_pActiveElement != NULL)
		// 		{
		// 			m_pActiveElement->UI_KillFocus()
		// 		}
		// 
		// 		m_pActiveElement = pActiveElement;
		//
		// 		if (m_pActiveElement != NULL)
		// 		{
		// 			m_pActiveElement->UI_OnLButtonUp(nFlags, point);
		// 		}
	}
	else
	{
		if (m_pActiveElement != NULL)
		{
			m_pActiveElement->UI_OnLButtonUp(nFlags, point);
		}
	}
}

BOOL CXDrawViewBase::UI_OnLButtonDown(UINT nFlags, CPoint point)
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

void CXDrawViewBase::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	CXDrawElement *pActiveElement = UI_GetActiveXDrawElement(point);

	if (pActiveElement != NULL)
	{
		pActiveElement->UI_OnMouseMove(nFlags, point);
	}
}

void CXDrawViewBase::UI_OnTimer(UINT nIDEvent)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnTimer(nIDEvent);
	}
}

UINT CXDrawViewBase::UI_OnGetDlgCode()
{
	return 0;
}

BOOL CXDrawViewBase::UI_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnKeyDown(nChar, nRepCnt, nFlags);
	}

	return FALSE;
}

BOOL CXDrawViewBase::UI_OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnChar(nChar, nRepCnt, nFlags);
	}

	return FALSE;
}

void CXDrawViewBase::UI_OnLButtonDblClk(UINT nFlags, CPoint point)
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

void CXDrawViewBase::UI_OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnRButtonDblClk(nFlags, point);
	}
}

BOOL CXDrawViewBase::UI_OnEraseBkgnd(CDC* pDC)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnEraseBkgnd(pDC);
	}

	return FALSE;
}

BOOL CXDrawViewBase::UI_OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return FALSE;
}

void CXDrawViewBase::UI_OnSysColorChange()
{

}

void CXDrawViewBase::UI_OnCaptureChanged(CWnd *pWnd)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnCaptureChanged(pWnd);
	}
}

void CXDrawViewBase::UI_OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{

}

void CXDrawViewBase::UI_OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnRButtonUp(nFlags, point);
	}
}

void CXDrawViewBase::UI_OnKillFocus(CWnd* pNewWnd)
{
	if (m_pActiveElement != NULL)
	{
		m_pActiveElement->UI_OnKillFocus(pNewWnd);
	}
}


#if _MFC_VER >= 0x0421
void CXDrawViewBase::UI_OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{

}

BOOL CXDrawViewBase::UI_OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return FALSE;
}
#endif

LRESULT CXDrawViewBase::UI_OnSetFont(WPARAM hFont, LPARAM lParam)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnSetFont(hFont, lParam);
	}

	return 0;
}

LRESULT CXDrawViewBase::UI_OnGetFont(WPARAM hFont, LPARAM lParam)
{
	if (m_pActiveElement != NULL)
	{
		return m_pActiveElement->UI_OnGetFont(hFont, lParam);
	}

	return 0;
}

void CXDrawViewBase::UI_OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXDrawViewBase::UI_OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXDrawViewBase::UI_OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

LRESULT CXDrawViewBase::UI_OnFillComboBox(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawViewBase::UI_OnFillList(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawViewBase::UI_OnFillTree(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawViewBase::UI_OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

void CXDrawViewBase::UI_OnRButtonDown(UINT nFlags, CPoint point)
{

}
