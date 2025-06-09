#pragma once

#include "GbtDataTraverseObj.h"
#include "..\GbStxmlFileMap.h"

class CGbtBatchDatasetTraverse :public CExBaseList
{
public:
	CGbtBatchDatasetTraverse(void);
	virtual ~CGbtBatchDatasetTraverse(void);

public:
	void SetGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pStxmlFileMngr);
	void Traverse(CExBaseList *pDatasetList);

protected:
	CGbInsertStxmlFile *m_pGbInsertStxmlFile;

	void InitGbtDatasTraverseObj();

	CExBaseList m_listAllDataObj;
	void InitAllDataObj(CExBaseList *pDatasetList);

	void Traverse(CGbtDataTraverseObj *pGbtDataTraverseObj);
	void Traverse(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex);
	void Traverse_Dataset(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex);
	void Traverse_ValRamp(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex);
};

