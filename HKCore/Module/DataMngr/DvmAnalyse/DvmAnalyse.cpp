//DvmAnalyse.cpp  CDvmAnalyse

#include "stdafx.h"
#include "DvmAnalyse.h"
#include "DvmDatasetAnalyse.h"

CDvmAnalyse::CDvmAnalyse()
{
	AddDatasetKey(_T("Ena"));
	AddDatasetKey(_T("Setting"));
}

CDvmAnalyse::~CDvmAnalyse()
{
	m_listAnlyseDestObject.RemoveAll();
}

void CDvmAnalyse::DvmQueryFilter()
{
	POS pos = GetHeadPosition();
	CDvmDatasetAnalyse *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetAnalyse *)GetNext(pos);
		p->DvmQueryFilter(m_listAnlyseDestObject);
	}
}

BOOL CDvmAnalyse::IsDatasetNeedAnalyse(const CString &strID)
{
	long nCount = m_astrDatasetKey.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strID.Find(m_astrDatasetKey.GetAt(nIndex)) >= 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CDvmAnalyse::DvmAnalyse(CDvmDevice *pDvmDevice, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery)
{
	ASSERT(pDvmDevice!=NULL);

	POS pos = pDvmDevice->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *p1 = NULL;
	CExBaseList oList;

	while (pos != NULL)
	{
		p = pDvmDevice->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		CDvmLogicDevice* pLogicDevice = (CDvmLogicDevice*)p;
		POS pos1 = pLogicDevice->GetHeadPosition();

		while (pos1 != NULL)
		{
			p1 = pLogicDevice->GetNext(pos1);

			if (p1->GetClassID()==DVMCLASSID_CDVMDATASET)
			{
				if (IsDatasetNeedAnalyse(p1->m_strID))
				{
					oList.AddTail(p1);
				}
			}
		}
	}

	CDvmDatasetAnalyse* pDvmDatasetAnalyse = NULL;
	CDvmDataset* pDvmDataset = NULL;

	pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		p = oList.GetNext(pos);
		pDvmDataset = (CDvmDataset*)p;
		pDvmDatasetAnalyse = new CDvmDatasetAnalyse();
		AddNewChild(pDvmDatasetAnalyse);
		pDvmDatasetAnalyse->DvmAnalyse(pDvmDataset,pXKeyDB, pQuery);
	}

	oList.RemoveAll();

	DvmQueryFilter();
}

CDvmDatasetAnalyse* CDvmAnalyse::FindByDataset(CDvmDataset *pDataset)
{
	POS pos = GetHeadPosition();
	CDvmDatasetAnalyse *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetAnalyse *)GetNext(pos);

		if (p->m_pDvmDatasetRef == pDataset)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

