#pragma once


// CListBoxEx
#define COLOR_SELECT_BK				RGB(242,248,248)
#define COLOR_SELECT_TEXT				RGB(0,0,0)

typedef struct ListBoxInfo
{
	CString strText;
	COLORREF itemTextColor;
	ListBoxInfo()
	{
		strText.Empty();
		itemTextColor = RGB(0,0,0);
	}
};

class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)

public:
	CListBoxEx();
	virtual ~CListBoxEx();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	
protected:
	DECLARE_MESSAGE_MAP()	

public:
	int AddString(LPCTSTR lpszItem, COLORREF itemColor);
	int InsertString(int nIndex,LPCTSTR lpszItem, COLORREF itemColor);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


