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

// AutoTestBaseTreeView.h : CAutoTestBaseTreeView 类的接口
//


#pragma once

//////////////////////////////////////////////////////////////////////////
//测试用
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseReportView;
class CAutoTestBaseLogicView;

#define ID_GUIDEBOOK_TEST_TREECTRL  3123


class CAutoTestBaseTreeView : public CView
{
protected: // 仅从序列化创建
	CAutoTestBaseTreeView();
	DECLARE_DYNCREATE(CAutoTestBaseTreeView)

public:
	void AdjustLayout(int cx, int cy);//自适应调整尺寸
	CGuideBookTreeCtrl* GetGuideBookTree()							{		return &m_treeGuideBook;		}

// 属性
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;
	CAutoTestBaseReportView *m_pReportView;
	CAutoTestBaseLogicView *m_pLogicView;
	CGuideBookTreeCtrl m_treeGuideBook;

// 操作
public: 
	virtual CRptFillInterface* GetRptFillInterface();
	virtual void CloseTestControl();
	long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop);
	void SelectTestItem(CExBaseObject *pItem);
	void LocateVisio(CExBaseObject *pItem);

	//shaolei 20220622 SV接收压板一致性测试，需要动态生成项目，需要删除或插入
	void InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	void DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	//shaolei 2023-6-14：插入项目时，递归插入子项目
	void InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem);

protected:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// 实现
public:
	virtual ~CAutoTestBaseTreeView();
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
	DECLARE_MESSAGE_MAP()
	
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
public:
	afx_msg void OnDestroy();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // AutoTestBaseTreeView.cpp 中的调试版本
inline CAutoTestBaseDoc* CAutoTestBaseTreeView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

