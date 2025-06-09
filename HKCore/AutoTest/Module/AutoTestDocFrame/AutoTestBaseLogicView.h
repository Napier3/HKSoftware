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

// AutoTestBaseLogicView.h : CAutoTestBaseLogicView 类的接口
//


#pragma once

#include "../GuideBook/ReportMap/VisioLogicRpt/VisioLogicRptFill.h"
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseDoc;

class CAutoTestBaseLogicView : public CScrollView
{
protected: // 仅从序列化创建
	CAutoTestBaseLogicView();
	DECLARE_DYNCREATE(CAutoTestBaseLogicView)

// 属性
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;

	//增加成员指针
	CVisioLogicRptFill *m_pVisioRptFill;

// 操作
public: 
	virtual void CreateTestControlView(CTestControl *pTestControl);
	virtual void CloseTestControl();
	void LocateVisio(CExBaseObject *pItem);
	void SetParentWnd(CWnd *pParent)	{	m_pParentWnd = pParent;	}
	CWnd* GetParentWnd()	{	return m_pParentWnd;	}

protected:
	CWnd *m_pParentWnd;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// 实现
public:
	virtual ~CAutoTestBaseLogicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) ;

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
	long OnCurrItemStateChanged(CGbItemBase* pItem);
};

#ifndef _DEBUG  // AutoTestBaseLogicView.cpp 中的调试版本
inline CAutoTestBaseDoc* CAutoTestBaseLogicView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

