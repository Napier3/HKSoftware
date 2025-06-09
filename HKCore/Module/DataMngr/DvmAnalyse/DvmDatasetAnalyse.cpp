//DvmDatasetAnalyse.cpp  CDvmDatasetAnalyse

#include "stdafx.h"
#include "DvmDatasetAnalyse.h"
#include "DvmDataAnalyse.h"

CDvmDatasetAnalyse::CDvmDatasetAnalyse()
{
	m_pDvmDatasetRef = NULL;
}

CDvmDatasetAnalyse::~CDvmDatasetAnalyse()
{
	
}

void CDvmDatasetAnalyse::DvmAnalyse(CDvmDataset *pDvmDataset, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery)
{
	ASSERT(pDvmDataset!=NULL);
	m_pDvmDatasetRef = pDvmDataset;
	CDvmDataAnalyse* pDvmDataAnalyse = NULL;
	CDvmData* pDvmData = NULL;
	POS pos = pDvmDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDvmDataset->GetNext(pos);
		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pDvmData = (CDvmData*)p;
			pDvmDataAnalyse = new CDvmDataAnalyse();
			AddNewChild(pDvmDataAnalyse);
			pDvmDataAnalyse->DvmAnalyse(pDvmData,pXKeyDB, pQuery);
		}
	}
}

void CDvmDatasetAnalyse::DvmQueryFilter(CExBaseList &listTemplate)
{
	CDvmDataAnalyse *pDataAnls = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDataAnls = (CDvmDataAnalyse *)GetNext(pos);
		pDataAnls->DvmQueryFilter(listTemplate);
	}
}

