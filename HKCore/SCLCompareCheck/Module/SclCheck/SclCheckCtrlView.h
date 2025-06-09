#pragma once

#include "SclCheckDatasGrid.h"

// CSclCheckCtrlView 窗体视图

class CSclCheckCtrlView : public CFormView
{
	DECLARE_DYNCREATE(CSclCheckCtrlView)

public:
	CSclCheckCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSclCheckCtrlView();

public:
	void ShowGridDatas(CExBaseList *pDatas );
	CSclCheckCtrlGrid m_oSclCheckCtrlGrid;

public:
	enum { IDD = IDD_SCLCHECKCTRLVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};


