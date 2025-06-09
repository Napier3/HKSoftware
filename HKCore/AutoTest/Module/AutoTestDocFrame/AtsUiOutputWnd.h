
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口
#include "AtsUiTestStatusButton.h"
#include "AtsUiTabCtrl.h"

class CAtsUiOutputWnd : public CDockablePane
{
// 构造
public:
	CAtsUiOutputWnd();
	void CreateTestTempFile()	{			m_wndTabs.CreateTestTempFile();	}
	void EmptyGridInlegibleTestItem()	{	m_wndTabs.EmptyGridInlegibleTestItem();	}
	void AttachMainFrame(CWnd *pWnd)	{	m_wndTabs.AttachMainFrame(pWnd);	}

	void AdjustLog(HWND hLogParent);

// 属性
public:
	CFont m_Font;
	CAtsUiTabCtrl	m_wndTabs;
	
//	void SetTestControl(CTestControl* pTestControl)					{		m_wndTabs.m_btnTest.SetTestControl(pTestControl);		}
//	void UpdateTestItemsState()															{		m_wndTabs.m_btnTest.Invalidate(FALSE);		}

	void OutPutString(const CString& str);
	void AddOutPutString(const CString &str);


protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// 实现
public:
	virtual ~CAtsUiOutputWnd();

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