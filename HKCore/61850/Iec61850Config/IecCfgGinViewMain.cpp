#include "StdAfx.h"
#include "IecCfgGinViewMain.h"

CIecCfgGinViewMain::CIecCfgGinViewMain(void)
{
}

CIecCfgGinViewMain::~CIecCfgGinViewMain(void)
{
}

void CIecCfgGinViewMain::CreateViews(const CRect &rect, CCreateContext *pContext)
{
	m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CIecCfgGinDataView),
		CSize(rect.Width()/4,rect.Height()),
		pContext);

	m_wndSplitter.CreateView(1,0,
		RUNTIME_CLASS(CIecCfgGinDataChsView),
		CSize(1,1),
		pContext);

	CIecCfgGinDataView *pView = (CIecCfgGinDataView*)m_wndSplitter.GetPane(0, 0);
	pView->m_pChsView = (CIecCfgGinDataChsView*)m_wndSplitter.GetPane(1, 0);
}

