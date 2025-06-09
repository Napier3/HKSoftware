#if !defined(_XColorEdit_h_)
#define _XColorEdit_h_

#if _MSC_VER > 1000
#pragma once
#endif 

// XColorEdit.h : header file

class CXColorEdit : public CEdit
{
	DECLARE_DYNAMIC(CXColorEdit)
public:
	CXColorEdit();

public:
	COLORREF m_crText;
	COLORREF m_crBack;

public:
	virtual ~CXColorEdit();
	void SetTextColor(COLORREF rgb);
	void SetBackColor(COLORREF rgb);

protected:
	CBrush m_brBackGnd;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);//OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#endif // !defined(_XColorEdit_h_)