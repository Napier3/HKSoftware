#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "..\..\Module\XfileMngrBase\XFileMngr.h"

// 带有拆分器的 CXFileMngrFrame 框架
class CXFileMngrListView;
class CXFileMngrFolderView;

class CXFileMngrFrame : public CMDIChildWndEx//, public CXFileMngrOptrInterface
{
	DECLARE_DYNCREATE(CXFileMngrFrame)

public:
	CString   m_strDocID;
	CDocument *m_pXFileMngrDoc;

	CXFileMngrListView   *m_pXFileMngrListView;
	CXFileMngrFolderView *m_pXFileMngrFolderView;

	void ShowXFileMngr(CXFileMngr *pXFileMngr);
	void SetFramwWnd(CWnd *pFrameWnd);

protected:
	CXFileMngrFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CXFileMngrFrame();

	CSplitterWnd m_wndSplitter;
	void ExecXFile(CXFile *pFile);

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();

// 	afx_msg LRESULT OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam);
// 
// 	afx_msg void OnUpdateFolderAdd(CCmdUI* pCmdUI);
// 	afx_msg void OnFolderAdd();
// 	afx_msg void OnUpdateFolderDelete(CCmdUI* pCmdUI);
// 	afx_msg void OnFolderDelete();
// 	afx_msg void OnUpdateFolderEdit(CCmdUI* pCmdUI);
// 	afx_msg void OnFolderEdit();
// 	afx_msg void OnUpdateFolderExport(CCmdUI* pCmdUI);
// 	afx_msg void OnFolderExport();
// 	afx_msg void OnUpdateFolderImport(CCmdUI* pCmdUI);
// 	afx_msg void OnFolderImport();
// 	afx_msg void OnUpdateFileCopy(CCmdUI* pCmdUI);
// 	afx_msg void OnFileCopy();
// 	afx_msg void OnUpdateFilePaste(CCmdUI* pCmdUI);
// 	afx_msg void OnFilePaste();
// 	afx_msg void OnUpdateFileDelete(CCmdUI* pCmdUI);
// 	afx_msg void OnFileDelete();
// 	afx_msg void OnUpdateFileEdit(CCmdUI* pCmdUI);
// 	afx_msg void OnFileEdit();
// 	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
// 	afx_msg void OnFileExport();
// 	afx_msg void OnUpdateFileImport(CCmdUI* pCmdUI);
// 	afx_msg void OnFileImport();
};


CXFileMngrFrame* UI_GetCXFileMngrFrame(CView *pView);

