// IecCfgDataViewBase.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgDataChsViewBase.h"

// CIecCfgDataViewBase

CIecCfgDataChsViewBase::CIecCfgDataChsViewBase(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{
	m_pIecCfgDataChsGrid = NULL;
	m_pIecCfgData = NULL;
	m_pIecCfgFile = NULL;
}

CIecCfgDataChsViewBase::~CIecCfgDataChsViewBase()
{
	FreeGrid();
}

void CIecCfgDataChsViewBase::InitView(CIecCfgDataChsGridBase *pIecCfgDataChsGrid)
{
	
}

void CIecCfgDataChsViewBase::AdjustSize(int cx, int cy)
{
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
			rc.right = cx - 5;
			rc.top = m_nGridTop;
			rc.bottom = cy - 5;
			m_pIecCfgDataChsGrid->MoveWindow(rc, TRUE);
		}
	}
}

void CIecCfgDataChsViewBase::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CIecCfgFile *pFile = (CIecCfgFile*)lHint;
	m_pIecCfgFile = pFile;

}

void CIecCfgDataChsViewBase::FreeGrid(CRect &rcGrid)
{
	if (m_pIecCfgDataChsGrid != NULL)
	{
		m_pIecCfgDataChsGrid->GetWindowRect(&rcGrid);
		ScreenToClient(&rcGrid);
	}

	FreeGrid();
}

void CIecCfgDataChsViewBase::UpdateGrid(BOOL bInitTile)
{
	if (m_pIecCfgDataChsGrid == NULL || m_pIecCfgData == NULL)
	{
		return;
	}

	if (bInitTile)
	{
		m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());
		m_pIecCfgDataChsGrid->InitGrid();
		m_pIecCfgDataChsGrid->UpdateDatas();
	} 
	else
	{
		m_pIecCfgDataChsGrid->UpdateDatas();
	}
}

void CIecCfgDataChsViewBase::FreeGrid()
{
	if (m_pIecCfgDataChsGrid != NULL)
	{
		m_pIecCfgDataChsGrid->DestroyWindow();
		delete m_pIecCfgDataChsGrid;
		m_pIecCfgDataChsGrid = NULL;
	}
}

void CIecCfgDataChsViewBase::ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData)
{
	if (m_pIecCfgDataChsGrid == NULL )
	{
		return;
	}

	m_pIecCfgData = pIecCfgData;

	if (pIecCfgData == NULL)
	{
		m_pIecCfgDataChsGrid->ShowDatas(NULL);
	}
	else
	{
		m_pIecCfgDataChsGrid->ShowDatas(pIecCfgData->m_pCfgChs);
	}
}

