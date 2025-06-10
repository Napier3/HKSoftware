#include "StdAfx.h"
#include "IecCfgGoutViewMain.h"

CIecCfgGoutViewMain::CIecCfgGoutViewMain(void)
{
}

CIecCfgGoutViewMain::~CIecCfgGoutViewMain(void)
{
}


void CIecCfgGoutViewMain::CreateViews(const CRect &rect, CCreateContext *pContext)
{
	m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CIecCfgGoutDataView),
		CSize(rect.Width()/4,rect.Height()),
		pContext);

	m_wndSplitter.CreateView(1,0,
		RUNTIME_CLASS(CIecCfgGoutDataChsView),
		CSize(1,1),
		pContext);


	CIecCfgGoutDataView *pView = (CIecCfgGoutDataView*)m_wndSplitter.GetPane(0, 0);
	pView->m_pChsView = (CIecCfgGoutDataChsView*)m_wndSplitter.GetPane(1, 0);
}

