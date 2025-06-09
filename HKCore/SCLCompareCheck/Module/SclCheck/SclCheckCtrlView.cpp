// SclCheckCtrlView.cpp : 实现文件
//

#include "stdafx.h"
//#include "SCLCompareCheckDev.h"
#include "SclCheckCtrlView.h"


// CSclCheckCtrlView

IMPLEMENT_DYNCREATE(CSclCheckCtrlView, CFormView)

CSclCheckCtrlView::CSclCheckCtrlView()
	: CFormView(CSclCheckCtrlView::IDD)
{

}

CSclCheckCtrlView::~CSclCheckCtrlView()
{
}

void CSclCheckCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSclCheckCtrlView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSclCheckCtrlView 诊断

#ifdef _DEBUG
void CSclCheckCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSclCheckCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSclCheckCtrlView 消息处理程序

void CSclCheckCtrlView::ShowGridDatas(CExBaseList *pDatas )
{
	if (pDatas == NULL)
	{
		m_oSclCheckCtrlGrid.SetRowCount(1);
		m_oSclCheckCtrlGrid.Invalidate(FALSE);
		return ;
	}

	m_oSclCheckCtrlGrid.AttachDatas(pDatas);

	m_oSclCheckCtrlGrid.InitGridTitle();

	m_oSclCheckCtrlGrid.ShowDatas(pDatas);
	m_oSclCheckCtrlGrid.SelectRow(1);
	m_oSclCheckCtrlGrid.SetEditable(FALSE);
//	m_oSclCheckCtrlGrid.Invalidate(TRUE);
}

void CSclCheckCtrlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CRect rcGrid;
	GetClientRect(&rcGrid);

	m_oSclCheckCtrlGrid.Create(rcGrid, this, IDC_GRID_SCLCHECK_CTRL);
	m_oSclCheckCtrlGrid.SetFont(g_pGlobalFont11);
	m_oSclCheckCtrlGrid.InitGrid();
}

void CSclCheckCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!::IsWindow(m_oSclCheckCtrlGrid.m_hWnd))
	{
		return;
	}

	CRect rc(IECCFG_CTRL_GAP, IECCFG_CTRL_GAP, cx - 2*IECCFG_CTRL_GAP, cy - 2*IECCFG_CTRL_GAP);
	m_oSclCheckCtrlGrid.MoveWindow(rc);
}

BOOL CSclCheckCtrlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
