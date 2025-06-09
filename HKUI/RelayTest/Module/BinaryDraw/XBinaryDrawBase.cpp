//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XBinaryDrawBase.cpp  CXBinaryDrawBase


#include "stdafx.h"
#include "XBinaryDrawBase.h"
#include "../../../Module/API/GloblaDrawFunctions.h"

long g_nXBinaryDrawSize = X_BINARY_DRAW_SIZE_LARGE; 
long g_nBinaryDrawMode = BIANRY_DRAW_MODE_CARD_NXID; 
LOGFONT g_fontXBinaryDraw = InitLogFont();
// long g_nBinaryDrawMode = BIANRY_DRAW_MODE_CARD_ALLID; 
COLORREF  g_crCardIndexDraw = RGB(0, 0, 255);

// #define BINARY_CLOSE_COLOR   RGB(255, 0, 0)
// #define BINARY_OPEN_COLOR    RGB(0, 255, 0)


//////////////////////////////////////////////////////////////////////////
//CXBinarysDrawBase
CXBinaryDrawBase::CXBinaryDrawBase()
{
	//初始化属性
	m_nBinaryIndex = 0;   //开关量编号

	//初始化成员变量
}

CXBinaryDrawBase::~CXBinaryDrawBase()
{
}

long CXBinaryDrawBase::GetBinaryBitVal()
{
	return 0;
}

void CXBinaryDrawBase::AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow)
{
	POS pos = GetHeadPosition();
// 	CXDrawCtrlBase *pCtrlBase = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pCtrlBase = (CXDrawCtrlBase *)GetNext(pos);
// 		pCtrlBase->AttachViewWindow(pViewWindow);
// 	}
}

void vm_draw_get_binary_name(CString &strName, long nBinaryIndex)
{
	if (g_nBinaryDrawMode == BIANRY_DRAW_MODE_CARD_NXID)
	{
		strName.Format(_T("%d"), nBinaryIndex % 32+1);
	}
	else
	{
		strName.Format(_T("%d"), nBinaryIndex+1);
	}
}

void vm_draw_get_card_font(LOGFONT &font)
{
	font.lfHeight = g_fontXBinaryDraw.lfHeight * 3 / 4;
}

void vm_draw_get_binary_rect(const CPoint &ptTopLeft, CRect &rc)
{
	if (X_BINARY_DRAW_SIZE_LARGE == g_nXBinaryDrawSize)
	{
		rc.left = ptTopLeft.x + XBINARY_DRAW_GAP_HOR;
		rc.top =  ptTopLeft.y + XBINARY_DRAW_GAP_HOR;
		rc.right = rc.left + XBINARY_DRAW_WIDTH;
		rc.bottom = rc.top + XBINARY_DRAW_HEIGHT;
	}
	else
	{
		rc.left = ptTopLeft.x + XBINARY_DRAW_GAP_HOR_S;
		rc.top =  ptTopLeft.y + XBINARY_DRAW_GAP_HOR_S;
		rc.right = rc.left + XBINARY_DRAW_WIDTH_S;
		rc.bottom = rc.top + XBINARY_DRAW_HEIGHT_S;
	}
}

void vm_draw_init_binary_font()
{
	if (X_BINARY_DRAW_SIZE_LARGE == g_nXBinaryDrawSize)
	{
		g_fontXBinaryDraw.lfHeight = -XBINARY_DRAW_HEIGHT_FONT;
	}
	else
	{
		g_fontXBinaryDraw.lfHeight = -XBINARY_DRAW_HEIGHT_FONT_S;
	}
}


void CXBinaryDrawBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rc_IedName;
	vm_draw_get_binary_rect(m_ptTopLeft, rc_IedName);
// 	rc_IedName.left = m_ptTopLeft.x + XBINARY_DRAW_GAP_HOR;
// 	rc_IedName.top =  m_ptTopLeft.y + XBINARY_DRAW_GAP_HOR;
// 	rc_IedName.right = rc_IedName.left + XBINARY_DRAW_WIDTH;
// 	rc_IedName.bottom = rc_IedName.top + XBINARY_DRAW_HEIGHT;
	
	CPen pen;
	
	if (IsPicked())
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}

	CPen *pOldPen = pDC->SelectObject(&pen);
	CBrush brush;

#ifdef BINARY_IN_USE_CLOSE_IS_0
	if (GetBinaryBitVal() == 0)
#else
	if (GetBinaryBitVal() != 0)
#endif
	{
		brush.CreateSolidBrush(BINARY_CLOSE_COLOR);
	}
	else
	{
		brush.CreateSolidBrush(BINARY_OPEN_COLOR);
	}

	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rc_IedName);
	CString strName;
	vm_draw_get_binary_name(strName, m_nBinaryIndex);

	CRect rc_IedName_Text = rc_IedName;
	rc_IedName_Text.DeflateRect(1, 1, 1, 1);
	CmDrawTextRect(pDC, strName, m_crForeColor, rc_IedName_Text, m_crBkColor, g_fontXBinaryDraw, TRANSPARENT,DT_VCENTER|DT_CENTER,0);

