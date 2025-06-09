#pragma once

#define  WM_CHANGE_STATIC_XPATH   (WM_USER + 3019)
#include "XFileMngr.h"
// CXFolderTreeCtrl

class CXFileListView;

class CXFolderTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CXFolderTreeCtrl)

public:
	CXFolderTreeCtrl();
	virtual ~CXFolderTreeCtrl();
	void AttacthXFileListView(CXFileListView *pListView)	{	m_pXFileListView = pListView;	}

protected:
	CWnd *m_pFrameWnd;
	CXFileMngr *m_pXFileMngr;
	BOOL m_bSetExBaseItemData;
	CXFileListView *m_pXFileListView;
	BOOL m_bDeleteAllFolder;
	CXFileOptrMsgRcvWnd *m_pXFileMsgRcvWnd;

public:
	void SetDeleteAllFolder(BOOL bDeleteAllFolder)	{	m_bDeleteAllFolder = bDeleteAllFolder;	}
	void SetXFileMsgRcvWnd(CXFileOptrMsgRcvWnd *pWnd)	{	m_pXFileMsgRcvWnd = pWnd;	}
	void SetExBaseItemData(BOOL b)	{	m_bSetExBaseItemData = b;	}
	void ShowXFileMngr(CXFileMngr* pXFileMngr);
	void SetFrameWnd(CWnd *pFrameWnd)									{		m_pFrameWnd = pFrameWnd;	}

	CExBaseObject* GetSelObject();
	CXFolder* GetCurrSelFolder();
	void SelectNode(CExBaseObject* pObj);

	virtual BOOL Insert(CExBaseObject *pObj);
	virtual HTREEITEM Delete(CExBaseObject *pObj);
	virtual BOOL Update(CExBaseObject *pObj);

	virtual void InitXFileMngrCurrSel();
	void OnTvnSelchanged(HTREEITEM hItem);

protected:
	HTREEITEM Insert(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter = TVI_LAST);
	virtual void OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pObj);
	virtual void InitContextMenuTree(CMenu &menu,CExBaseObject* pObj);
	UINT GetImgIndex(CExBaseObject* pObj);
	virtual BOOL CanInsert(CExBaseObject* pObj);
	HTREEITEM GetLastFolderItem(HTREEITEM hParent);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMDblclkTreeFile(NMHDR *pNMHDR, LRESULT *pResult);

public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);

public:
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
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};

inline void xfile_PostXFileObjSelChangeMsg(CWnd *pWnd, UINT nMsg, CExBaseObject *pXObj)
{
	if (pWnd == NULL)
	{
		return;
	}

	pWnd->PostMessage(nMsg, (WPARAM)pXObj, (LPARAM)pXObj);
}

inline void xfile_SendXFileObjSelChangeMsg(CWnd *pWnd, UINT nMsg, CExBaseObject *pXObj)
{
	if (pWnd == NULL)
	{
		return;
	}

	pWnd->SendMessage(nMsg, (WPARAM)pXObj, (LPARAM)pXObj);
}