#pragma once

class CWzdDlgComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CWzdDlgComboBox)
public:
	CWzdDlgComboBox();
	virtual ~CWzdDlgComboBox();

private:
	COLORREF m_crBorder;

public:
	BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PreSubclassWindow();
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnPaint();

	DECLARE_MESSAGE_MAP()
};