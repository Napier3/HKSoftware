//DvmMatchTool.h  CDvmMatchTool

#pragma once



#include "..\..\BaseClass\ExBaseList.h"
#include "..\..\KeyDB\XKeyDB.h"
#include "..\..\KeyDB\XMatchList.h"
#include "DvmCmpKeyDataTypes.h"
#include "DvmMapObject.h"

class CDvmMatchEqualObject
{
public:
	CDvmMatchEqualObject();
	virtual ~CDvmMatchEqualObject();

	CString m_strSrcKeysText;
	CString m_strDestKeysText;

	CXKeyMatchRefList m_listSrcMatchXKeys;
	CXKeyMatchRefList m_listDestMatchXKeys;

public:
	BOOL IsMatchTextSame(const CString &strSrcText, const CString &strDestText);
	BOOL InitMatchKey(CXKeyDB *pKeyDb, const CString &strSrcText, const CString &strDestText);
};

class CDvmMatchData : public CXMatchObject
{
public:
	CDvmMatchData();
	CDvmMatchData(CExBaseObject *pRefObj, CXKeyDB *pKeyDb);
	virtual ~CDvmMatchData();

	CString m_strExpr;

public:
	void ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual);
	void RestoreKeys(CDvmMatchEqualObject *pXMatchEqual);
	void GetAllMaps(CExBaseList &listVarMaps);
};

class CDvmMatchDataset : public CXMatchList
{
public:
	CDvmMatchDataset();
	virtual ~CDvmMatchDataset();

	void SetThreadProgress(CThreadProgressInterface *pThreadProgress)	{ m_pThreadProgress = pThreadProgress;	}
	void SetMatchRatio(long nMatchRatio)	{	m_nMatchRatio = nMatchRatio;	}

public:
	CExBaseList m_listSrcDataset;   //源数据集列表
	CExBaseList m_listDestDataset;   //目标数据集列表
	CExBaseList m_listSrcDatas;     //源数据集的所有数据对象
	CExBaseList m_listDestDatas;     //目标数据集的所有数据对象

	CXMatchList m_oDestXMatchList;   //目标数据集数据的分析对象

protected:
	CThreadProgressInterface *m_pThreadProgress;
	long m_nMatchRatio;

public:
	virtual CXMatchObject* CreateMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb);

public:
	BOOL IsMatchInclude(CExBaseList *pSrc, CExBaseList *pDest);
	void AddMatchDataset(CExBaseList *pSrc, CExBaseList *pDest);
	void XMatch(CXKeyDB *pXKeyDB);
	void ReXMatch();
	CXMatchObject* FindXMatchObjBySrc(CExBaseObject *pDvmDataObj);

	void ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual);
	void RestoreKeys(CDvmMatchEqualObject *pXMatchEqual);
	void SelFirstMatch();
	BOOL ValidateMatch();
	void GetAllMaps(CExBaseList &listVarMaps);
};


class CDvmMatchTool : public CExBaseList
{
public:
	CDvmMatchTool();
	virtual ~CDvmMatchTool();

	void SetClassID_Device(UINT nClassID)		{	m_nClassID_Device = nClassID;	}
	void SetClassID_Ldevice(UINT nClassID)		{	m_nClassID_Ldevice = nClassID;	}
	void SetClassID_Dataset(UINT nClassID)	{	m_nClassID_Dataset = nClassID;	}
	void SetClassID_Data(UINT nClassID)		{	m_nClassID_Data = nClassID;		}
	void SetXKeyDB(CXKeyDB *pKeyDB)			{	m_pXKeyDB = pKeyDB;				}

	CXMatchObject* FindXMatchObjBySrc(CExBaseObject *pDvmDataObj);
	CExBaseList* GetDestDvmDatasetList()	{	return &m_listDestDvmDataset;	}

protected:
	CDvmCmpKeyDataTypes m_oDvmCmpKeyDataTypes;

	//用于匹配的两个设备数据模型
	CExBaseList *m_pSrcDvmDevice;
	CExBaseList *m_pDestDvmDevice;

	CXKeyDB *m_pXKeyDB;
	UINT m_nClassID_Device;
	UINT m_nClassID_Ldevice;
	UINT m_nClassID_Dataset;
	UINT m_nClassID_Data;
	
	CExBaseList m_listLdDsMap;

	CExBaseList m_listDestDvmDataset;
public:
	void DvmMatch_Device(CExBaseList *pSrc, CExBaseList *pDest);

protected:
	void InitDestDvmDataset();
	void DvmMatch_BuildMatch(CExBaseList *pSrc, CExBaseList *pDest);
	void DvmMatch_XMatch();
	void ReXMatch();
	long DvmMatch_FindDestLdevice(CExBaseList *pSrcLdevice, CExBaseList *pDestDevice, CExBaseList &listLdevice);
	void DvmMatch_Ldevice_List(CExBaseList *pSrc, CExBaseList &listLdevice);
	void DvmMatch_Ldevice(CExBaseList *pSrc, CExBaseList *pDest);
	long DvmMatch_FindDestDataset(CExBaseList *pSrcDataset, CExBaseList *pDestLdevice, CExBaseList &listDataset);
	void DvmMatch_Dataset_List(CExBaseList *pSrcDataset, CExBaseList &listDataset);
	void DvmMatch_Dataset(CExBaseList *pSrc, CExBaseList *pDest);
	CDvmMatchDataset* FindDvmMatch_Dataset(CExBaseList *pSrc, CExBaseList *pDest);

	CDvmMapObject* AddDvmMap(CExBaseList *pSrc, CExBaseList *pDest);
	CDvmMapObject* FindDvmMap(CExBaseList *pSrc, CExBaseList *pDest);

public:
	void ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual);
	void RestoreKeys(CDvmMatchEqualObject *pXMatchEqual);
	void SelFirstMatch();
	BOOL ValidateMatch();
	void GetAllMaps(CExBaseList &listVarMaps);
};

