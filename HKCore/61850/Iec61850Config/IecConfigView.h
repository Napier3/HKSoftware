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

// IecConfigView.h : CIecConfigView 类的接口
//


#pragma once

#include "IecCfgSmvViewMain.h"
#include "IecCfgGoutViewMain.h"
#include "IecCfgGinViewMain.h"
#include "..\Module\ScdDraw\XscdViewMain.h"
#include "IecCfgSysParasView.h"

//#define _use_CXscdViewMain

class CIecConfigView : public CFormView
{
protected: // 仅从序列化创建
	CIecConfigView();
	DECLARE_DYNCREATE(CIecConfigView)

public:
	enum{ IDD = IDD_IEC61850CONFIG_FORM };

// 属性
public:
	CIecConfigDoc* GetDocument() const;
	CMFCTabCtrl m_tabPara;

#ifdef _use_CXscdViewMain
	CXscdViewCfgMain *m_pXscdViewMain;
#endif

	CIecCfgSmvViewMain *m_pViewSmvMain;
	CIecCfgGinViewMain *m_pViewGinMain;
	CIecCfgGoutViewMain *m_pViewGoutMain;
	CIecCfgSysParasView *m_pSysParasView;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

// 实现
public:
	virtual ~CIecConfigView();
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

#ifndef _DEBUG  // IecConfigView.cpp 中的调试版本
inline CIecConfigDoc* CIecConfigView::GetDocument() const
   { return reinterpret_cast<CIecConfigDoc*>(m_pDocument); }
#endif

