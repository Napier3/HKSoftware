// DrawBinaryVariable.h: interface for the CDrawBinaryVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DrawBinaryVariable_H__0C352207_378D_4574_8A01_A224B9393D50__INCLUDED_)
#define AFX_DrawBinaryVariable_H__0C352207_378D_4574_8A01_A224B9393D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawVariable.h"
class CDrawBinaryVariable : public CDrawVariable  
{
public:
	UINT m_nChanIndex;

public:
//	virtual void SetBorder(const CRect &rect, BOOL bSavePos);
	virtual void SetBorder(const CRect &rect);
	//继承的方法
// 	virtual LONG MouseMove(UINT nFlags, CPoint &point);
// 	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
// 	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
// 	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
// 	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void SetAttachStruct(PRECORDDRAWOBJECTCONTROL pDrawStruct)	{	m_pDrawStruct = pDrawStruct;	}
	virtual BOOL CanZoomY()			{	return FALSE;	}
	virtual BOOL CanZoomX()			{	return TRUE;	}
	virtual UINT GetClassID()		{	return CMTRDCLASSID_BINARYVARIABLE;		}
	virtual void InitAxis(long nAxisRight);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	
	//自身的方法
	void SetChanIndex(long nIndex)	{	m_nChanIndex = nIndex;	}
	long GetChanIndex()				{	return m_nChanIndex;	}

public:
	CDrawBinaryVariable();
	virtual ~CDrawBinaryVariable();

private:
	void DrawBinary(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
};

#endif // !defined(AFX_DrawBinaryVariable_H__0C352207_378D_4574_8A01_A224B9393D50__INCLUDED_)
