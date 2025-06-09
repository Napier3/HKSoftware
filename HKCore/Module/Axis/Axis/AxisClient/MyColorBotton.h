#if !defined(AFX_MYCOLORBOTTON_H__28AA4F44_A720_48A2_AB1C_4A4AC2855A72__INCLUDED_)
#define AFX_MYCOLORBOTTON_H__28AA4F44_A720_48A2_AB1C_4A4AC2855A72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyColorBotton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyColorBotton window

class CMyColorBotton : public CButton
{
// Construction
public:
	CMyColorBotton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyColorBotton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyColorBotton();
	COLORREF crColor;
	void SetColor(COLORREF,char);
	COLORREF GetColor();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyColorBotton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOLORBOTTON_H__28AA4F44_A720_48A2_AB1C_4A4AC2855A72__INCLUDED_)
