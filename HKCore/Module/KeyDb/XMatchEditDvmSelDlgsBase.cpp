#include "StdAfx.h"
#include "XMatchEditDvmSelDlgsBase.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDatasetSelDlg* CXMatchEditDvmSelDlgsBase::m_pAllDatasDlg = NULL;
long CXMatchEditDvmSelDlgsBase::g_nAllDatasDlgRef = 0;


CXMatchRefObjectSelDlg* CXMatchEditDvmSelDlgsBase::m_pMatchedDatasDlg = NULL;
long CXMatchEditDvmSelDlgsBase::m_nMatchedDatasDlgRef = 0;

CXMatchEditDvmSelDlgsBase::CXMatchEditDvmSelDlgsBase(void)
{
	m_pXMatchTool = NULL;
	m_pMatchedDatasDlg = NULL;
	m_pDataSelChangeMsgRcvWnd = NULL;

	m_nMatchedDatasDlgRef++;
	m_nShowDataMode = 1;
	g_nAllDatasDlgRef++;
	m_bShowMatchDataChanged = FALSE;
	m_pDlgsParentWnd = NULL;
	m_nXMatchRefClassID = 0;
}

CXMatchEditDvmSelDlgsBase::~CXMatchEditDvmSelDlgsBase(void)
{
	m_nMatchedDatasDlgRef--;

	if (m_nMatchedDatasDlgRef == 0)
	{
		if (m_pMatchedDatasDlg != NULL)
		{
			m_pMatchedDatasDlg->DestroyWindow();
			delete m_pMatchedDatasDlg;
			m_pMatchedDatasDlg = NULL;
		}
	}

	g_nAllDatasDlgRef--;

	if (g_nAllDatasDlgRef == 0)
	{
		if (m_pAllDatasDlg != NULL)
		{
			m_pAllDatasDlg->DestroyWindow();
			delete m_pAllDatasDlg;
			m_pAllDatasDlg = NULL;
		}
	}
}


void CXMatchEditDvmSelDlgsBase::CreateMatchedDatasDlg()
{
	if (m_pMatchedDatasDlg == NULL)
	{
		m_pMatchedDatasDlg = new CXMatchRefObjectSelDlg(this, m_pDlgsParentWnd);
		m_pMatchedDatasDlg->SetWindowTitle(g_sLangTxt_SelMatchDataObject/*_T("选择匹配的数据对象")*/);
		m_pMatchedDatasDlg->SetUseModeless();
		m_pMatchedDatasDlg->DoModal();
	}
	else
	{
		m_pMatchedDatasDlg->ShowWindow(SW_SHOW);
	}
}

void CXMatchEditDvmSelDlgsBase::CreateAllDatasDlg()
{
	if (m_pAllDatasDlg == NULL)
	{
		m_pAllDatasDlg = new CXMatchDatasetSelDlg(this);
		m_pAllDatasDlg->SetWindowTitle(g_sLangTxt_SelMatchDataObject/*_T("选择匹配的数据对象")*/);
		m_pAllDatasDlg->SetUseModeless();
		m_pAllDatasDlg->DoModal();
	}
	else
	{
		if (!m_pAllDatasDlg->IsWindowVisible())
		{
			m_pAllDatasDlg->ShowWindow(SW_SHOW);
		}

		m_pAllDatasDlg->BringWindowToTop();
	}

	m_pAllDatasDlg->m_pEdit = this;
}

void CXMatchEditDvmSelDlgsBase::AddDatasetsToDlg(CExBaseList *pListAllDataset)
{
	if (m_pMatchedDatasDlg != NULL)
	{
		if (m_pMatchedDatasDlg->IsWindowVisible())
		{
			m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
		}
	}

	if (m_bShowMatchDataChanged)
	{
		m_pAllDatasDlg->ResetDatasetList();
		POS pos = pListAllDataset->GetHeadPosition();
		CExBaseList *pDataset = NULL;

		while (pos != NULL)
		{
			pDataset = (CExBaseList *)pListAllDataset->GetNext(pos);
			m_pAllDatasDlg->AddDataset(pDataset);
		}
	}

	if (!m_pAllDatasDlg->IsWindowVisible())
	{
		m_pAllDatasDlg->ShowWindow(SW_SHOW);
	}

	m_pAllDatasDlg->BringWindowToTop();
}

void CXMatchEditDvmSelDlgsBase::ShowAllDatasToDlg(CExBaseList *pDataset)
{
	if (m_pMatchedDatasDlg != NULL)
	{
		if (m_pMatchedDatasDlg->IsWindowVisible())
		{
			m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
		}
	}

	if (m_bShowMatchDataChanged)
	{
		m_pAllDatasDlg->ResetDatasetList();

		if (pDataset == NULL)
		{
			m_pAllDatasDlg->AddDataset(m_pXMatchTool->GetSrcRefList());
		}
		else
		{
			m_pAllDatasDlg->AddDataset(pDataset);
		}

		m_pAllDatasDlg->ShowDatasetTree();
		m_bShowMatchDataChanged = FALSE;
	}

	if (!m_pAllDatasDlg->IsWindowVisible())
	{
		m_pAllDatasDlg->ShowWindow(SW_SHOW);
	}

	m_pAllDatasDlg->BringWindowToTop();
}

void CXMatchEditDvmSelDlgsBase::ShowMatchedDatasToDlg(long nDataIndex)
{
	if (m_pAllDatasDlg != NULL)
	{
		if (m_pAllDatasDlg->IsWindowVisible())
		{
			m_pAllDatasDlg->ShowWindow(SW_HIDE);
		}
	}

	if (!m_pMatchedDatasDlg->IsWindowVisible())
	{
		m_pMatchedDatasDlg->ShowWindow(SW_SHOW);
	}


	m_pMatchedDatasDlg->BringWindowToTop();

	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(nDataIndex);
	ASSERT(pXMatchObject!= NULL);
	CExBaseList *pListMatchRef = &pXMatchObject->m_listMacthRefObject;
	m_pMatchedDatasDlg->ShowExBaseList(pListMatchRef, TRUE);
}

void CXMatchEditDvmSelDlgsBase::ShowMatchedDatasToDlg(CExBaseList *pListMacthRefs)
{
	if (m_pAllDatasDlg != NULL)
	{
		if (m_pAllDatasDlg->IsWindowVisible())
		{
			m_pAllDatasDlg->ShowWindow(SW_HIDE);
		}
	}

	if (!m_pMatchedDatasDlg->IsWindowVisible())
	{
		m_pMatchedDatasDlg->ShowWindow(SW_SHOW);
	}

	m_pMatchedDatasDlg->BringWindowToTop();
	m_pMatchedDatasDlg->ShowExBaseList(pListMacthRefs, TRUE, TRUE);
}

CExBaseObject* CXMatchEditDvmSelDlgsBase::GetPopSelectData()
{
	if (m_pAllDatasDlg == NULL)
	{
		return NULL;
	}

	if (!m_pAllDatasDlg->IsWindowVisible())
	{
		return NULL;
	}

	return m_pAllDatasDlg->GetSelectDataObject();
}

void CXMatchEditDvmSelDlgsBase::HideAllDlgs()
{
	if (m_pMatchedDatasDlg != NULL)
	{
		m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
	}

	if (m_pAllDatasDlg != NULL)
	{
		m_pAllDatasDlg->ShowWindow(SW_HIDE);
	}
}

