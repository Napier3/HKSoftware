
#pragma once
#include "PxiData.h"

// CPxiDataSet 

class CPxiDataSet
{
public:
	CDvmDataset *m_pDataset;
	CString m_strReadSoeDsPath;

	static CPxiDataSet* _NewPoDataset(CDvmDataset *pDataset)
	{
		CPxiDataSet *pNew = new CPxiDataSet();
		pNew->m_pDataset = pDataset;
		return pNew;
	}
	
public:
	CPxiDataSet();
	virtual ~CPxiDataSet();

	virtual void OnFinalRelease();
	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(CString newVal);
	long GetCount(void);
	CPxiData* GetItem(long nIndex);
	CPxiData* FindDataByID(const CString &strDataID);
	CPxiData* FindDataByName(const CString &strName);
	CString GetXmlData(void);
	long SetXmlData(const CString &strXmlData);
	CString GetXmlDataEx(void);

    //2020-9-8  lijunqing
    void InitByDataset(CDvmDataset *pDataset);
};


