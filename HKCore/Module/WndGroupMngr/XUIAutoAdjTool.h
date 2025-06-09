#pragma once
#include "..\baseclass\TLinkList.h"

class CXUIAdjItemBase
{
public:
	CXUIAdjItemBase();
	virtual ~CXUIAdjItemBase();

public:
	CRect m_rcItemCurrPos;   //控件的新位置
	CRect m_rcItem;             //控件的原始位置
	float	m_fXMoveCoef;		//控件沿x轴移动的百分比
	float	m_fYMoveCoef;		//控件沿y轴移动的百分比
	float	m_fXZoomCoef;		//控件沿x轴缩放的百分比
	float	m_fYZoomCoef;		//控件沿y轴缩放的百分比

	//以下三个用于扩展用
	long m_nMinVisibleWidth;	//控件可见的最小宽度，当窗口的宽度小于该值，则隐藏此控件；如果该值为-1则从不隐藏；
	long m_nMinVisibleHeight;	//控件可见的最小高度，当窗口的高度小于该值，则隐藏此控件；如果该值为-1则从不隐藏；
	BOOL m_bCanHideShow;		//指示窗口缩放时是否根据“最小宽度和最小高度”显示或隐藏控件；

	BOOL XUI_Validate(const CRect &rcItem);
	void XUI_Merge(CRect &rcDest, CRect &rcSrc);
public:
	virtual void XUI_Adjust(long xChange, long yChange);
	virtual void XUI_CalSize();
	virtual void XUI_CalSize(CRect &rcItem);
	virtual void XUI_CalOwnSize(CRect &rcItem);
	virtual void XUI_CalChildrenSize(CRect &rcChildren);

};

class CXUIAdjItem_Wnd : public CXUIAdjItemBase
{
public:
	CXUIAdjItem_Wnd();
	CXUIAdjItem_Wnd(CWnd *pParent, CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	virtual ~CXUIAdjItem_Wnd();

public:
	CWnd *m_pWnd;   //关联的窗口指针

public:
	virtual void XUI_Adjust(long xChange, long yChange);
};

class CXUIAdjItem_Area : public CXUIAdjItemBase, public CTLinkList<CXUIAdjItemBase>
{
public:
	CXUIAdjItem_Area(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area(CWnd *pWnd, CRect rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area();
	virtual ~CXUIAdjItem_Area();

	void XUI_SetParentWnd(CWnd *pWnd);

public:
	virtual void XUI_Adjust(long xChange, long yChange);
	virtual void XUI_CalChildrenSize(CRect &rcChildren);

public:
	CXUIAdjItem_Wnd* XUI_AddWnd(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Wnd* XUI_AddWnd(UINT nID, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area* XUI_AddArea(float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area* XUI_AddArea(const CRect &rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);

	void XUI_OnSize(long cx, long cy);
	void XUI_OnSize();
	BOOL XUI_HasIinit()	{	return m_pXUI_ParentWnd != NULL;	}

protected:
	CWnd *m_pXUI_ParentWnd;

	virtual void XUI_InitAdjust()	{	ASSERT (FALSE);	}
};
