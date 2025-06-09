//DvmCmpTool.h  CDvmCmpTool

#pragma once



#include "..\DvmDevice.h"
#include "..\DataTypes.h"
#include "DvmDeviceMap.h"
#include "..\..\StringCmp\StringCmp.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include "..\..\..\Module\KeyDb\XKeyDB.h"
#include "..\..\..\Module\Office\msword9.h"

#define WM_OPEN_DVMCMPOBJ  (WM_USER + 2115)

#define  MAX_LDEVICE_KEY   10

#define DVMCMP_CLASSID_RESULT   (CLASSID_BASECLASS   +901)
#define DVMCMP_CLASSID_CMPOBJ   (CLASSID_EXLISTCLASS +902)
#define DVMCMP_CLASSID_TOOL     (CLASSID_EXLISTCLASS +903)

#define CMP_STATE_NONE      -1
#define CMP_STATE_DATASET   0
#define CMP_STATE_DATA      1


class CDvmCmpResult : public CExBaseObject
{
public:
	CDvmCmpResult(CString *m_pStand, CString *pDestCmp);
	virtual ~CDvmCmpResult();

	CString *m_pStand;
	CString *m_pDestCmp;
	void Cmp();

public:
	virtual UINT GetClassID() {    return DVMCMP_CLASSID_RESULT;   }
	BOOL IsCmpError();

protected:
	BOOL m_bCmpErr;
};

class CDvmCmpObj : public CExBaseList
{
public:
	CDvmCmpObj(CExBaseObject *pStand, CExBaseObject *pDestCmp);
	virtual ~CDvmCmpObj();

	BOOL IsDvmLdeviceCmpObj();
	BOOL IsDvmDatasetCmpObj();
	CString GetDvmCmpID();

	BOOL IsNameCmpError();
	BOOL IsIdCmpError();
	BOOL IsDataTypeCmpError();
	BOOL IsMinCmpError();
	BOOL IsMaxCmpError();
	BOOL IsStepCmpError();

	BOOL IsCmpError();
	BOOL IsCmpError_Own();
	BOOL IsCmpError_Child();

	void StringCmp();
	CStringCmpBlocks* GetNameCmp_Stand();
	CStringCmpBlocks* GetNameCmp_Dest();
	CStringCmpBlocks* GetIDCmp_Stand();
	CStringCmpBlocks* GetIDCmp_Dest();
	void FreeStringCmp();

	void GetCmpErrorNum(long &nCmpErrs);
protected:
	void CmpEx();
	void Cmp();

	CStringCmp *m_pStringCmp_Name;
	CStringCmp *m_pStringCmp_ID;

public:
	CExBaseObject *m_pStand;
	CExBaseObject *m_pDestCmp;
	long          m_nDestIndex;
	long          m_nStandIndex;
	long          m_nCmpRate;
	long          m_nCmpResult;   //对象的不同之处
	HTREEITEM     m_hStand;
	HTREEITEM     m_hDestCmp;
	long          m_nChildCmp;

	BOOL          m_bNameCmpErr;
	BOOL          m_bIDCmpErr;
	BOOL          m_bDataTypeCmpErr;
	BOOL          m_bMinCmpErr;
	BOOL          m_bMaxCmpErr;
	BOOL          m_bStepCmpErr;
	
	void InitCmpResultByChildCmp();
	BOOL IsInChild_Stand(CExBaseObject *pStand);
	CDvmCmpObj* SetStand(CExBaseObject *pStand);
	CDvmCmpObj* SetDest(CExBaseObject *pDest);

protected:
	CDvmCmpObj* RemoveParentStand(CExBaseObject *pStand);
	CDvmCmpObj* RemoveParentDest(CExBaseObject *pDest);
	void RemoveChildDest();
	void RemoveChildStand();

public:
	virtual UINT GetClassID() {    return DVMCMP_CLASSID_CMPOBJ;   }
};


class CDvmCmpTool : public CExBaseList
{
public:
	CDvmCmpTool();
	virtual ~CDvmCmpTool();

