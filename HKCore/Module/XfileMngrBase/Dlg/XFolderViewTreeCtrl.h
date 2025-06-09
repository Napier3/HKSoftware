#pragma once


// CXFolderViewTreeCtrl

#include "../XFileMngr.h"

#define ID_GBDEV_NEW_FOLDER 3001
#define ID_GBDEV_DELETE_FOLDER 3002
#define ID_GBDEV_RENAME_FOLDER 3003

#define WM_CHANGE_STATIC_PATH       (WM_USER + 5101)
#define WM_THREAD_DLG_XFILEMNGR		(WM_USER + 5102)
#define WM_PARENT_SAVE_XFILE		(WM_USER + 5103)
#define WM_PARENT_OPEN_XFILE		(WM_USER + 5104)


class CXFileViewListCtrl;

class CXFolderViewTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CXFolderViewTreeCtrl)

public:
	CXFolderViewTreeCtrl();
	virtual ~CXFolderViewTreeCtrl();

protected:
	CXFileMngr* m_pFileMngrBase;
	CXFileViewListCtrl* m_pFileList;

	virtual void InsertItemToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent);
	virtual void InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent);
	void OnContextMenuEx(CWnd* pWnd, CPoint point);			//�����Ҽ��˵�

public:
	void SetFileMngr(CXFileMngr* pFileMngrBase)				{		m_pFileMngrBase = pFileMngrBase;		}
	CXFileMngr* GetFileMngrBase()												{		return m_pFileMngrBase;							}
	void InitShowFolderViewTree();
	void SetRelatedListCtrl(CXFileViewListCtrl* pFileList);

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


