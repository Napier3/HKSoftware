#pragma once

class CWzdDlgEdit : public CEdit
{
	DECLARE_DYNAMIC(CWzdDlgEdit)
private:
	COLORREF m_crBorder;

public:
	CWzdDlgEdit();
	virtual ~CWzdDlgEdit();

public:
	BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	void SetBorderColor(COLORREF color) { m_crBorder = color; }

	DECLARE_MESSAGE_MAP()
};