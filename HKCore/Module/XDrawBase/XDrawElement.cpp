//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawElement.cpp  CXDrawElement


#include "stdafx.h"
#include "XDrawElement.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


static const CString g_strXDrawPenStyle[] = 
{_T("PS_SOLID"), _T("PS_DASH"), _T("PS_DOT"), _T("PS_DASHDOT"), _T("PS_DASHDOTDOT") };

CString XDraw_GetLineStype(UINT nStyle)
{
	if (0 <= nStyle && nStyle<=4)
	{
		return g_strXDrawPenStyle[nStyle];
	}

	return g_strXDrawPenStyle[0];
}

UINT XDraw_GetLineStyle(const CString &strStyle)
{
	UINT nStyle = 0;

	for (nStyle=0; nStyle<5; nStyle++)
	{
		if (strStyle == g_strXDrawPenStyle[nStyle])
		{
			return nStyle;
		}
	}

	return PS_SOLID;
}

BOOL XDraw_Is_XDrawElement(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	return XDraw_Is_XDrawElement(pObj->GetClassID());
}

BOOL XDraw_Is_XDrawElement(UINT nClassID)
{
	return ( (nClassID & XDRAW_BASECLASS) == XDRAW_BASECLASS);
}

COLORREF CXDrawElement:: m_crPickColor = RGB(0, 0, 255);
DWORD    CXDrawElement::m_nPickStyle   = PS_SOLID;
long     CXDrawElement::m_nPickWidth   = 2;
CXDrawElement* CXDrawElement::g_pActiveElement = NULL;

CPoint CXDrawElement::g_ptOrigin  = CPoint(0,0);
CPoint CXDrawElement::g_ptCurrent = CPoint(0,0);
BOOL CXDrawElement::g_bLButtonDown = FALSE;

CXDrawElement::CXDrawElement()
{
	//初始化属性
	m_dwItemData = 0;
	m_dwState = XDRAW_STATE_NORMAL;
	m_ptTopLeft.x = 0;
	m_ptTopLeft.y = 0;
	m_nWidth = 0;
	m_nHeight = 0;
#ifdef _XDRAW_USE_EXTERN_ATTR_
	m_nEnable = 1;
	m_nShow = 1;
	m_nShow = 1;
	m_nEnable = 1;
#endif
	m_crBkColor = RGB(255, 255, 255);
	m_crForeColor = RGB(0, 0, 0);

	//初始化成员变量
	m_pXDrawDataRef = NULL;
	m_pParentWnd = NULL;
}

CXDrawElement::~CXDrawElement()
{
}
// 
// long CXDrawElement::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CXDrawElement::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CXDrawElement::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	return 0;
// }
// 
// BOOL CXDrawElement::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	CXDrawElement *p = (CXDrawElement*)pObj;
// 
// 	return TRUE;
// }
// 
BOOL CXDrawElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);
	CXDrawElement *p = (CXDrawElement*)pDest;

	p->m_dwItemData = m_dwItemData;
	p->m_dwState = m_dwState;
	p->m_ptTopLeft = m_ptTopLeft;
	p->m_nWidth = m_nWidth;
	p->m_nHeight = m_nHeight;
#ifdef _XDRAW_USE_EXTERN_ATTR_
	p->m_nEnable = m_nEnable;
	p->m_nShow = m_nShow;
#endif
	p->m_crBkColor = m_crBkColor;
	p->m_crForeColor = m_crForeColor;

	//初始化成员变量
	p->m_pXDrawDataRef = m_pXDrawDataRef;

	return TRUE;
}

CBaseObject* CXDrawElement::Clone()
{
	ASSERT (FALSE);
	return NULL;
}

CPoint CXDrawElement::GetTopCenter()
{
	return CPoint(m_ptTopLeft.x + m_nWidth / 2, m_ptTopLeft.y);
}

CPoint CXDrawElement::GetLeftCenter()
{
	return CPoint(m_ptTopLeft.x, m_ptTopLeft.y + m_nHeight / 2);
}

CPoint CXDrawElement::GetBottomCenter()
{
	return CPoint(m_ptTopLeft.x + m_nWidth / 2, m_ptTopLeft.y + m_nHeight);
}

CPoint CXDrawElement::GetRightCenter()
{
	return CPoint(m_ptTopLeft.x + m_nWidth, m_ptTopLeft.y + m_nHeight / 2);
}

CPoint CXDrawElement::CenterPoint()
{
	return CPoint(m_ptTopLeft.x + m_nWidth / 2, m_ptTopLeft.y + m_nHeight / 2);
}

long CXDrawElement::Right()
{
	return m_ptTopLeft.x + m_nWidth;
}

long CXDrawElement::Bottom()
{
	return m_ptTopLeft.y + m_nHeight;
}

void CXDrawElement::SetPickState(BOOL bPick)
{
	if (bPick)
	{
		m_dwState |= XDRAW_STATE_PICKED;
	}
	else
	{
		m_dwState &= (~XDRAW_STATE_PICKED);
	}
}

void CXDrawElement::Pick(const CPoint &point, CExBaseList &oList)
{
	if (IsPointInRect(point))
	{
		oList.AddTail(this);
	}
}

BOOL CXDrawElement::IsPointInRect(const CPoint &point)
{
	return ((m_ptTopLeft.x <= point.x && point.x <= m_nWidth + m_ptTopLeft.x) 
		&&  (m_ptTopLeft.y <= point.y && point.y <= m_nHeight + m_ptTopLeft.y));
}

