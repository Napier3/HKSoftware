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

// StateToolView.h : CStateToolView 类的接口
//


#pragma once

#include "..\..\AutoTest\Module\GbMacroUIInterface.h"

class CStateToolView : public CFormView
{
protected: // 仅从序列化创建
	CStateToolView();
	DECLARE_DYNCREATE(CStateToolView)
	CGbMacroUI *m_pGbMacroUI;

	void CreateGbUI();
public:
	enum{ IDD = IDD_STATETOOL_FORM };

// 属性
public:
	CStateToolDoc* GetDocument() const;

// 操作
public:
	void GetTestPara(CString &strParas);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CStateToolView();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // StateToolView.cpp 中的调试版本
inline CStateToolDoc* CStateToolView::GetDocument() const
   { return reinterpret_cast<CStateToolDoc*>(m_pDocument); }
#endif

