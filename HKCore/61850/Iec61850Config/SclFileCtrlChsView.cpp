// SclFileCtrlChsView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileCtrlChsView.h"


// CSclFileCtrlChsView

IMPLEMENT_DYNCREATE(CSclFileCtrlChsView, CFormView)

CSclFileCtrlChsView::CSclFileCtrlChsView()
	: CFormView(CSclFileCtrlChsView::IDD)
{

}

CSclFileCtrlChsView::~CSclFileCtrlChsView()
{
}

void CSclFileCtrlChsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSclFileCtrlChsView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSclFileCtrlChsView 诊断

#ifdef _DEBUG
void CSclFileCtrlChsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSclFileCtrlChsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSclFileCtrlChsView 消息处理程序

void CSclFileCtrlChsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CRect rcGrid;
	GetClientRect(&rcGrid);

	rcGrid.top = 5;
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.bottom -= 5;

	m_oCSclIecCfgCtrlChnGrid.Create(rcGrid, this, IDC_GRID_SCLIECCFG_CHN);
	m_oCSclIecCfgCtrlChnGrid.SetFont(g_pGlobalFont11);
	m_oCSclIecCfgCtrlChnGrid.InitGrid();
}

void CSclFileCtrlChsView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_oCSclIecCfgCtrlChnGrid.m_hWnd))
	{
		return;
	}

	m_oCSclIecCfgCtrlChnGrid.MoveWindow(0, 0, cx, cy);
}

void CSclFileCtrlChsView::ShowDatas(CExBaseList *pDatas)
{
	if (pDatas == NULL)
	{
		m_oCSclIecCfgCtrlChnGrid.SetRowCount(1);
		return;
	}

	m_oCSclIecCfgCtrlChnGrid.AttachDatas(pDatas);
	m_oCSclIecCfgCtrlChnGrid.InitGridTitle();
	m_oCSclIecCfgCtrlChnGrid.ShowDatas(pDatas);
}


//////////////////////////////////////////////////////////////////////////
//外部操作
void CSclFileCtrlChsView::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (nRow <= 0 || nCol <= 0)
	{
		return;
	}

	PEXBASECELLDATA pVellData = (EXBASECELLDATA*)pGridCtrl->GetItemData(nRow, nCol);

	if (pVellData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  表格没有关联数据对象"), nRow, nCol);
		return;
	}

	ASSERT (pVellData->pObj != NULL);

	CExBaseList *pDatas = (CExBaseList*)pVellData->pObj;

	if (pDatas == NULL )
	{
		return;
	}

	ShowDatas(pDatas);
}
