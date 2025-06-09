#pragma once
#include <map>
#include "WzdDlgButton.h"

struct tagTabColor
{
	COLORREF m_clrBk;
	COLORREF m_clrTxt;
};

class CWzdDlgTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CWzdDlgTabCtrl)

private:
	std::map<int, tagTabColor> m_color;

public:
	CWzdDlgTabCtrl();
	virtual ~CWzdDlgTabCtrl();

public:
	BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetItemColor(long nIndex, COLORREF rgbBk, COLORREF rgbTxt);

	DECLARE_MESSAGE_MAP()
};
