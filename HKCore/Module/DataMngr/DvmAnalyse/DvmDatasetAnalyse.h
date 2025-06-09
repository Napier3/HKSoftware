//DvmDatasetAnalyse.h  CDvmDatasetAnalyse

#pragma once

#include "..\DataMngr\DvmDataset.h"
#include "DvmDataAnalyse.h"

class CDvmDatasetAnalyse : public CExBaseList
{
public:
	CDvmDatasetAnalyse();
	virtual ~CDvmDatasetAnalyse();

	CDvmDataset *m_pDvmDatasetRef;
	void DvmAnalyse(CDvmDataset *pDvmDataset, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery); 

	void DvmQueryFilter(CExBaseList &listTemplate);
protected:

};