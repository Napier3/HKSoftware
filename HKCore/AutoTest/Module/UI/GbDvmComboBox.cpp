#include "StdAfx.h"
#include "GbDvmComboBox.h"
#include "..\..\Module\FilterText\FilterTextComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define PREV_STRING _T("----")

CGbDvmComboBox::CGbDvmComboBox(void)
{
}

CGbDvmComboBox::~CGbDvmComboBox(void)
{
}

void CGbDvmComboBox::ShowDvmTree(CDevice *pDevice)
{
	//GbDvmCmb_ShowDvmTree(pDevice, this, m_strFilterDsID);
	GbDvmCmb_ShowDvmTree(pDevice, this, m_astrFilterDsID);
}


CDataSet* CGbDvmComboBox::GetCurrSelDataset()
{
	long nItemCount = GetCount();

	if (nItemCount == 0)
	{
		return NULL;
	}

	long nSel = GetCurSel();
	CDataSet *pDataset = NULL;
	CDataSet *pDatasetFind = NULL;
	long nIndex = nSel;

	if (nIndex == CB_ERR)
	{
		nIndex = 0;
	}

	while (TRUE)
	{
		pDataset = (CDataSet *)GetItemDataPtr(nIndex);

		if (pDataset == NULL)
		{
			break;
		}

		if (pDataset->GetClassID() == GBCLASSID_DATASET)
		{
			pDatasetFind = pDataset;
			break;
		}

		if (pDataset->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			pDatasetFind = pDataset;
			break;
		}

		if (pDataset->GetClassID() == GBCLASSID_GBTDATAS)
		{
			pDatasetFind = pDataset;
			break;
		}

		nIndex++;

		if (nIndex >= nItemCount)
		{
			break;
		}
	}

	if (nIndex != nSel)
	{
		SetCurSel(nIndex);
	}

	return pDatasetFind;
}

void CGbDvmComboBox::SelectDataset(CDataSet *pDataset)
{
	long nIndex = 0, nFind = -1;
	long nCount = GetCount();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (GetItemDataPtr(nIndex) == pDataset)
		{
			nFind = nIndex;
			break;
		}
	}

	SetCurSel(nFind);
}

void CGbDvmComboBox::SelectDataset(const CString &strDatasetID)
{
	long nIndex = 0, nFind = -1;
	long nCount = GetCount();
	CExBaseObject *pObj = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObj = (CExBaseObject*)GetItemDataPtr(nIndex);
		if (pObj->m_strID == strDatasetID)
		{
			nFind = nIndex;
			break;
		}
		else
		{
			CString strPath;
			strPath = pObj->GetIDPathEx(GBCLASSID_CPU);

			if (strPath == strDatasetID)
			{
				nFind = nIndex;
				break;
			}
		}
	}

	SetCurSel(nFind);
}

void CGbDvmComboBox::AddFilterDsID(const CString &strFilterDsID)
{
	m_astrFilterDsID.Add(strFilterDsID);
}

void GbDvmCmb_ShowDvmTree(CCpus *pCpus, CComboBox *pCombBox, const CStringArray &astrFilterDsID);
void GbDvmCmb_ShowDvmTree(CCpu *pCpu, CComboBox *pCombBox, const CStringArray &astrFilterDsID);


void GbDvmCmb_ShowDvmTree(CDevice *pDevice, CComboBox *pCombBox, const CStringArray &astrFilterDsID)
{
	pCombBox->ResetContent();

	if (Gb_IsGuideBookTemplate(pDevice))
	{
		CGbtDataInterfaces *pCGbtDataInterfaces = pDevice->m_pGbtDataInterfaces;
		ASSERT (pCGbtDataInterfaces != NULL);
		ASSERT (pCGbtDataInterfaces->m_pGbtDatas != NULL);

		long nIndex = pCombBox->AddString(pCGbtDataInterfaces->m_pGbtDatas->m_strName);;
		pCombBox->SetItemDataPtr(nIndex, pCGbtDataInterfaces->m_pGbtDatas);
	}
	else
	{
		CExBaseList listCpus;
		pDevice->GetCpusList(listCpus, TRUE);
		POS pos = listCpus.GetHeadPosition();
		CCpus *pCpus = NULL;

		while (pos != NULL)
		{
			pCpus = (CCpus *)listCpus.GetNext(pos);
			 GbDvmCmb_ShowDvmTree(pCpus, pCombBox, astrFilterDsID);
		}

		listCpus.RemoveAll();
	}
}

void GbDvmCmb_ShowDvmTree(CCpus *pCpus, CComboBox *pCombBox, const CStringArray &astrFilterDsID)
{
	CString strText;
	long nIndex = 0;

	strText = pCpus->m_strName;

	if (strText.GetLength() == 0)
	{
		strText = pCpus->m_strID;
	}

	nIndex = pCombBox->AddString(strText);
	pCombBox->SetItemDataPtr(nIndex, pCpus);
	CString strPrev = PREV_STRING;

	POS pos = pCpus->GetHeadPosition();
	CCpu *pCpu = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)pCpus->GetNext(pos);

		GbDvmCmb_ShowDvmTree(pCpu, pCombBox, astrFilterDsID);
	}
}

