#pragma once
#include <afxext.h>

// CSplitterWndEx

class CSplitterWnd_Ex : public CSplitterWnd
{
	DECLARE_DYNAMIC(CSplitterWnd_Ex)

public:
	CSplitterWnd_Ex();
	virtual ~CSplitterWnd_Ex();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnPaint();

public:

	void setSplitterGap(int nX,int nY);
	void setBorder(int nX,int nY);



protected:
	int m_nLineX;
	int m_nLineY;
	int m_nBorderX;
	int m_nBorderY;
};


