// DrawTimeCursor.h: interface for the CDrawTimeCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DrawTimeCursor_H__EAA5F417_35B9_4F9F_B548_84612620E734__INCLUDED_)
#define AFX_DrawTimeCursor_H__EAA5F417_35B9_4F9F_B548_84612620E734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _PSX_IDE_QT_
#include "../../BaseClass/DIB.h"
#endif
#include "DrawGlobalDef.h"
#include "DrawBase.h"

#define  USETIMECURSORA 0
#define  USETIMECURSORB 1
#define  WIDTHTOCENTER  4

class CDrawTimeCursor : public CDrawBase  
{
public:
	//关键字
	static const char* g_pszKeyZoomBmp;

	long m_nCurrCursorID;
	long m_nXA;
	long m_nXB;
	long m_nXAOld;
	long m_nXBOld;
	//画笔
	CPen m_ACursorPen;
	CPen m_BCursorPen;
	COLORREF m_crATimeCursorColor;
	COLORREF m_crBTimeCursorColor;
	//操作设置
	BOOL m_bCanMoveACursor;
	BOOL m_bCanMoveBCursor;
	HCURSOR m_hMoveCursor;

	//	
	CRect m_rcZoomBmp;
	CRect m_rcZoomBmpOld;
	BOOL  m_bUseZoomBmp;
#ifndef _PSX_IDE_QT_
	CDib m_oDib;
#endif
public:
	//继承的方法
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	//virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Move(long nHor = 0, long nVer = 0, BOOL bUseAcc = TRUE) ;
	virtual void SetBorder(const CRect &rect);
	virtual UINT GetClassID()				{	return CMTRDCLASSID_TIMECURSOR;	   }

	//自身的方法
	void SetCurrentCursor(long nCursorID);
	long GetCurrCursorID();
	long SetCursorPosition(long nPos, long nCursorID = -1);
	long GetCursorPosition(long nCursorID = -1);
	void GetTwoCursorPosition(long& nXA,long& nXB) { nXA = m_nXA; nXB = m_nXB;	}
	void EraseATimeLine();
	void EraseBTimeLine();
	void SetMoveCursor(HCURSOR hCursor)     {    m_hMoveCursor = hCursor;      }
	void ShowSet(long nShow);
	void GetCurrCursorInvalidateRect(CRect &rcOld, CRect &rcNew);
	void GetInvalidateRect(CRect &rcOld, CRect &rcNew);
	long GetCurrentCursorPosition();
public:
	void DrawBCursor(CDC* pDC);
	void DrawACursor(CDC* pDC);
	CDrawTimeCursor();
	virtual ~CDrawTimeCursor();
private:
	void ChangeCursorPosition(long& nPosition , long nCurrentX);//改变时间光标位置
	void SetZoomRect();
	long m_nZoomMode; // 0-放大，1－缩小，2－还原
	void SetZoomMode(CPoint point);
};

#endif // !defined(AFX_DrawTimeCursor_H__EAA5F417_35B9_4F9F_B548_84612620E734__INCLUDED_)
