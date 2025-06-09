#pragma once

#include "..\XfileMngrBase\XFileMngrTreeCtrl.h"
#include "..\FilterText\FilterTextComboBox.h"
#include "XFileDlgDefine.h"
#include "..\XLanguage\XLangToolBar.h"

// CXFileDockablePane

#define XID_XFILE_DOCPANE   2121

class CTaskFileToolBar : public CXLangToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{ 
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};



class CXFileDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CXFileDockablePane)

public:
	CXFileDockablePane();
	virtual ~CXFileDockablePane();

	void ShowXFileTree(CXFileMngr* pXFileMngr);
	void AdjustLayout();//自适应调整尺寸
	CXFileMngrTreeCtrl* GetGbEditTree()							{		return &m_wndXFileTree;		}
	void OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile);
	CXFolder* OnSaveAsFolder(CXFolder *pCurrFolder, const CString &strFolder);

	void SetIDB_XFILEMNGR(UINT nIDB_XFILEMNGR)
	{
		m_nIDB_XFILEMNGR = nIDB_XFILEMNGR;
	}
	void SetXFileMsgRcvWnd(CXFileOptrMsgRcvWnd *pWnd);
	void SetFilterTextMngr(CFilterTextMngr *pFilterTextMngr)	
	{	
		FreeFilterTextMngr();
		m_bFilterTextMngrCreate = FALSE;
		m_pFilterTextMngr = pFilterTextMngr;
	}

	void CreateFilterTextMngr(const CString &strFile);
	void SetDeleteAllFolder(BOOL bDeleteAllFolder)	{	m_bDeleteAllFolder = bDeleteAllFolder;	}
	void InsertFolderToTree(CXFolder *pXFolder);
	void UpdateTree();
	void DeleteFile(CXFile *pXFile);  //2017-2-17  lijunqing

	//shaolei 2021.08.21
	void SelectRoot();

// 属性
protected:
	CXFileMngrTreeCtrl m_wndXFileTree;

	UINT m_nIDB_XFILEMNGR;
	CBmpImageList m_XFileImages;

	UINT m_nIDR_XFILEMNGR_TOOLBAR;
	CTaskFileToolBar m_wndXToolBar;

	BOOL m_bFilterTextMngrCreate;
	CFilterTextMngr *m_pFilterTextMngr;
	CFilterTextComboBox m_cmbFilterText;
	CButton m_btnFilter;

	CXFileMngr *m_pXFileMngr;
	
	CString m_strXFilePostFix;
	CString m_strXFileFilter;

	CXFileOptrMsgRcvWnd *m_pXFileMsgRcvWnd;
	BOOL m_bDeleteAllFolder;

protected:
	void FreeFilterTextMngr();

protected:
	afx_msg void OnNMDblclkTreeFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateFolderAdd(CCmdUI* pCmdUI);
	afx_msg void OnFolderAdd();
	afx_msg void OnUpdateFolderDelete(CCmdUI* pCmdUI);
	afx_msg void OnFolderDelete();
	afx_msg void OnUpdateFolderEdit(CCmdUI* pCmdUI);
	afx_msg void OnFolderEdit();
	afx_msg void OnUpdateFolderExport(CCmdUI* pCmdUI);
	afx_msg void OnFolderExport();
	afx_msg void OnUpdateFolderImport(CCmdUI* pCmdUI);
	afx_msg void OnFolderImport();
	afx_msg void OnUpdateFileCopy(CCmdUI* pCmdUI);
	afx_msg void OnFileCopy();
	afx_msg void OnUpdateFilePaste(CCmdUI* pCmdUI);
	afx_msg void OnFilePaste();
	afx_msg void OnUpdateFileDelete(CCmdUI* pCmdUI);
	afx_msg void OnFileDelete();
	afx_msg void OnUpdateFileEdit(CCmdUI* pCmdUI);
	afx_msg void OnFileEdit();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileImport(CCmdUI* pCmdUI);
	afx_msg void OnFileImport();
	afx_msg void OnUpdateFileDownload(CCmdUI* pCmdUI);
	afx_msg void OnFileDownload();
	afx_msg void OnUpdateFileUpload(CCmdUI* pCmdUI);
	afx_msg void OnFileUpload();
	afx_msg void OnTvnSelchangedXFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileFilter();
	afx_msg void OnUpdateFileFilter(CCmdUI* pCmdUI);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	afx_msg LRESULT OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnXFileMngrSelChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


