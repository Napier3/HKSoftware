#pragma once


// CMyMFCTabCtrl

#include "XUiOutputLog.h"

class CXUiTabCtrl : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CXUiTabCtrl)

public:
	CXUiTabCtrl();
	virtual ~CXUiTabCtrl();
	void AttachMainFrame(CWnd *pWnd)	{	m_pMainFrame = pWnd;	}

public:
	CXUiOutputLog *m_pWndInfo;						//提示信息窗口

	CFont m_Font;
	CWnd *m_pMainFrame;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();

};


