// IecCfgGinDataChsView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgGinDataChsView.h"
#include "TestEngine.h"

// CIecCfgGinDataChsView

IMPLEMENT_DYNCREATE(CIecCfgGinDataChsView, CFormView)

CIecCfgGinDataChsView::CIecCfgGinDataChsView()
	: CIecCfgDataChsViewBase(CIecCfgGinDataChsView::IDD)
{
	m_nGridTop = 2;
	m_pGinAppChMapGrid = NULL;
	m_pGinDatas = NULL;
}

CIecCfgGinDataChsView::~CIecCfgGinDataChsView()
{
	if (m_pGinAppChMapGrid != NULL)
	{
		delete m_pGinAppChMapGrid;
		m_pGinAppChMapGrid = NULL;
	}
}

void CIecCfgGinDataChsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIecCfgGinDataChsView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_GET_CURR_SEL_GIN_CH, OnGetCurrSelGinCh)
	ON_MESSAGE(WM_UPDATE_GIN_CH,       OnUpdateGinCh)
	ON_MESSAGE(WM_GIN_CH_APPID_CHANGED,OnGinChAppIDChanged)
END_MESSAGE_MAP()


// CIecCfgGinDataChsView 诊断

#ifdef _DEBUG
void CIecCfgGinDataChsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgGinDataChsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgGinDataChsView 消息处理程序

void CIecCfgGinDataChsView::CreateChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CRect rc;
	GetClientRect(&rc);
	rc.left = 5;
	rc.right -= 5;
	rc.top = m_nGridTop;
	rc.bottom -=  5;

	if (m_pGinAppChMapGrid == NULL)
	{
		m_pGinAppChMapGrid = new CIecCfgGinAppChMapGrid();
		m_pGinAppChMapGrid->Create(rc, this, IDC_GRID_IECCFG_DATACHS_BASE);
		m_pGinAppChMapGrid->SetFont(g_pGlobalFont11);
		m_pGinAppChMapGrid->InitGrid();
	}
	
	if (m_pIecCfgDataChsGrid != NULL)
	{
		return;
	}


// 	FreeGrid(rc);

	m_pIecCfgDataChsGrid = new CIecCfgGinDataChsGrid(g_nEngineDispMode == _DISP_MODE_PNI302);
	m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());

	m_pIecCfgDataChsGrid->Create(rc, this, IDC_GRID_IECCFG_DATACHS_BASE);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}


void CIecCfgGinDataChsView::OnInitialUpdate()
{
	CIecCfgDataChsViewBase::OnInitialUpdate();

	//CreateGrid();
}

void CIecCfgGinDataChsView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataChsViewBase::OnSize(nType, cx, cy);


	if (cy < IDC_IECCFG_DATACHSVIEW_CY_MIN)
	{
		cy = IDC_IECCFG_DATACHSVIEW_CY_MIN;
	}

	CRect rc;

	if (m_pIecCfgDataChsGrid != NULL)
	{
		if (::IsWindow(m_pIecCfgDataChsGrid->m_hWnd))
		{
			rc.left = 5;
			rc.right = cx / 2 - 5;
			rc.top = m_nGridTop;
			rc.bottom = cy - 5;
			m_pIecCfgDataChsGrid->MoveWindow(rc, TRUE);
		}
	}

	if (m_pGinAppChMapGrid != NULL)
	{
		if (::IsWindow(m_pGinAppChMapGrid->m_hWnd))
		{
			rc.left = rc.right + 5;
			rc.right = cx - 5;
			rc.top = m_nGridTop;
			rc.bottom = cy - 5;
			m_pGinAppChMapGrid->MoveWindow(rc, TRUE);
		}
	}
}

void CIecCfgGinDataChsView::ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData)
{
	CIecCfgDataChsViewBase::ShowIecCfgDataChs(pIecCfgData);

	if (m_pGinDatas != NULL)
	{
		return;
	}

	if (pIecCfgData == NULL)
	{
		return;
	}

	m_pGinDatas = (CIecCfgGinDatas *)pIecCfgData->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	m_pGinAppChMapGrid->ShowDatas(m_pGinDatas->GetIecCfgGinAppChMaps());
}

void CIecCfgGinDataChsView::ShowIecCfgGinAppMaps()
{
	if (m_pGinDatas == NULL)
	{
		return;
	}

	m_pGinAppChMapGrid->ShowDatas(m_pGinDatas->GetIecCfgGinAppChMaps());
}

LRESULT CIecCfgGinDataChsView::OnGetCurrSelGinCh(WPARAM wParam, LPARAM lParam)
{
	if (m_pIecCfgDataChsGrid == NULL)
	{
		return NULL;
	}

	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)m_pIecCfgDataChsGrid->GetCurrSelData(1);

	if (pGinCh == NULL)
	{
		return NULL;
	}

	ASSERT (pGinCh->GetClassID() == CFGCLASSID_CIECCFGGINCH);
	return (LRESULT)pGinCh;
}


LRESULT CIecCfgGinDataChsView::OnUpdateGinCh(WPARAM wParam, LPARAM lParam)
{
	if (m_pIecCfgDataChsGrid == NULL)
	{
		return NULL;
	}

	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)wParam;
	ASSERT (pGinCh != NULL);

	if (pGinCh == NULL)
	{
		return 0;
	}

	CIecCfgGinData *pGinData = (CIecCfgGinData*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGGINDATA);
	
	if (pGinData != m_pIecCfgData)
	{
		return 0;
	}

	int nRow = pGinData->m_pCfgChs->FindIndex(pGinCh);
	ASSERT (nRow >= 0);
	nRow++;
	m_pIecCfgDataChsGrid->ShowData(pGinCh, nRow, FALSE);

	if (CIecCfgTool::IsViewChsPath())
	{
		m_pIecCfgDataChsGrid->AutoSizeColumn(IECCFG_COL_ID_GINCH_APPCH);
	}
	else
	{
		m_pIecCfgDataChsGrid->AutoSizeColumn(IECCFG_COL_ID_GINCH_APPCH-1);
	}

	m_pIecCfgDataChsGrid->Invalidate(FALSE);

	return 0;
}

LRESULT CIecCfgGinDataChsView::OnGinChAppIDChanged(WPARAM wParam, LPARAM lParam)
{
	m_pGinDatas = (CIecCfgGinDatas *)m_pIecCfgData->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);

	m_pGinDatas->InitGinAppChMaps();
	m_pGinAppChMapGrid->ShowDatas(m_pGinDatas->GetIecCfgGinAppChMaps());

	return 0;
}

