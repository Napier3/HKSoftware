// XFileMngrListView.cpp : 实现文件
//

#include "stdafx.h"
// #include "StationTestMain.h"
#include "XFileMngrListView.h"
#include "XFileMngrFrame.h"

// CXFileMngrListView

IMPLEMENT_DYNCREATE(CXFileMngrListView, CView)

CXFileMngrListView::CXFileMngrListView()
{

}

CXFileMngrListView::~CXFileMngrListView()
{
}

void CXFileMngrListView::AttatchXFolderTreeCtrl(CXFolderTreeCtrl *pXFolderTreeCtrl, CWnd *pFrameWnd)
{
	m_fileListCtrl.SetRelatedFolderTreeCtrl(pXFolderTreeCtrl);
	m_fileListCtrl.SetFrameWnd(pFrameWnd);
}

BEGIN_MESSAGE_MAP(CXFileMngrListView, CView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER+1011, OnUploadFile)
END_MESSAGE_MAP()

HRESULT CXFileMngrListView::OnUploadFile(WPARAM wParam, LPARAM lParam)
{
	AfxGetMainWnd()->PostMessage(WM_USER+1011, wParam, lParam);
	return 0;
}

// CXFileMngrListView 绘图

void CXFileMngrListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CXFileMngrListView 诊断

#ifdef _DEBUG
void CXFileMngrListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CXFileMngrListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXFileMngrListView 消息处理程序

void CXFileMngrListView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rcClient;
	GetClientRect(&rcClient);

	DWORD dwStyle = (WS_VISIBLE | WS_CHILD | WS_TABSTOP | /*WS_BORDER |*/ LVS_REPORT | LVS_SHOWSELALWAYS);
	//m_fileListCtrl.SetUseYun(pXFileMngr->)
	
	if (m_fileListCtrl.Create(dwStyle, rcClient, this, XFIDC_LIST_FILE))
	{
		m_fileListCtrl.ModifyStyle(0L,LVS_NOSORTHEADER|LVS_SINGLESEL);
		m_fileListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	}

	xfile_LoadFileMngrBmp(&m_oImageList);

	if (m_oImageList.ValidImageList())
	{
		m_fileListCtrl.SetImageList(&m_oImageList,LVSIL_SMALL);
	}
}

void CXFileMngrListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CXFileMngr *pXFileMngr = (CXFileMngr*)lHint;
	
	if (pXFileMngr == NULL)
	{
		return;
	}

	m_fileListCtrl.SetXFileMngr(pXFileMngr);
	m_fileListCtrl.SetFrameWnd(this);
}

void CXFileMngrListView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_fileListCtrl.m_hWnd))
	{
		return;
	}

	m_fileListCtrl.MoveWindow(0,0, cx, cy);
}