CXDrawElement* CXDrawElement::QueryByXDrawDataRef(CExBaseObject *pDrawDataRef)
{
	if (m_pXDrawDataRef == pDrawDataRef)
	{
		return this;
	}

	return QueryChildrenByXDrawDataRef(pDrawDataRef);
}

CXDrawElement* CXDrawElement::QueryChildrenByXDrawDataRef(CExBaseObject *pDrawDataRef)
{
	return NULL;
}

void CXDrawElement::SetBorder(const CRect &rect) 
{ 
	m_ptTopLeft = rect.TopLeft();	
	m_nWidth = rect.Width();	
	m_nHeight = rect.Height(); 
}

CRect CXDrawElement::GetBorder()
{ 
	CRect rc;

	rc.left = m_ptTopLeft.x;
	rc.right = m_ptTopLeft.x + m_nWidth;
	rc.top = m_ptTopLeft.y;
	rc.bottom = m_ptTopLeft.y + m_nHeight;

	return rc;
}


void CXDrawElement::ExpandBorder(long &l, long &t, long &r, long &b)
{
	m_ptTopLeft.x -= l;
	m_ptTopLeft.y -= t;
	m_nWidth += r+l;
	m_nHeight += b+t;

	long nTemp = 0;

	if (m_nWidth < 0)
	{
		m_nWidth = 0;
	}

	if (m_nHeight < 0)
	{
		m_nHeight = 0;
	}
}

void CXDrawElement::Move(long nHor, long nVer)	
{ 
	m_ptTopLeft.Offset(nHor, nVer);
} 

void CXDrawElement::Zoom(double dRate)
{

}

////////////////////////////////////////////////////////////////////////
void CXDrawElement::UI_OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXDrawElement::UI_OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CXDrawElement::UI_OnSize(UINT nType, int cx, int cy)
{

}

void CXDrawElement::UI_OnLButtonUp(UINT nFlags, CPoint point)
{

}

BOOL CXDrawElement::UI_OnLButtonDown(UINT nFlags, CPoint point)
{
	SetPickState(TRUE);
	return TRUE;
}

void CXDrawElement::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	
}

void CXDrawElement::UI_OnTimer(UINT nIDEvent)
{
	
}

UINT CXDrawElement::UI_OnGetDlgCode()
{
	return 0;
}

BOOL CXDrawElement::UI_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return FALSE;
}

BOOL CXDrawElement::UI_OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return FALSE;
}

void CXDrawElement::UI_OnLButtonDblClk(UINT nFlags, CPoint point)
{

}

void CXDrawElement::UI_OnRButtonDblClk(UINT nFlags, CPoint point)
{

}

BOOL CXDrawElement::UI_OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

BOOL CXDrawElement::UI_OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return FALSE;
}

void CXDrawElement::UI_OnSysColorChange()
{

}

void CXDrawElement::UI_OnCaptureChanged(CWnd *pWnd)
{

}

void CXDrawElement::UI_OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{

}

void CXDrawElement::UI_OnRButtonUp(UINT nFlags, CPoint point)
{

}

void CXDrawElement::UI_OnKillFocus(CWnd* pNewWnd)
{

}


#if _MFC_VER >= 0x0421
void CXDrawElement::UI_OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{

}

BOOL CXDrawElement::UI_OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return FALSE;
}
#endif

LRESULT CXDrawElement::UI_OnSetFont(WPARAM hFont, LPARAM lParam)
{
	return 0;
}

LRESULT CXDrawElement::UI_OnGetFont(WPARAM hFont, LPARAM lParam)
{
	return 0;
}

void CXDrawElement::UI_OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXDrawElement::UI_OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CXDrawElement::UI_OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult)
{

}

LRESULT CXDrawElement::UI_OnFillComboBox(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawElement::UI_OnFillList(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawElement::UI_OnFillTree(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

LRESULT CXDrawElement::UI_OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox)
{
	return 0;
}

void CXDrawElement::UI_OnRButtonDown(UINT nFlags, CPoint point)
{

}

void CXDrawElement::UI_KillFocus()
{
	SetPickState(FALSE);
}


DWORD CXDrawElement::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	m_pXDrawDataRef = pData;

	if (pData->IsBaseList())
	{
		XCreateElementChildren((CExBaseList*)pData, pParentWnd);
	}

	InitAfterCreateElement(pParentWnd);

	return XCREATE_SUCC;
}

CXDrawElement* CXDrawElement::XCreateChildElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	if (pData == NULL)
	{
		return NULL;
	}

	return XCreateChildElement(pData->GetClassID());
}

CXDrawElement* CXDrawElement::XCreateChildElement(UINT nClassID)
{
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
CSize CXDrawElement::Layout(CPoint &ptTopLeft)
{
	m_ptTopLeft = ptTopLeft;
	return CSize(m_nWidth, m_nHeight);
}

CSize CXDrawElement::CalLayout(CSize &szDraw)
{
	CalLayoutOwn(szDraw);
	CalLayoutChildren(szDraw);
	return szDraw;
}

CSize CXDrawElement::CalLayoutOwn(CSize &szDraw)
{
	return szDraw;
}

CSize CXDrawElement::CalLayoutChildren(CSize &szDraw)
{
	return szDraw;
}

void CXDrawElement::GetSize(CSize &sz, DWORD dwMode)
{
	sz.cx = m_nWidth;
	sz.cy = m_nHeight;
}

