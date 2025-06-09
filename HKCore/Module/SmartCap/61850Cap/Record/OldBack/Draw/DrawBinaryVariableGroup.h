// DrawBinaryVariableGroup.h: interface for the CDrawBinaryVariableGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBINARYVARIABLEGROUP_H__A147DED1_81D8_475F_8B18_7A18D4FD731E__INCLUDED_)
#define AFX_DRAWBINARYVARIABLEGROUP_H__A147DED1_81D8_475F_8B18_7A18D4FD731E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBaseList.h"
#include "DrawBinaryVariable.h"

#define CHANSINONEGROUP 16
//这个类的目的是将多个开关量作为一个整体管理和绘制,但是现在没有用到
class CDrawBinaryVariableGroup : public CDrawBaseList  
{
public:
	long m_nCenterY ;
public:
	virtual UINT GetClassID() {	return DRAWCLASSID_BINARYVARIABLEGROUP;	}
	//继承的方法
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, ULONG nDrawStyle=0XFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void SetBorder(const CRect &rect);
public:
	CDrawBinaryVariableGroup();
	virtual ~CDrawBinaryVariableGroup();
};

#endif // !defined(AFX_DRAWBINARYVARIABLEGROUP_H__A147DED1_81D8_475F_8B18_7A18D4FD731E__INCLUDED_)
