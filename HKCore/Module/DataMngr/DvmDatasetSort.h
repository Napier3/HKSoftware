//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.h  CDvmDatasetSort

#pragma once

#include "DvmDataset.h"


class CDvmDatasetSort
{
private:
	typedef struct _struct_DvmDataSort
	{
		CDvmData *pData;

		__time64_t tm64Value;
	}DVMDATASORT, *PDVMDATASORT;

public:
	CDvmDatasetSort();
	virtual ~CDvmDatasetSort();

private:
	CDvmDataset *m_pDvmDataset;
	
public:
	void SortByAttrValue_t(CDvmDataset *pDataset);
	
protected:
	BOOL InitDvmStruct(PDVMDATASORT pSort, CDvmData *pDvmData);
	
	CDvmValue* FindValue(CDvmData *pDvmData, const CString &strID);
	BOOL Sort(PDVMDATASORT pSort, long nCount);

};

