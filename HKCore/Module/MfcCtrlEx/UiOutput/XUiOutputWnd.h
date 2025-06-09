
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ����
#include "XUiTabCtrl.h"

class CXUiOutputWnd : public CDockablePane
{
// ����
public:
	CXUiOutputWnd();
	void AttachMainFrame(CWnd *pWnd)	{	m_wndTabs.AttachMainFrame(pWnd);	}

// ����
public:
	CFont m_Font;
	CXUiTabCtrl	m_wndTabs;

	void OutPutString(const CString& str);
	void AddOutPutString(const CString &str);


protected:
	void AdjustHorzScroll(CListBox& wndListBox);

// ʵ��
public:
	virtual ~CXUiOutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};