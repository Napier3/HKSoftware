#pragma once

#include "XFileMngr.h"
#include "XFolderTreeCtrl.h"
// CXFileListView

#define ID_GBDEV_DELETE_FILES			4001
#define ID_GBDEV_RENAME_FILES			4002

class CXFileListView : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CXFileListView)

public:
	CXFileListView();
	virtual ~CXFileListView();

protected:
	CXFolderTreeCtrl* m_pFolderTree;
	CXFolder* m_pXFolder;
	BOOL m_bFirstShow;
	CString m_strFilter;
	CXFileMngr* m_pXFileMngr;
	BOOL m_bDeleteAllFolder;
	long m_nCurrSelIndex;
	CWnd *m_pFrameWnd;
	BOOL m_bUseYun;

	virtual void InsertItemToListCtrl(CExBaseObject* pObj);
	virtual void UpdateItemToListCtrl(CExBaseObject* pObj, long nItem);
	void OnContextMenuEx(CWnd* pWnd, CPoint point);
	void OnSelectXFileChanged(long nItemIndex);

public:
	BOOL IsUseYun()	{	return m_bUseYun;	}
	void SetUseYun(BOOL b)	{	m_bUseYun = b;	}

	void SetFilter(const CString& strFilter)										{		m_strFilter = strFilter;									}
	void SetXFileMngr(CXFileMngr* pFileMngr)				{		m_pXFileMngr = pFileMngr;		m_bUseYun = pFileMngr->IsYunFolder();		}
	void RefreshFileViewList();
	void SetRelatedFolderTreeCtrl(CXFolderTreeCtrl* pFolderTree);
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);
	HTREEITEM FindTreeItem(int nItem);
	void SetFrameWnd(CWnd *pFrameWnd)									{		m_pFrameWnd = pFrameWnd;	}
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnRename();
	afx_msg void OnDelete();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
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
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPublishFileAdd();
	afx_msg void OnUpdatePublishFileAdd(CCmdUI* pCmdUI);
};