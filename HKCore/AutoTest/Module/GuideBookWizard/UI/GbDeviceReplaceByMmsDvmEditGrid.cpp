#include "StdAfx.h"
#include "GbDeviceReplaceByMmsDvmEditGrid.h"


CGbDeviceReplaceByMmsDvmEditGrid::CGbDeviceReplaceByMmsDvmEditGrid(void)
{
	m_pReplaceDatasets = NULL;
}

CGbDeviceReplaceByMmsDvmEditGrid::~CGbDeviceReplaceByMmsDvmEditGrid(void)
{
	
}


void CGbDeviceReplaceByMmsDvmEditGrid::UpdateMap()
{
	AutoSizeColumn(XMATCH_GRID_ID_DST);
	Invalidate(FALSE);

	CXMatchEditGridCtrlBase::CreateAllDatasDlg();
	AddAllDatasToDlg();
}

void CGbDeviceReplaceByMmsDvmEditGrid::AddAllDatasToDlg(BOOL bShowDlg)
{
	if (m_pAllDatasDlg == NULL)
	{
		return;
	}

	m_pAllDatasDlg->ResetDatasetList();
	CXMatchEditGridCtrlBase::CreateAllDatasDlg();
	POS pos = m_pReplaceDatasets->GetHeadPosition();
	CExBaseList *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CExBaseList *)m_pReplaceDatasets->GetNext(pos);
		m_pAllDatasDlg->AddDataset(pDataset);
	}

	if (bShowDlg)
	{
		m_pAllDatasDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pAllDatasDlg->ShowWindow(SW_HIDE);
	}
}

void CGbDeviceReplaceByMmsDvmEditGrid::ShowAllDatasToDlg()
{
	if (m_pAllDatasDlg == NULL)
	{
		CXMatchEditGridCtrlBase::CreateAllDatasDlg();
		AddAllDatasToDlg();
	}

	if (m_pMatchedDatasDlg != NULL)
	{
		if (m_pMatchedDatasDlg->IsWindowVisible())
		{
			m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
		}
	}

	m_pAllDatasDlg->ShowWindow(SW_SHOW);

	CXMatchObject *pXMatchObj = NULL;
	pXMatchObj = (CXMatchObject*)GetCurrSelData(2);

	if (pXMatchObj == NULL)
	{
		return;
	}

	CExBaseList *pListMatchRef = &pXMatchObj->m_listMacthRefObject;

	if (pListMatchRef != NULL)
	{
		if (pListMatchRef->GetCount() == 1)
		{
			m_pAllDatasDlg->SelectData(pListMatchRef->GetHead());
		}
	}
}

void CGbDeviceReplaceByMmsDvmEditGrid::CreateAllDatasDlg()
{
	if (m_pAllDatasDlg == NULL)
	{
		CXMatchEditGridCtrlBase::CreateAllDatasDlg();
		AddAllDatasToDlg();
	}
}