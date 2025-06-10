// IecCfgGoutDataChsView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgGoutDataChsView.h"
#include "TestEngine.h"


// CIecCfgGoutDataChsView

IMPLEMENT_DYNCREATE(CIecCfgGoutDataChsView, CFormView)

CIecCfgGoutDataChsView::CIecCfgGoutDataChsView()
	: CIecCfgDataChsViewBase(CIecCfgGoutDataChsView::IDD)
{
	m_nGridTop = 2;
}

CIecCfgGoutDataChsView::~CIecCfgGoutDataChsView()
{
}

void CIecCfgGoutDataChsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIecCfgGoutDataChsView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CIecCfgGoutDataChsView 诊断

#ifdef _DEBUG
void CIecCfgGoutDataChsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgGoutDataChsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgGoutDataChsView 消息处理程序


void CIecCfgGoutDataChsView::CreateChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	if (m_pIecCfgDataChsGrid != NULL)
	{
		return;
	}

	CRect rc;
	GetClientRect(&rc);
	rc.left = 5;
	rc.right -= 5;
	rc.top = m_nGridTop;
	rc.bottom -=  5;

	//FreeGrid(rc);

	m_pIecCfgDataChsGrid = new CIecCfgGoutDataChsGrid(g_nEngineDispMode == _DISP_MODE_PNI302);
	m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());

	m_pIecCfgDataChsGrid->Create(rc, this, IDC_GRID_IECCFG_DATACHS_BASE);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}


void CIecCfgGoutDataChsView::OnInitialUpdate()
{
	CIecCfgDataChsViewBase::OnInitialUpdate();

	//CreateGrid();
}

void CIecCfgGoutDataChsView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataChsViewBase::OnSize(nType, cx, cy);

	AdjustSize(cx, cy);
}
