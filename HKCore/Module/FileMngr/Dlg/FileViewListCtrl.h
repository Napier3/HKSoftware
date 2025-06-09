#pragma once

#include "../FolderBase.h"
#include "FolderViewTreeCtrl.h"
// CFileViewListCtrl

#define ID_GBDEV_DELETE_FILES			4001
#define ID_GBDEV_RENAME_FILES			4002

class CFileViewListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CFileViewListCtrl)

public:
	CFileViewListCtrl();
	virtual ~CFileViewListCtrl();

protected:
	CFolderViewTreeCtrl* m_pFolderTree;
	CFolderBase* m_pFolderBase;
	BOOL m_bFirstShow;
	CString m_strFilter;
	CFileMngrBase* m_pFileMngrBase;

	virtual void InsertItemToListCtrl(CExBaseObject* pObj);
	void OnContextMenuEx(CWnd* pWnd, CPoint point);

public:
	void SetFilter(const CString& strFilter)										{		m_strFilter = strFilter;									}
	void SetFileMngrBase(CFileMngrBase* pFileMngr)				{		m_pFileMngrBase = pFileMngr;				}
	void RefreshFileViewList();
	void SetRelatedFolderTreeCtrl(CFolderViewTreeCtrl* pFolderTree);
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);
	HTREEITEM FindTreeItem(int nItem);
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnRename();
	afx_msg void OnDelete();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
};