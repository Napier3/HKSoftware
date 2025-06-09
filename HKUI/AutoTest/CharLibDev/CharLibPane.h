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

#pragma once
#include "..\..\Module\XLanguage\XLangToolBar.h"
#include "..\Module\Characteristic\CharLibTreeCtrl.h"

class CClassToolBar : public CXLangToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

#define IDC_CHARLIB_REECTRL    6932
class CCharLibPane : public CDockablePane
{
public:
	CCharLibPane();
	virtual ~CCharLibPane();

	void AdjustLayout();
	void OnChangeVisualStyle();

	void ShowCharLib();
	void InsertCharTemp(CCharacteristic *pCharTemp);
	void UpdateCharTemp(CCharacteristic *pCharTemp);
	CCharacterFolder* GetCurrSelFolder();

protected:
	CClassToolBar m_wndToolBar;
	CCharLibTreeCtrl m_wndCharLibView;
	CImageList m_CharLibViewImages;
	UINT m_nCurrSort;

// 重写
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnEditFolder();
	afx_msg void OnUpdateEditFolder(CCmdUI* pCmdUI);
	afx_msg void OnDeleteFolder();
	afx_msg void OnUpdateDeleteFolder(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);
	afx_msg void OnNMDblclkCharLibTree(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
};