	HTREEITEM     m_hStand;
	HTREEITEM     m_hDestCmp;

	CDvmDevice *m_pStand;
	CDvmDevice *m_pDestCmp;

	CDvmDeviceMap m_oDvmDeviceMap;
	CDataTypes m_oDvmCmpValueKeyDataType;

public:
	virtual UINT GetClassID() {    return DVMCMP_CLASSID_TOOL;   }

public:
	void AttachKeyDB(CXKeyDB *pKeyDB);
	void CmpDvmDevice(CDvmDevice *pStand, CDvmDevice *pDestCmp);
	void CmpDvmDevice_DsMap(CDvmDevice *pStand, CDvmDevice *pDestCmp);
	void CmpDvmDevice_DsDataMap();
	void SaveDvmCmpMapFile();
	void OpenDvmCmpMapFile();
	void CmpDvmData(CDvmCmpObj *pDvmCmpObj);
	void OpenDvmCmpValueKeyDataTypeFile();
	void OpenDvmCmpRptExportFile();

	void GetCmpErrorNum(long &nCmpErrs);
protected:
	void SortByStand();
	CDvmLogicDevice* FindCmpDvmLdevice(CDvmDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);
	long        CanCmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);
	CDvmCmpObj* CmpDvmLdevice(CDvmDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);
	CDvmCmpObj* CmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);

	CDvmDataset* FindCmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset);
	long        CanCmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset);
	CDvmCmpObj* CmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset, CDvmCmpObj *pParent);
	CDvmCmpObj* CmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset);
	void SortByStand(CDvmCmpObj *pDvmCmpObj, CDvmDataset *pDsStand, CDvmDataset *pDsDest);
	CDvmCmpObj* FindByStand(CDvmCmpObj *pDvmCmpObj, CDvmData *pDvmData);
	CDvmData* FindDvmData_Name(CDvmDataset *pDataset, const CString &strName, long nStandIdKey, BOOL bFullCmp);
	CDvmCmpObj* CmpDvmDataset_Name(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset);
	CDvmCmpObj* CmpDvmDataset_ID(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, CDvmCmpObj *pDsCmpObj);
	
	CDvmData* FindCmpDvmData(CDvmDataset *pStand, CDvmData *pDestCmpData, CDvmCmpObj *pParent);
	long        CanCmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData);
	CDvmCmpObj* CmpDvmData(CDvmDataset *pStand, CDvmData *pDestCmpData, CDvmCmpObj *pParent);
	CDvmCmpObj* CmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData);
	
	CDvmValue* FindCmpDvmValue(CExBaseList *pStand, CDvmValue *pDestCmpData);
	CString    GetDvmValueKey(CDvmValue *pDvmValue);
	long        CanCmpDvmValue(CDvmValue *pStand, CDvmValue *pDestCmpValue);
	CDvmCmpObj* CmpDvmValue(CDvmData *pStand, CDvmValue *pDestCmpValue, CDvmCmpObj *pParent);
	CDvmCmpObj* CmpDvmValueEx(CDvmValue *pStand, CDvmValue *pDestCmpValue);
	CDvmCmpObj* CmpDvmValueVal(CDvmValue *pStand, CDvmValue *pDestCmpValue);

	CDvmCmpObj* GetCmpMatchObject(CExBaseList &listCmpObj);

protected:
	CDataTypes m_oKeyDataTypes;
	static const CString g_strLdeviceDataTypeID;
	static const CString g_strDatasetDataTypeID;
	static const CString g_strDvmCmpValueKeyDataTypeID;
	static const CString g_strDvmCmpFullNameIdKeyTypeID;


	CDataType *m_pLdeviceDataType;
	CDataType *m_pDatasetDataType;
	CDataType *m_pDvmCmpValueKeyDataType;
	CDataType *m_pDvmCmpFullNameIdKeyType;

	CExBaseList m_listCmpErrors;
	CDvmDataset m_oRptDstaset;
	DWORD m_dwCmpState;

