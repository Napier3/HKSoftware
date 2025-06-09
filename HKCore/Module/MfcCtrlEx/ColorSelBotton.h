#if !defined(_ColorSelBotton_h__)
#define _ColorSelBotton_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorSelBotton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorSelBotton window

class CColorSelBotton : public CButton
{
// Construction
public:
	CColorSelBotton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelBotton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorSelBotton();
	COLORREF m_crColor;
	void SetColor(COLORREF,BOOL bInvalid=TRUE);
	COLORREF GetColor();
	BOOL SelColor(CWnd *pParent);

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorSelBotton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ColorSelBotton_h__)
