//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawElement.h  CXDrawElement

#pragma once

#include "../BaseClass/ExBaseList.h"

#define XDRAW_STATE_NORMAL  0
#define XDRAW_STATE_PICKED  0X00000001

#define XCREATE_SUCC        1
#define XCREATE_FAIL        0

#define GETSIZE_MODE_XMAX_YADD   0
#define GETSIZE_MODE_XADD_YMAX   1
#define GETSIZE_MODE_XADD_YADD   2

#define XDRAW_BASECLASS         (CLASSID_BASECLASS + 0X07000000)
#define XDRAW_EXLISTCLASS       (CLASSID_LISTCLASS + 0X07000000)

// #define _XDRAW_USE_EXTERN_ATTR_

class CXDrawElement : public CExBaseList
{
public:
	CXDrawElement();
	virtual ~CXDrawElement();

	CPoint m_ptTopLeft;
	long   m_nWidth, m_nHeight;
	COLORREF  m_crBkColor;
	COLORREF  m_crForeColor;
	DWORD m_dwState;
	CExBaseObject *m_pXDrawDataRef;

#ifdef _XDRAW_USE_EXTERN_ATTR_
	long  m_nEnable;
	long  m_nShow;
	BOOL m_bSelect;
	long m_nUse;
#endif

	CWnd *m_pParentWnd;//如果需要给父窗口发消息时使用

public:
	static COLORREF  m_crPickColor;
	static DWORD  m_nPickStyle;
	static long   m_nPickWidth;
	static CXDrawElement* g_pActiveElement;

	static CPoint g_ptOrigin;
	static CPoint g_ptCurrent;
	static BOOL   g_bLButtonDown;

	//重载函数
public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	CPoint GetTopCenter();
	CPoint GetLeftCenter();
	CPoint GetBottomCenter();
	CPoint GetRightCenter();
	CPoint CenterPoint();
	long Right();
	long Bottom();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
	virtual void SetPickState(BOOL bPick=FALSE);
	virtual BOOL IsPicked()	{	return ((m_dwState & XDRAW_STATE_PICKED) > 0);	}

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF) = 0;
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual BOOL IsPointInRect(const CPoint &point);

	virtual CXDrawElement* QueryByXDrawDataRef(CExBaseObject *pDrawDataRef);
	virtual CXDrawElement* QueryChildrenByXDrawDataRef(CExBaseObject *pDrawDataRef);

public:
	void SetColor(COLORREF cr)                    {    m_crForeColor = cr;              }
	COLORREF GetColor()                           {    return m_crForeColor;            }
	virtual void SetBorder(const CRect &rect) ;
	virtual CRect GetBorder() ;
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual void Move(long nHor = 0, long nVer = 0);
	virtual BOOL CanZoomY()								{    return FALSE;							}
	virtual BOOL CanZoomX()								{    return FALSE;							}
	virtual void Zoom(double dRate) ;
	virtual void SetParentWnd(CWnd* pParentWnd)	  {	   m_pParentWnd = pParentWnd;	}

#ifdef _XDRAW_USE_EXTERN_ATTR_
	virtual void SetSelect(BOOL bSelect = TRUE)   {    m_bSelect = bSelect;         }
	virtual BOOL GetSelect()                      {    return m_bSelect;            }
	virtual long GetShow()						  {	   return m_nShow;				}
	virtual void SetShow(long nShow)			  {	   m_nShow = nShow;				}
	virtual void SetUse(long nUse)		{	m_nUse = nUse;	}
	virtual long GetUse()				{	return m_nUse;	}	
#endif

//////////////////////////////////////////////////////////////////////////
//消息函数
public:
	virtual void UI_OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void UI_OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void UI_OnSize(UINT nType, int cx, int cy);
	virtual void UI_OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL UI_OnLButtonDown(UINT nFlags, CPoint point);
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);
	virtual void UI_OnTimer(UINT nIDEvent);
	virtual UINT UI_OnGetDlgCode();
	virtual BOOL UI_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL UI_OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void UI_OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void UI_OnRButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL UI_OnEraseBkgnd(CDC* pDC);
	virtual BOOL UI_OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void UI_OnSysColorChange();
	virtual void UI_OnCaptureChanged(CWnd *pWnd);
	virtual void UI_OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	virtual void UI_OnRButtonUp(UINT nFlags, CPoint point);
	virtual void UI_OnKillFocus(CWnd* pNewWnd);	

#if _MFC_VER >= 0x0421
	virtual void UI_OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	virtual BOOL UI_OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif

	virtual LRESULT UI_OnSetFont(WPARAM hFont, LPARAM lParam);
	virtual LRESULT UI_OnGetFont(WPARAM hFont, LPARAM lParam);
	virtual void UI_OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void UI_OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void UI_OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult);

	virtual LRESULT UI_OnFillComboBox(WPARAM nColumn, LPARAM pListBox);
	virtual LRESULT UI_OnFillList(WPARAM nColumn, LPARAM pListBox);
	virtual LRESULT UI_OnFillTree(WPARAM nColumn, LPARAM pListBox);
	virtual LRESULT UI_OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox);
	virtual void UI_OnRButtonDown(UINT nFlags, CPoint point);

	virtual void UI_KillFocus();
//////////////////////////////////////////////////////////////////////////
//根据数据对象构建绘图元素
public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CXDrawElement* XCreateChildElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CXDrawElement* XCreateChildElement(UINT nClassID);
	virtual DWORD XCreateElementChildren(CExBaseList *pDatas, CWnd *pParentWnd){	return XCREATE_FAIL;	};
	virtual void InitAfterCreateElement(CWnd *pParentWnd){}

//////////////////////////////////////////////////////////////////////////
//创建绘图
public:
	//创建绘图对象

	//布局
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize CalLayoutOwn(CSize &szDraw);
	virtual CSize CalLayoutChildren(CSize &szDraw);
	virtual void  GetSize(CSize &sz, DWORD dwMode);

};

CString XDraw_GetLineStype(UINT nStyle);
UINT XDraw_GetLineStyle(const CString &strStyle);
BOOL XDraw_Is_XDrawElement(CExBaseObject *pObj);
BOOL XDraw_Is_XDrawElement(UINT nClassID);
