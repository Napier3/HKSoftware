#if !defined(AFX_UIWNDLISTPOOL_H__035F6327_1682_4BD1_8241_617800A70A0C__INCLUDED_)
#define AFX_UIWNDLISTPOOL_H__035F6327_1682_4BD1_8241_617800A70A0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UIWndListPool.h : header file
//

//#define IDD_UI_WINDOW                   129
#include "UIMemDC.H"
#include "..\BaseClass\DIB.h"
#include "UIBaseGlobal.h"

/////////////////////////////////////////////////////////////////////////////
// CUIWndListPool dialog

class CUIWndListPool : public CDialog
{
// Construction
public:
	CUIWndListPool(CWnd* pParent = NULL);   // standard constructor
	void CreateUIWndListPool(UINT nIDD, CWnd* pParent)	{		Create(nIDD, pParent);	}//创建窗口,没有使用,在实际中创建窗口的时候,直接调用Create()创建窗口
	BOOL m_bHasInited;//没有用到
	void CreateUIMenDC();//没有用到

	COLORREF m_crBkColorFrom;
	COLORREF m_crBkColorTo;
	DWORD    m_dwPoolType;

	void     SetDibBackBitmap(CDib *pDib)
	{
		m_pDibBack = pDib;
	}
	
	void SetType(const CString &strType);
	BOOL CreatePool(CWnd *pParent, BOOL &bNeedCenterWnd);

	//enum { IDD = IDD_UI_WINDOW };
// Dialog Data
	//{{AFX_DATA(CUIWndListPool)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIWndListPool)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUIWndListPool)
	virtual BOOL OnInitDialog();
	virtual void OnOK();//重载此函数要避免按下Enter或Esc键使对话框关闭,所以要注释掉CDialog::OnOK
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDib *m_pDibBack;

public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIWNDLISTPOOL_H__035F6327_1682_4BD1_8241_617800A70A0C__INCLUDED_)
