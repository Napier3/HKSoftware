// DrawTrigCursor.h: interface for the CDrawTrigCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DrawTrigCursor_H__)
#define _DrawTrigCursor_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"

class CDrawTrigCursor : public CDrawBase  
{
public:
	CPoint m_ptTrig[4];
	BOOL m_bCanbeMove;
	CRect m_rcClipRect;
	
public:
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, ULONG nDrawStyle=0XFFFFFFFF);
	virtual void Move(long nHor = 0, long nVer = 0, BOOL bUseAcc=FALSE) ;
	virtual UINT GetClassID()					{	return DRAWCLASSID_TRIGCURSOR;					 }

	void SetClipRect(const CRect &rect);			
	void SetCursorPosition(const CPoint &point) ;
	long GetCursorPosition(long &x, long &y)	 {	x = m_ptTrig[2].x; y= m_ptTrig[2].y;	return 0;}
	long GetCursorPosition(CPoint &point)		 {	point = m_ptTrig[2];				    return 0;}
	CPoint GetCursorPosition()					 {	return m_ptTrig[2];								 }
	void EraseTrigCursor();
	void ShowSet(long nShow);
	BOOL SetTrigCursorPos(long nXPos,long nYPos);//设置光标的位置
	void AttachDrawStruct(PMR1200SYSANALYSEMNGR pDrawVars)	{	m_pDrawStruct = pDrawVars;	}
public:
	CDrawTrigCursor();
	virtual ~CDrawTrigCursor();

private:
	void SetTrigCursorPosition(long nLeft, long nTop, long nRight ,long nBottom , CPoint ptOffSet = CPoint(0,0));

	//关联绘图结构体
	PMR1200SYSANALYSEMNGR m_pDrawStruct;
};

#endif // !defined(_DrawTrigCursor_H__)
