#pragma once

#include "..\API\GloblaDrawFunctions.h"
// CWndGroupFrame
#define WM_FRAME_EXPAND     (WM_USER+1001)   //框架展开
#define WM_FRAME_CLOSED     (WM_USER+1002)   //框架关闭

class CWndGroupFrame : public CStatic
{
	DECLARE_DYNAMIC(CWndGroupFrame)

public:
#define EXPAND_CLOSE_BUTTUON_WIDTH   10
#define EXPAND_CLOSE_BUTTUON_GAP     3
#define EXPAND_CLOSE_FRAME_POINTS    10
#define ROUND_GAP_X    2
#define ROUND_GAP_Y    2

	static long GetTitleHeight()
	{
		return EXPAND_CLOSE_BUTTUON_WIDTH +EXPAND_CLOSE_BUTTUON_GAP*3;
	}

	long GetLeftGap()
	{
		return m_rcButton.right+EXPAND_CLOSE_BUTTUON_GAP;
	}

public:
	CWndGroupFrame();
	virtual ~CWndGroupFrame();

// Attributes
public:
	CPoint m_ptLeftTop;
	CRect m_rcOrigin;
	CRect m_rcFrame;
	CRect m_rcButton;
	CRect m_rcCurr;
	BOOL  m_bExpand;

	CPoint m_ptFrameExpand[EXPAND_CLOSE_FRAME_POINTS];
	CPoint m_ptFrameClosed[EXPAND_CLOSE_FRAME_POINTS];

	COLORREF m_crFrame;
	COLORREF m_crBack;
	COLORREF m_crTitle;
	COLORREF m_crTitleBack;

	CString m_strTitle;	//关闭时的标题
	long    m_nFrameIndex;

// Operations
public:
	void InitAll();
	CRect GetFrameRect();
	long  GetFrameGap();
	void  Move(CRect rcWnd, BOOL bExpand);
	CRect  AdjustWndRect();
	BOOL UICreate(CRect rcBorder, CWnd *pParent, UINT nID);

	void Resize(CRect rect);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