/*
	strName.Format(_T("%d"), m_nBinaryIndex / 32 + 1);
	rc_IedName_Text.right = rc_IedName_Text.left + rc_IedName_Text.Width() / 2;
	LOGFONT font = g_fontXBinaryDraw;
	vm_draw_get_card_font(font);
	CmDrawTextRect(pDC, strName, g_crCardIndexDraw, rc_IedName_Text, m_crBkColor, font, TRANSPARENT,DT_LEFT|DT_TOP,0);
*/

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


CSize CXBinaryDrawBase::CalLayout(CSize &szDraw)
{
	m_nWidth = vm_binary_get_width();
	m_nHeight = vm_binary_get_height();

	szDraw.cx += m_nWidth;
	szDraw.cy = m_nHeight;

	return szDraw;
}

CSize CXBinaryDrawBase::Layout(CPoint &ptTopLeft)
{
	CPoint pt = ptTopLeft;
	m_ptTopLeft = ptTopLeft;

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

//////////////////////////////////////////////////////////////////////////
//CXBinaryOutDraw
CXBinaryOutDraw::CXBinaryOutDraw()
{

}

CXBinaryOutDraw::~CXBinaryOutDraw()
{

}


void CXBinaryOutDraw::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rc_IedName;
	vm_draw_get_binary_rect(m_ptTopLeft, rc_IedName);
// 	rc_IedName.left = m_ptTopLeft.x + XBINARY_DRAW_GAP_HOR;
// 	rc_IedName.top =  m_ptTopLeft.y + XBINARY_DRAW_GAP_HOR;
// 	rc_IedName.right = rc_IedName.left + XBINARY_DRAW_WIDTH;
// 	rc_IedName.bottom = rc_IedName.top + XBINARY_DRAW_HEIGHT;

	CPen pen;

	if (IsPicked())
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}

	CPen *pOldPen = pDC->SelectObject(&pen);
	CBrush brush;

	if (GetBinaryBitVal())
	{
		brush.CreateSolidBrush(BINARY_CLOSE_COLOR);
	}
	else
	{
		brush.CreateSolidBrush(BINARY_OPEN_COLOR);
	}

	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rc_IedName);
	CString strName;
	vm_draw_get_binary_name(strName, m_nBinaryIndex);

	CRect rc_IedName_Text = rc_IedName;
	rc_IedName_Text.DeflateRect(1, 1, 1, 1);
	CmDrawTextRect(pDC, strName, m_crForeColor, rc_IedName_Text, m_crBkColor, g_fontXBinaryDraw, TRANSPARENT,DT_VCENTER|DT_CENTER,0);

	strName.Format(_T("%d"), m_nBinaryIndex / 32 + 1);
	rc_IedName_Text.right = rc_IedName_Text.left + rc_IedName_Text.Width() / 2;
	LOGFONT font = g_fontXBinaryDraw;
	vm_draw_get_card_font(font);
	CmDrawTextRect(pDC, strName, g_crCardIndexDraw, rc_IedName_Text, m_crBkColor, font, TRANSPARENT,DT_LEFT|DT_TOP,0);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

BOOL CXBinaryOutDraw::UI_OnLButtonDown(UINT nFlags, CPoint point)
{
// 	if (m_pParentWnd == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (!IsPointInRect(point))
// 	{
// 		return FALSE;
// 	}
// 
// 	if (m_pParentWnd->PostMessage(WM_BINARYOUT_CAN_CHANGE, m_nBinaryIndex, 0) > 0)
// 	{
// 		vm_ChangeBinaryBitVal(m_pBinaryBufRef, m_nBytePos, m_nBitPos);
// 		m_pParentWnd->PostMessage(WM_BINARYOUT_CHANGED, m_nBinaryIndex, (LPARAM)this);
// 
// 		return TRUE;
// 	}
// 	else
	{
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
//CXBinarysDrawBase
CXBinarysDrawBase::CXBinarysDrawBase()
{
	//初始化属性
	m_pBinaryBufRef = NULL;
	m_nBinaryCount = 0;   //开关量数目

	//初始化成员变量
}

CXBinarysDrawBase::~CXBinarysDrawBase()
{
}

void CXBinarysDrawBase::AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow)
{
	POS pos = GetHeadPosition();
	// 	CXDrawCtrlBase *pCtrlBase = NULL;
	// 
	// 	while (pos != NULL)
	// 	{
	// 		pCtrlBase = (CXDrawCtrlBase *)GetNext(pos);
	// 		pCtrlBase->AttachViewWindow(pViewWindow);
	// 	}
}


// void CXBinarysDrawBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 
// }

CSize CXBinarysDrawBase::CalLayout(CSize &szDraw)
{
	CXDrawElements::CalLayout(szDraw);

	m_nWidth = szDraw.cx;
	m_nHeight = szDraw.cy;

	return szDraw;
}

CSize CXBinarysDrawBase::Layout(CPoint &ptTopLeft)
{
	CPoint pt = ptTopLeft;
	m_ptTopLeft = ptTopLeft;

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}
