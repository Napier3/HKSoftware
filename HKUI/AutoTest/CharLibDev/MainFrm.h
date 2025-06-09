﻿// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "CharLibPane.h"
#include "OutputWnd.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:

// 操作
public:
	void UpdateCharTemp(CCharacteristic *pCharTemp);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CCharLibPane        m_wndCharLibView;
	COutputWnd        m_wndOutput;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnCharoptrNewchar();
	afx_msg void OnCharoptrSave();
	afx_msg void OnUpdateCharoptrSave(CCmdUI *pCmdUI);
	afx_msg void OnCharoptrSaveas();
	afx_msg void OnUpdateCharoptrSaveas(CCmdUI *pCmdUI);
	afx_msg void OnCharoptrDelete();
	afx_msg void OnUpdateCharoptrDelete(CCmdUI *pCmdUI);
	afx_msg void OnCharoptrExport();
	afx_msg void OnUpdateCharoptrExport(CCmdUI *pCmdUI);
	afx_msg void OnViewCharpane();
	afx_msg void OnUpdateViewCharpane(CCmdUI *pCmdUI);
	afx_msg void OnViewOutputwnd();
	afx_msg void OnUpdateViewOutputwnd(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnCharoptrImportfromriofile();
};


