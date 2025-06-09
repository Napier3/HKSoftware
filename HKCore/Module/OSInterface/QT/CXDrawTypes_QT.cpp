#include "stdafx.h"
#include "CXDrawTypes_QT.h"


// CSize
CSize::CSize()
	{ /* random filled */ }
CSize::CSize(int initCX, int initCY)
	{ cx = initCX; cy = initCY; }
CSize::CSize(SIZE initSize)
	{ *(SIZE*)this = initSize; }
CSize::CSize(POINT initPt)
	{ *(POINT*)this = initPt; }
CSize::CSize(DWORD dwSize)
	{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
	}
BOOL CSize::operator==(SIZE size) const
	{ return (cx == size.cx && cy == size.cy); }
BOOL CSize::operator!=(SIZE size) const
	{ return (cx != size.cx || cy != size.cy); }
void CSize::operator+=(SIZE size)
	{ cx += size.cx; cy += size.cy; }
void CSize::operator-=(SIZE size)
	{ cx -= size.cx; cy -= size.cy; }
void CSize::SetSize(int CX, int CY)
	{ cx = CX; cy = CY; }	
CSize CSize::operator+(SIZE size) const
	{ return CSize(cx + size.cx, cy + size.cy); }
CSize CSize::operator-(SIZE size) const
	{ return CSize(cx - size.cx, cy - size.cy); }
CSize CSize::operator-() const
	{ return CSize(-cx, -cy); }
CPoint CSize::operator+(POINT point) const
	{ return CPoint(cx + point.x, cy + point.y); }
CPoint CSize::operator-(POINT point) const
	{ return CPoint(cx - point.x, cy - point.y); }

// CPoint
CPoint::CPoint()
	{ /* random filled */ }
CPoint::CPoint(int initX, int initY)
	{ x = initX; y = initY; }
CPoint::CPoint(POINT initPt)
	{ *(POINT*)this = initPt; }
CPoint::CPoint(SIZE initSize)
	{ *(SIZE*)this = initSize; }

void CPoint::Offset(int xOffset, int yOffset)
	{ x += xOffset; y += yOffset; }
void CPoint::Offset(POINT point)
	{ x += point.x; y += point.y; }
void CPoint::Offset(SIZE size)
	{ x += size.cx; y += size.cy; }
void CPoint::SetPoint(int X, int Y)
	{ x = X; y = Y; }
BOOL CPoint::operator==(POINT point) const
	{ return (x == point.x && y == point.y); }
BOOL CPoint::operator==(CPoint &point) const
{
    return (x == point.x && y == point.y);
}
BOOL CPoint::operator!=(POINT point) const
	{ return (x != point.x || y != point.y); }
void CPoint::operator+=(SIZE size)
	{ x += size.cx; y += size.cy; }
void CPoint::operator-=(SIZE size)
	{ x -= size.cx; y -= size.cy; }
void CPoint::operator+=(POINT point)
	{ x += point.x; y += point.y; }
void CPoint::operator-=(POINT point)
	{ x -= point.x; y -= point.y; }
CPoint CPoint::operator+(SIZE size) const
	{ return CPoint(x + size.cx, y + size.cy); }
CPoint CPoint::operator-(SIZE size) const
	{ return CPoint(x - size.cx, y - size.cy); }
CPoint CPoint::operator-() const
	{ return CPoint(-x, -y); }
CPoint CPoint::operator+(POINT point) const
	{ return CPoint(x + point.x, y + point.y); }
CSize CPoint::operator-(POINT point) const
	{ return CSize(x - point.x, y - point.y); }

// CRect
CRect::CRect()
	{ /* random filled */ }
CRect::CRect(int l, int t, int r, int b)
	{ left = l; top = t; right = r; bottom = b; }
CRect::CRect(const RECT& srcRect)
{
    left = srcRect.left;
    top = srcRect.left;
    right = srcRect.right;
    bottom = srcRect.bottom;
}

