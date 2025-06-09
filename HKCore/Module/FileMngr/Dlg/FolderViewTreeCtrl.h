#pragma once


// CFolderViewTreeCtrl

#include "../FileMngrBase.h"

#define ID_GBDEV_NEW_FOLDER 3001
#define ID_GBDEV_DELETE_FOLDER 3002
#define ID_GBDEV_RENAME_FOLDER 3003

#define WM_CHANGE_STATIC_PATH WM_USER + 5001

class CFileViewListCtrl;

class CFolderViewTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CFolderViewTreeCtrl)

public:
	CFolderViewTreeCtrl();
	virtual ~CFolderViewTreeCtrl();

protected:
	CFileMngrBase* m_pFileMngrBase;
	CFileViewListCtrl* m_pFileList;

	virtual void InsertItemToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent);
	virtual void InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent);
	void OnContextMenuEx(CWnd* pWnd, CPoint point);			//µ¯³öÓÒ¼ü²Ëµ¥

public:
	void SetFileMngr(CFileMngrBase* pFileMngrBase)				{		m_pFileMngrBase = pFileMngrBase;		}
	CFileMngrBase* GetFileMngrBase()												{		return m_pFileMngrBase;							}
	void InitShowFolderViewTree();
	void SetRelatedListCtrl(CFileViewListCtrl* pFileList);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewFolder();
	afx_msg void OnDeleteFolder();
	afx_msg void OnRenameFolder();

	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
};


