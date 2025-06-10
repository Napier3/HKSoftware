// SclFileDetailView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileDetailView.h"
#include "SclFileCtrlView.h"
#include "SclFileTreeView.h"


// CSclFileDetailView
IMPLEMENT_DYNCREATE(CSclFileDetailView, CView)

CSclFileDetailView::CSclFileDetailView(void)
{
	m_pSclFileTreeView = NULL;
}

CSclFileDetailView::~CSclFileDetailView(void)
{

}



void CSclFileDetailView::CreateViews(const CRect &rect, CCreateContext *pContext)
{
	m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CSclFileCtrlView),
		CSize(rect.Width()/4,rect.Height()),
		pContext);

	m_wndSplitter.CreateView(1,0,
		RUNTIME_CLASS(CSclFileCtrlChsView),
		CSize(1,1),
		pContext);

	CSclFileCtrlView *pView = (CSclFileCtrlView*)m_wndSplitter.GetPane(0, 0);
	pView->m_pSclFileTreeView = m_pSclFileTreeView;
	pView->m_pChsView = (CSclFileCtrlChsView*)m_wndSplitter.GetPane(1, 0);

	int cyCurr, cyMin;
	m_wndSplitter.GetRowInfo(0, cyCurr, cyMin);
	cyMin = pView->m_cyMin;

	if (cyCurr < 0)
	{
		cyCurr = 200;
	}

	m_wndSplitter.SetRowInfo(0, cyCurr, cyMin);
}

void CSclFileDetailView::InitViews()
{
	CSclFileCtrlView *pView = (CSclFileCtrlView*)m_wndSplitter.GetPane(0, 0);
	ASSERT(m_pSclFileTreeView != NULL);
	m_pSclFileTreeView->m_pSclFileCtrlView = pView;
}

void CSclFileDetailView::AttachSclFileTreeView(CView *pSclFileTreeView)
{
	m_pSclFileTreeView = (CSclFileTreeView*)pSclFileTreeView;
	CSclFileCtrlView *pView = (CSclFileCtrlView*)m_wndSplitter.GetPane(0, 0);

	if (pView != NULL)
	{
		pView->m_pSclFileTreeView = m_pSclFileTreeView;
	}
}

CSclFileCtrlView* CSclFileDetailView::GetSclFileCtrlView()
{
	return (CSclFileCtrlView*)m_wndSplitter.GetPane(0, 0);
}

// 
// IMPLEMENT_DYNCREATE(CSclFileDetailView, CView)
// 
// CSclFileDetailView::CSclFileDetailView()
// {
// 
// }
// 
// CSclFileDetailView::~CSclFileDetailView()
// {
// }
// 
// BEGIN_MESSAGE_MAP(CSclFileDetailView, CView)
// 	ON_WM_CREATE()
// 	ON_WM_SIZE()
// END_MESSAGE_MAP()
// 
// 
// // CSclFileDetailView ��ͼ
// 
// void CSclFileDetailView::OnDraw(CDC* pDC)
// {
// 	CDocument* pDoc = GetDocument();
// 	// TODO: �ڴ���ӻ��ƴ���
// }
// 
// 
// // CSclFileDetailView ���
// 
// #ifdef _DEBUG
// void CSclFileDetailView::AssertValid() const
// {
// 	CView::AssertValid();
// }
// 
// #ifndef _WIN32_WCE
// void CSclFileDetailView::Dump(CDumpContext& dc) const
// {
// 	CView::Dump(dc);
// }
// #endif
// #endif //_DEBUG
// 
// 
// // CSclFileDetailView ��Ϣ�������
// 
// int CSclFileDetailView::OnCreate(LPCREATESTRUCT lpCreateStruct)
// {
// 	if (CView::OnCreate(lpCreateStruct) == -1)
// 		return -1;
// 
// 	CRect rect;
// 	GetClientRect(&rect);
// 
// 	//��ô��ڵĴ�����Ϣָ��
// 	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
// 
// 	//�������ξ�̬�з�
// 	m_wndSplitter.CreateStatic(this, 2, 1);
// 
// 	m_wndSplitter.CreateView(0,0,
// 		RUNTIME_CLASS(CSclFileCtrlView),
// 		CSize(rect.Width()/4,rect.Height()),
// 		pContext);
// 
// 	m_wndSplitter.CreateView(1,0,
// 		RUNTIME_CLASS(CSclFileCtrlChsView),
// 		CSize(1,1),
// 		pContext);
// 
// 	CSclFileCtrlView *pView = (CSclFileCtrlView*)m_wndSplitter.GetPane(0, 0);
// 	pView->m_pChsView = (CSclFileCtrlChsView*)m_wndSplitter.GetPane(1, 0);
// 
// 	return 0;
// }
// 
// void CSclFileDetailView::OnSize(UINT nType, int cx, int cy)
// {
// 	CView::OnSize(nType, cx, cy);
// 
// 	// TODO: �ڴ˴������Ϣ����������
// }
