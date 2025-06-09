// XFileMngrFolderView.cpp : 实现文件
//

#include "stdafx.h"
// #include "StationTestMain.h"
#include "XFileMngrFolderView.h"
#include "XFileMngrFrame.h"


// CXFileMngrFolderView

IMPLEMENT_DYNCREATE(CXFileMngrFolderView, CView)

CXFileMngrFolderView::CXFileMngrFolderView()
{

}

CXFileMngrFolderView::~CXFileMngrFolderView()
{
}

void CXFileMngrFolderView::AttachXFileListView(CXFileListView *pXFileListView, CWnd *pFrameWnd)
{
	m_folderTree.AttacthXFileListView(pXFileListView);
	m_folderTree.SetFrameWnd(pFrameWnd);
}

void CXFileMngrFolderView::ShowXFileMngr(CXFileMngr *pXFileMngr)
{
	m_folderTree.ShowXFileMngr(pXFileMngr);
}

BEGIN_MESSAGE_MAP(CXFileMngrFolderView, CView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CXFileMngrFolderView 绘图

void CXFileMngrFolderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CXFileMngrFolderView 诊断

#ifdef _DEBUG
void CXFileMngrFolderView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CXFileMngrFolderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXFileMngrFolderView 消息处理程序

void CXFileMngrFolderView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rcClient;
	GetClientRect(&rcClient);

	DWORD dwStyle = (/*WS_BORDER |*/ WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS);
	m_folderTree.Create(dwStyle, rcClient, this, XFIDC_TREE_FOLDER);

	xfile_LoadFileMngrBmp(&m_oImageList);

	if (m_oImageList.ValidImageList())
	{
		m_folderTree.SetImageList(&m_oImageList, TVSIL_NORMAL);
	}
}

void CXFileMngrFolderView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CXFileMngr *pXFileMngr = (CXFileMngr*)lHint;

	if (pXFileMngr == NULL)
	{
		return;
	}

	//m_folderTree.ShowXFileMngr(pXFileMngr);
	
}

void CXFileMngrFolderView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_folderTree.m_hWnd))
	{
		return;
	}

	m_folderTree.MoveWindow(0,0, cx, cy);
}
