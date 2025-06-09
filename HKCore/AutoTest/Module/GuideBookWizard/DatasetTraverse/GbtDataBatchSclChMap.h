#pragma once

#include "..\DinWzdFromSclGinChs.h"
#include "..\GbStxmlFileMap.h"

class  CGbtDataBatchSclChMap : public CExBaseObject
{
public:
	CGbtDataBatchSclChMap();
	virtual ~CGbtDataBatchSclChMap();

	CDataObj *m_pDataObj;
	CDinWzdFromSclGinCh *m_pSclGinCh;
};


class CGbtDataBatchSclChMapGen :public CExBaseList
{
public:
	CGbtDataBatchSclChMapGen(void);
	virtual ~CGbtDataBatchSclChMapGen(void);

	CString m_strDataTypeFilter;

public:
	void SetAutoNameID(BOOL b)	{	m_bAutoNameID = b;	}
	void SetGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pStxmlFileMngr);
// 	void SetGbtBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups);
	void AddDataset(CExBaseList *pDataset);	//{	m_listDataset.AddTail(pDataset);	}
	void AddDatasets(CExBaseList *pDatasets);
	void SetXKeyDB(CXKeyDB *pXKeyDB)		{	m_pXKeyDB = pXKeyDB;				}
	CXMatchToolBase* GetMatchTool()	{	return &m_oXMatchTool;	}

	void OpenDinWzdFromSclGinChsFile(const CString &strFile);
	CExBaseList* GetXMatchList(CGbtDataBatchSclChMap *pSclChMap);
	void InitMatchFirst();

	void Match();
	void Traverse();
	BOOL CanRunTraverse(CString &strMsg, long &nRowIndex);

	CExBaseList* GetAllDataset()	{	return &m_listDataset;	}

protected:
	CGbInsertStxmlFile  *m_pGbInsertStxmlFile;
// 	CGbtBatchItemGroups  *m_pBatchItemGroups;
	CDinWzdFromSclGinChs m_oDinWzdFromSclGinChs;
	CExBaseList          m_listDatas;
	CExBaseList          m_listDataset;
	CXKeyDB              *m_pXKeyDB;
	CXMatchToolBase      m_oXMatchTool;

	BOOL m_bAutoNameID;

	void InitMapObj(CGbtDataBatchSclChMap *pGbtDataTraverseObj, CXMatchList *pDstXMatchList);
	CExBaseList* GetXMatchList(CGbtDataBatchSclChMap *pSclChMap, CXMatchList *pDstXMatchList);
	void InitGbtDataBatchSclChMapGen();
	void InitNameIDAuto();
	void InitNameIDAuto(CGbtBatchItemGroup *pGroup);
	void InitGbtDatasRampObj();

	void InitAllDataObj(CExBaseList &listSclChMap);
	void Traverse(CGbtDataBatchSclChMap *pSclChMap, CGbtDataInterfaceMap *pGbtDataInterfaceMap);
};

