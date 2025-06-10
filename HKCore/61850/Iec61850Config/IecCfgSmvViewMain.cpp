#include "StdAfx.h"
#include "IecCfgSmvViewMain.h"

CIecCfgSmvViewMain::CIecCfgSmvViewMain(void)
{
}

CIecCfgSmvViewMain::~CIecCfgSmvViewMain(void)
{
	
}



void CIecCfgSmvViewMain::CreateViews(const CRect &rect, CCreateContext *pContext)
{
	m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CIecCfgSmvDataView),
		CSize(rect.Width()/4,rect.Height()),
		pContext);

	m_wndSplitter.CreateView(1,0,
		RUNTIME_CLASS(CIecCfgSmvDataChsView),
		CSize(1,1),
		pContext);

	CIecCfgSmvDataView *pView = (CIecCfgSmvDataView*)m_wndSplitter.GetPane(0, 0);
	pView->m_pChsView = (CIecCfgSmvDataChsView*)m_wndSplitter.GetPane(1, 0);
}