public:
	long CanCmpDvmObject(CExBaseObject *pStand, CExBaseObject *pDestCmpObj);
	long CanCmpDvmObject_ID(CExBaseObject *pStand, CExBaseObject *pDestCmpObj);
	void OpenKeyDataTypesFile(const CString &strFile);
	long GetLdeviceKey(const CString &strText);
	long GetDatasetKey(const CString &strText);
	long GetCmpFullNameIdKey(const CString &strText);
	long GetKey(CDataType *pDataType, const CString &strText);

protected:
	void AddOtherCmpObj_Stand();
	long AddOtherCmpObj_Stand(CExBaseList *pStand, CExBaseList *pListCmpObj);
	BOOL IsStandInListCmpObj(CExBaseObject *pStand, CExBaseList *pListCmpObj);
	long AddOtherCmpObj_DestCmp(CExBaseList *pDestCmp, CExBaseList *pListCmpObj);
	BOOL IsDestCmpInListCmpObj(CExBaseObject *pDestCmp, CExBaseList *pListCmpObj);

protected:
	void InitByDvmMap();

	void CreateDvmMap();
	void CreateDvmMap_Ldevice(CDvmCmpObj *pDvmLdeviceCmp);
	void CreateDvmMap(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp);
	void CreateDvmMap(CDvmDataMap *pMap, CDvmCmpObj *pDvmDataCmp);

protected:
	void UpdateByMap_DsCmp(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp);
	void UpdateByMap_DataCmp(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDataCmp);

protected:
	BOOL m_bKeyDbRef;
	CXKeyDB *m_pKeyDB;
	CXMatchToolBase m_oXMatchTool;

	virtual void OpenKeyDbFile();
	virtual void XMatchDataset(CDvmDataset *pDsStand, CDvmDataset *pDsDestCmp);


public:
	void ExportReportFile(const CString &strFile);

protected:
	MSWord::_Application m_WordApp;
	MSWord::_Document		m_doc;
	float    m_fWidthCol1, m_fWidthCol2, m_fWidthCol3, m_fWidthCol4;

	BOOL CreateWordApplication(BOOL bVisible);
	BOOL ExitWordApplication();
	BOOL NewWordReportFile();
	void InsertTitle(const CString &strTitle, long nTitleLevel);

	void ExportReport_DsCmp(CDvmCmpObj *pDsCmp);
	void ExportReport_DataCmp(CDvmCmpObj *pDataCmp, MSWord::Table &oTable, long &nRowIndex);
	void ExportReport_ValueCmp(CDvmCmpObj *pValueCmp, MSWord::Table &oTable, long &nRowIndex);
	long ExportReport_DataCmp_GetRows(CDvmCmpObj *pDataCmp);
	void InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit=TRUE);
	void MergeRow(MSWord::Row &oRow);
	void GetRowCell(MSWord::Row &oRow, MSWord::Cell &oCell, long nIndex);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, CStringCmpBlocks *pStrCmpBlcks);

	BOOL IsDsNeedWriteToReport(const CString &strID);;
};

//////////////////////////////////////////////////////////////////////////
//CDvmCmpToolConfig
class CDvmCmpToolConfig : public CExBaseObject
{
private:
	CDvmCmpToolConfig();
	virtual ~CDvmCmpToolConfig();

	CString m_strFile;

public:
	static CDvmCmpToolConfig* g_pDvmCmpToolConfig;
	static long g_nDvmCmpToolConfigRef;

	static CDvmCmpToolConfig* Create();
	static void Release();

public:
	//Test
	long m_nCmpWithID;
	long m_nDvmCmdDataNameFull;

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CDataMngrXmlRWKeys::g_pXmlKeys->m_strDvmCmpToolConfigKey;	}

public:
	long Save();
	long Open();

public:
	static long GetCmpWithID();
	static void SetCmpWithID(long nVal);

	static long GetDvmCmdDataNameFull();
	static void SetDvmCmdDataNameFull(long nVal);

};

