#pragma once

#include "..\..\Module\XfileMngrBase\XFolderTreeCtrl.h"
#include "..\..\Module\XfileMngrBase\XFileListView.h"
#include "..\..\Module\XfileMngrBase\XFileMngr.h"

// CXFileMngrListView 视图

class CXFileMngrListView : public CView
{
	DECLARE_DYNCREATE(CXFileMngrListView)

public:
	void AttatchXFolderTreeCtrl(CXFolderTreeCtrl *pXFolderTreeCtrl, CWnd *pFrameWnd);
	CXFileListView* GetXFileListView()	{	return &m_fileListCtrl;	}

protected:
	CXFileMngrListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CXFileMngrListView();
	CXFileListView m_fileListCtrl;
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
	HRESULT OnUploadFile(WPARAM wParam, LPARAM lParam);
};


