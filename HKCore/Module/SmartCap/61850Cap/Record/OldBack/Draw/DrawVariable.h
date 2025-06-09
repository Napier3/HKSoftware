// DrawVariable.h: interface for the CDrawVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWVARIABLE_H__)
#define _DRAWVARIABLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "..\..\MemBuffer\MemBuffer_CPoint.h"
#include "..\..\MemBuffer\MemBuffer_Float.h"
#include "..\..\MemBuffer\MemBuffer_Long.h"
#include "..\..\..\..\..\Module\Axis\RulerAxis.h"
#include "..\RecordGlobalDefine.h"

#ifdef _SHOW_PARA
#include "DrawParas.h"
#endif

#define VARIABLE_DRAW_STYLE_ALL    0X0000000F
#define VARIABLE_DRAW_STYLE_NAME   0X00000001
#define VARIABLE_DRAW_STYLE_WAVE   0X00000002
#define VARIABLE_DRAW_STYLE_AXIS   0X00000004
#define VARIABLE_DRAW_STYLE_CENTER 0X00000008

class CDrawVariable : public CDrawBase  
{
public:
	CRect m_rcName;
	CRect m_rcAxis;
	CRect m_rcDraw;
	int m_nYCenter;
	CMemBuffer_Long* m_pnAttachBuffer;//long
	CMemBuffer_CPoint* m_pptAttachBuffer;//CPoint
	CMemBuffer_Float*  m_pfAttachBuffer;//float
	CRect* m_pClipRect;
	CRect m_rcNameRectOrigin;//Name区域的初始值
	long m_nTextHeight;//文字的高度
	CRulerAxis m_oRulerAxis;
	CFont m_oNameFont;
	CFont m_oSelectNameFont;
	BOOL m_bNeedDrawCenter;//是否需要绘制中心轴
	MrDraw::DRAWMEMBUFFERPOS m_oBufferPos;
	long m_nSelectedState;

	PDRAWVAR m_pDrawStruct;
#ifdef _SHOW_PARA
	CDrawParas m_oParas;//参数显示管理
#endif
	
public:
	//继承的方法
	virtual void SetBorder(const CRect &rect, BOOL bSavePos);
	virtual void SetBorder(const CRect &rect);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual void SetDrawRectRatio();
	virtual void SetUse(long nUse);
	virtual void SetShow(long nShow);
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, ULONG nDrawStyle=0XFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0, BOOL bUseAcc=FALSE) ;
	virtual void Zoom(double dRate) ;
	virtual void SetParentWnd(CWnd* pParentWnd); //fdp add 2009 12.24
	virtual BOOL CanZoomY()		{	return FALSE;	}
	virtual BOOL CanZoomX()		{	return FALSE;	}
	virtual UINT GetClassID()	{	return 0;		}
	virtual void SetAttachStruct(PDRAWVAR pDrawStruct);

	virtual void SetAxisHeight(long nHeight) ;
	virtual long GetAxisHeight()			 {	return m_rcAxis.Height();	}
	virtual void MoveAxis(long nVertOffset)	 ;
	virtual void SetClipRect(const CRect &rcClip);
	virtual void InitAxis(long nAxisRight);
	virtual void DrawChanName(CDC* pDC);
	void InitAxisSet();
	void CalTextHeight(CDC *pDC);
	void ClearSelectState()   {  m_nSelectedState = DRAW_NONE_OBJECT_SELECTED;  }
	virtual void SetSelect(BOOL bSelect = TRUE);
	void SetNameRect(long nLeft, long nTop, long nRight, long nBottom);
	void SetNameRect(const CRect &rc);
	void SetNameRectTop(long nVal);
	void SetNameRectBottom(long nVal);
	void SetNameRectLeft(long nVal);
	void SetNameRectRight(long nVal);

	void SetParaRectTop(long nVal);
	void SetParaRectBottom(long nVal);

	void SetBorderLeft(long nLeft);		
	void SetBorderRight(long nRight);
	void SetBorderTop(long nTop);
	void SetBorderBottom(long nBottom);
	
	CString GetBufferID()
	{
		if (m_pnAttachBuffer != NULL)
		{
			return m_pnAttachBuffer->m_strBufferID;
		}

		if (m_pfAttachBuffer != NULL)
		{
			return m_pfAttachBuffer->m_strBufferID;
		}

		return _T("");
	}

public:
	CDrawVariable();
	virtual ~CDrawVariable();

};

inline BOOL IsDrawVariable(CDrawBase *pObj)
{
	if (pObj != NULL)
	{
		UINT nClassID = pObj->GetClassID();
		
		if (nClassID == DRAWCLASSID_ANALOGVARIABLE
			|| nClassID == DRAWCLASSID_BINARYVARIABLE
			|| nClassID == DRAWCLASSID_COMPLEXVARIABLE
			|| nClassID == DRAWCLASSID_ATTRSPYVARIABLE )//DRAWCLASSID_ATTRSPYVARIABLE
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

#endif // !defined(_DRAWVARIABLE_H__)
