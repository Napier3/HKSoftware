#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "..\..\Module\XfileMngrBase\XFileMngr.h"

// 带有拆分器的 CXFileMngrFrameEx 框架
class CXFileMngrListView;
class CXFileMngrFolderView;

class CXFileMngrFrameEx : public CMDIChildWndEx//, public CXFileMngrOptrInterface
{
	DECLARE_DYNCREATE(CXFileMngrFrameEx)

public:
	CString   m_strDocID;
	CDocument *m_pXFileMngrDoc;

	CXFileMngrListView   *m_pXFileMngrListView;
	CXFileMngrListView   *m_pXFileMngrListView_Remote;
	CXFileMngrFolderView *m_pXFileMngrFolderView;

	void ShowXFileMngr(CXFileMngr *pXFileMngr);
	void SetFramwWnd(CWnd *pFrameWnd);

protected:
	CXFileMngrFrameEx();           // 动态创建所使用的受保护的构造函数
	virtual ~CXFileMngrFrameEx();

	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter_Right;
	void ExecXFile(CXFile *pFile);

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};


CXFileMngrFrameEx* UI_GetCXFileMngrFrameEx(CView *pView);

