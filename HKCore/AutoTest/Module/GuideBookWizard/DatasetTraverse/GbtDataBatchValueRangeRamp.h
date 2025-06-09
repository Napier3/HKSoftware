#pragma once

#include "GbtDataTraverseObj.h"
#include "..\GbStxmlFileMap.h"

class CGbtDataBatchValueRangeRamp :public CExBaseList
{
public:
	CGbtDataBatchValueRangeRamp(void);
	virtual ~CGbtDataBatchValueRangeRamp(void);

public:
	void SetAutoNameID(BOOL b)	{	m_bAutoNameID = b;	}
	void SetGbtBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups);
	void Batch();

protected:
	CGbtBatchItemGroups *m_pBatchItemGroups;
	BOOL m_bAutoNameID;

	void InitNameIDAuto();
	void InitNameIDAuto(CGbtBatchItemGroup *pGroup);
	void InitGbtDatasRampObj();
	void Batch(CGbtDataTraverseObj *pGbtDataTraverseObj);
	void Batch(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtBatchItemGroup *ppGroup, long nIndex);
};

