#pragma once

#include "..\..\Module\XfileMngrBase\XFolderTreeCtrl.h"
#include "..\..\Module\XfileMngrBase\XFileListView.h"
#include "..\..\Module\XfileMngrBase\XFileMngr.h"
// CXFileMngrFolderView 视图

class CXFileMngrFolderView : public CView
{
	DECLARE_DYNCREATE(CXFileMngrFolderView)

public:
	void AttachXFileListView(CXFileListView *pXFileListView, CWnd *pFrameWnd);
	CXFolderTreeCtrl* GetXFolderTreeCtrl()	{	return &m_folderTree;	}
	void ShowXFileMngr(CXFileMngr *pXFileMngr);

protected:
	CXFileMngrFolderView();           // 动态创建所使用的受保护的构造函数
	virtual ~CXFileMngrFolderView();
	CXFolderTreeCtrl m_folderTree;
	CBmpImageList m_oImageList;

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


