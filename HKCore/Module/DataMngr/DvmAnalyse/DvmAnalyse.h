//DvmAnalyse.h  CDvmAnalyse

#pragma once

#include "..\DataMngr\DvmDevice.h"
#include "..\DataMngr\DvmLogicDevice.h"
#include "DvmDatasetAnalyse.h"

class CDvmAnalyse : public CExBaseList
{
public:
	CDvmAnalyse();
	virtual ~CDvmAnalyse();

	CExBaseList m_listAnlyseDestObject;

	void DvmQueryFilter();
	void DvmAnalyse(CDvmDevice *pDvmDevice, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery); 

	CDvmDatasetAnalyse* FindByDataset(CDvmDataset *pDataset);

	void AddDatasetKey(const CString &strKey)	{	m_astrDatasetKey.Add(strKey);	}
	BOOL IsDatasetNeedAnalyse(const CString &strID);
	void ResetDatasetKey()								{	m_astrDatasetKey.RemoveAll();	}

	void QueryDatas(CDvmDataAnalyse *pSrcDataAnalyse);

protected:
	CStringArray m_astrDatasetKey;
	CDvmDevice *m_pDvmDevice;
};