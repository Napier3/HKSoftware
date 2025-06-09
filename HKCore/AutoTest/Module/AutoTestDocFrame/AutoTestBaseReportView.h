// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// AutoTestBaseReportView.h : CAutoTestBaseReportView 类的接口
//


#pragma once

//////////////////////////////////////////////////////////////////////////
//测试用
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseDoc;
class CAutoTestBaseTreeView;

class CAutoTestBaseReportView : public CScrollView
{
protected:// 仅从序列化创建
	CAutoTestBaseReportView();
	DECLARE_DYNCREATE(CAutoTestBaseReportView)

// 属性
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;
	UINT m_nTestControlMode;
	CAutoTestBaseTreeView *m_pTreeView;

// 操作
public: 
	virtual CRptFillInterface* GetRptFillInterface();
	virtual long OpenReportView();
	virtual void CreateTestControlView(CTestControl *pTestControl);
	virtual void CloseTestControl();

protected:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// 实现
public:
	virtual ~CAutoTestBaseReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) ;
	afx_msg LRESULT OnCreateNewTestProject(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAdjustViewSize(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	afx_msg void OnDestroy();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // AutoTestBaseReportView.cpp 中的调试版本
inline CAutoTestBaseDoc* CAutoTestBaseReportView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