void CRect::CopyRect(RECT &rcDst, const RECT &rcSrc)
{
    rcDst.left = rcSrc.left;
    rcDst.top = rcSrc.left;
    rcDst.right = rcSrc.right;
    rcDst.bottom = rcSrc.bottom;
}

void CRect::CopyRect(RECT *rcDst, const RECT *rcSrc)
{
    CopyRect(*rcDst, *rcSrc);
}

BOOL CRect::EqualRect(const RECT *pRect)
{
    return EqualRect(*pRect);
}

BOOL CRect::EqualRect(const RECT &rcRect)
{
    return ((left == rcRect.left)
            && (right == rcRect.right)
            && (top == rcRect.top)
            && (bottom == rcRect.bottom));
}


CRect::CRect(POINT point, SIZE size)
	{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
CRect::CRect(POINT topLeft, POINT bottomRight)
	{ left = topLeft.x; top = topLeft.y;
		right = bottomRight.x; bottom = bottomRight.y; }
int CRect::Width() const
	{ return right - left; }
int CRect::Height() const
	{ return bottom - top; }
CSize CRect::Size() const
	{ return CSize(right - left, bottom - top); }
CPoint& CRect::TopLeft()
	{ return *((CPoint*)this); }
CPoint& CRect::BottomRight()
	{ return *((CPoint*)this+1); }
const CPoint& CRect::TopLeft() const
	{ return *((CPoint*)this); }
const CPoint& CRect::BottomRight() const
	{ return *((CPoint*)this+1); }
CPoint CRect::CenterPoint() const
	{ return CPoint((left+right)/2, (top+bottom)/2); }
void CRect::SetRect(int x1, int y1, int x2, int y2)
{
    left = x1;
    top = y1;
    right = x2;
    bottom = y2;
}

void CRect::SetRect(POINT topLeft, POINT bottomRight)
{
    SetRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

BOOL CRect::PtInRect(POINT point) const
{
    return PtInRect(point.x, point.y);
}


BOOL CRect::PtInRect(const CPoint &point) const
{
    return PtInRect(point.x, point.y);
}

#if 0
void CRect::SwapLeftRight()
    { SwapLeftRight(LPRECT(this)); }
void WINAPI CRect::SwapLeftRight(LPRECT lpRect)
    { LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
CRect::operator LPRECT()
	{ return this; }
CRect::operator PRECT() const
	{ return this; }
BOOL CRect::IsRectEmpty() const
	{ return ::IsRectEmpty(this); }
BOOL CRect::IsRectNull() const
	{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
void CRect::SetRect(int x1, int y1, int x2, int y2)
	{ ::SetRect(this, x1, y1, x2, y2); }
void CRect::SetRect(POINT topLeft, POINT bottomRight)
	{ ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void CRect::SetRectEmpty()
	{ ::SetRectEmpty(this); }
void CRect::CopyRect(PRECT lpSrcRect)
{
    left = lpSrcRect->left;
    top = lpSrcRect->left;
    right = lpSrcRect->right;
    bottom = lpSrcRect->bottom;
}
BOOL CRect::EqualRect(PRECT lpRect) const
    { return ::EqualRect(this, lpRect); }
#endif

void CRect::InflateRect(int x, int y)
{
    left -= x;
    right += x;
    top -= y;
    bottom += y;

    if (left > right)
    {
        int i = right;
        right = left;
        left = i;
    }

    if (top > bottom)
    {
        int i = bottom;
        bottom = top;
        top = i;
    }
}

void CRect::InflateRect(SIZE size)
    { InflateRect(size.cx, size.cy); }
void CRect::DeflateRect(int x, int y)
    { InflateRect(-x, -y); }
void CRect::DeflateRect(SIZE size)
    { InflateRect(-size.cx, -size.cy); }
void CRect::OffsetRect(int x, int y)
{
    left += x;
    right += x;
    top += y;
    bottom += y;
}

void CRect::OffsetRect(POINT point)
    { OffsetRect(point.x, point.y); }
void CRect::OffsetRect(SIZE size)
    { OffsetRect(size.cx, size.cy); }
void CRect::MoveToY(int y)
	{ bottom = Height() + y; top = y; }
void CRect::MoveToX(int x)
	{ right = Width() + x; left = x; }
void CRect::MoveToXY(int x, int y)
	{ MoveToX(x); MoveToY(y); }
void CRect::MoveToXY(POINT pt)
	{ MoveToX(pt.x); MoveToY(pt.y); }

#if 0
BOOL CRect::IntersectRect(PRECT lpRect1, PRECT lpRect2)
    { return ::IntersectRect(this, lpRect1, lpRect2);}
BOOL CRect::UnionRect(PRECT lpRect1, PRECT lpRect2)
    { return ::UnionRect(this, lpRect1, lpRect2); }
#endif

void CopyRect()
{
}

BOOL CRect::operator==(const RECT& rect) const
    { return QT_EqualRect(this, &rect); }
BOOL CRect::operator!=(const RECT& rect) const
    { return !QT_EqualRect(this, &rect); }
void CRect::operator+=(POINT point)
    { OffsetRect(point.x, point.y); }
void CRect::operator+=(SIZE size)
    { OffsetRect(size.cx, size.cy); }
void CRect::operator+=(PRECT lpRect)
    { InflateRect(lpRect); }
void CRect::operator-=(POINT point)
    { OffsetRect(-point.x, -point.y); }
void CRect::operator-=(SIZE size)
    { OffsetRect(-size.cx, -size.cy); }
void CRect::operator-=(PRECT lpRect)
    { DeflateRect(lpRect); }

#if 0
void CRect::operator&=(const RECT& rect)
	{ ::IntersectRect(this, this, &rect); }
void CRect::operator|=(const RECT& rect)
	{ ::UnionRect(this, this, &rect); }
CRect CRect::operator+(POINT pt) const
	{ CRect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
CRect CRect::operator-(POINT pt) const
	{ CRect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
CRect CRect::operator+(SIZE size) const
	{ CRect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
CRect CRect::operator-(SIZE size) const
	{ CRect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
CRect CRect::operator+(PRECT lpRect) const
    { CRect rect(this); rect.InflateRect(lpRect); return rect; }
CRect CRect::operator-(PRECT lpRect) const
    { CRect rect(this); rect.DeflateRect(lpRect); return rect; }
CRect CRect::operator&(const RECT& rect2) const
	{ CRect rect; ::IntersectRect(&rect, this, &rect2);
		return rect; }
CRect CRect::operator|(const RECT& rect2) const
	{ CRect rect; ::UnionRect(&rect, this, &rect2);
		return rect; }
BOOL CRect::SubtractRect(PRECT lpRectSrc1, PRECT lpRectSrc2)
    { return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }
#endif


void CRect::NormalizeRect()
	{
		int nTemp;
		if (left > right)
		{
			nTemp = left;
			left = right;
			right = nTemp;
		}
		if (top > bottom)
		{
			nTemp = top;
			top = bottom;
			bottom = nTemp;
		}
	}

void CRect::InflateRect(PRECT lpRect)
	{
        left -= lpRect->left;		top -= lpRect->top;
        right += lpRect->right;		bottom += lpRect->bottom;
	}

void CRect::InflateRect(int l, int t, int r, int b)
	{
		left -= l;			top -= t;
		right += r;			bottom += b;
	}

void CRect::DeflateRect(PRECT lpRect)
	{
        left += lpRect->left;	top += lpRect->top;
        right -= lpRect->right;	bottom -= lpRect->bottom;
	}

void CRect::DeflateRect(int l, int t, int r, int b)
	{
		left += l;		top += t;
		right -= r;		bottom -= b;
	}

#if 0
CRect CRect::MulDiv(int nMultiplier, int nDivisor) const
	{
		return CRect(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}

#endif
