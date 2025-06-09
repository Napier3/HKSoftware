//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawViewBase.h  CXDrawViewBase

#pragma once

#include "XDrawMngr.h"
#include "../BaseClass/XDrawBaseInterface.h"
//////////////////////////////////////////////////////////////////////////
//CXDrawViewBase
class CXDrawViewBase : public CXDrawElements
{
public:
	CXDrawViewBase();
	virtual ~CXDrawViewBase();

//重载函数
public:

   virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);

public:
	CXDrawElement* m_pActiveElement;


//私有成员变量访问方法
public:
	CMemBufferDC m_oDrawMemDC;

//绘图相关函数定义
public:
	virtual BOOL CreateDrawMemDC(CDC *pDC, const CRect &rcClient);				//创建绘图缓存

	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void DrawActiveElement(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

//Message
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

	CXDrawElement* UI_GetActiveXDrawElement(const CPoint &point);
	BOOL UI_SetActiveElement(CXDrawElement *pElement);
};