BOOL GbDvmCmb_FiltDataset(const CString &strDatasetID, const CStringArray &astrFilterDsID)
{
	long nIndex = 0;
	long nCount = astrFilterDsID.GetCount();
	BOOL bTrue = FALSE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strDatasetID.Find(astrFilterDsID.GetAt(nIndex)) >= 0)
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void GbDvmCmb_ShowDvmTree(CCpu *pCpu, CComboBox *pCombBox, const CStringArray &astrFilterDsID)
{
	long nCount = 0;
	POS pos = pCpu->GetHeadPosition();
	CDataSet *pDataset = NULL;
	CString strTemp;

	if (astrFilterDsID.GetCount() > 0)
	{
		while (pos != NULL)
		{
			pDataset = (CDataSet *)pCpu->GetNext(pos);

			//if (pDataset->m_strID.Find(strFilterDsID) >= 0)
			if (GbDvmCmb_FiltDataset(pDataset->m_strID, astrFilterDsID))
			{
				nCount++;
			}
		}

		if (nCount == 0)
		{
			return;
		}
	}

	long nIndex = 0;
	CString strText;
	CString strPrev = PREV_STRING;

	pos = pCpu->GetHeadPosition();
	strText = strPrev + pCpu->m_strName;
	nIndex = pCombBox->AddString(strText);
	pCombBox->SetItemDataPtr(nIndex, pCpu);

	strPrev += PREV_STRING;

	while (pos != NULL)
	{
		pDataset = (CDataSet *)pCpu->GetNext(pos);

		//if (strFilterDsID.GetLength() >= 2)
		if (astrFilterDsID.GetCount() > 0)
		{
			//if (pDataset->m_strID.Find(strFilterDsID) >= 0)
			if (GbDvmCmb_FiltDataset(pDataset->m_strID, astrFilterDsID))
			{
				strText = strPrev + pDataset->m_strName;
				nIndex = pCombBox->AddString(strText);
				pCombBox->SetItemDataPtr(nIndex, pDataset);
			}
		}
		else
		{
			strText = strPrev + pDataset->m_strName;
			nIndex = pCombBox->AddString(strText);
			pCombBox->SetItemDataPtr(nIndex, pDataset);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CDvmDatasetFilterTool
CFilterTextMngr* CDvmDatasetFilterTool::g_pDatasetFilter = NULL;
long CDvmDatasetFilterTool::g_nDatasetFilterCount = 0;
CString CDvmDatasetFilterTool::g_strDatasetFilterFile = _T("CommCmdDatasFilterKey.xml");
CDWordArray CDvmDatasetFilterTool::g_dwarrCmbDsFilter;

CDvmDatasetFilterTool* CDvmDatasetFilterTool::g_pDvmDatasetFilterTool = NULL;


CDvmDatasetFilterTool::CDvmDatasetFilterTool()
{
	g_pDatasetFilter = new CFilterTextMngr();
	CString strFile;
	strFile = _P_GetConfigFilePath(g_strDatasetFilterFile);
	g_pDatasetFilter->OpenXmlFile(strFile);
}

CDvmDatasetFilterTool::~CDvmDatasetFilterTool()
{
	delete g_pDatasetFilter;
}


CDvmDatasetFilterTool* CDvmDatasetFilterTool::Create()
{
	g_nDatasetFilterCount++;

	if (g_nDatasetFilterCount == 1)
	{
		g_pDvmDatasetFilterTool = new CDvmDatasetFilterTool();
	}

	return g_pDvmDatasetFilterTool;
}


void CDvmDatasetFilterTool::Release()
{
	g_nDatasetFilterCount--;

	if (g_nDatasetFilterCount == 0)
	{
		delete g_pDvmDatasetFilterTool;
		g_pDvmDatasetFilterTool = NULL;
	}
}

CFilterTextMngr* CDvmDatasetFilterTool::GetFilterTextMngr()
{
	ASSERT (g_pDvmDatasetFilterTool != NULL);
	return g_pDvmDatasetFilterTool->g_pDatasetFilter;
}

void CDvmDatasetFilterTool::AddDatasetCmbFilter(CComboBox *pComboBox)
{
	g_dwarrCmbDsFilter.Add((DWORD)pComboBox);
}

void CDvmDatasetFilterTool::FreeDatasetCmbFilter(CComboBox *pComboBox)
{
	long nCount = g_dwarrCmbDsFilter.GetCount();
	long nIndex = 0;
	CComboBox *p = NULL;
	long nFind = -1;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = (CComboBox*)g_dwarrCmbDsFilter.GetAt(nIndex);

		if (p == pComboBox)
		{
			nFind = nIndex;
			break;
		}
	}

	if (nFind >= 0)
	{
		g_dwarrCmbDsFilter.RemoveAt(nFind);
	}
}

void CDvmDatasetFilterTool::UpdateAllDatasetCmbFilter(CComboBox *pComboBox)
{
	long nCount = g_dwarrCmbDsFilter.GetCount();
	long nIndex = 0;
	CFilterTextComboBox *p = NULL;
	long nFind = -1;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = (CFilterTextComboBox*)g_dwarrCmbDsFilter.GetAt(nIndex);

		if (pComboBox != p)
		{
			p->ShowBaseList(g_pDatasetFilter);
		}
	}
}

