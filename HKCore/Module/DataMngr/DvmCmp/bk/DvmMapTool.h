//DvmMapTool.h  CDvmMapTool

#pragma once



#include "..\DvmDevice.h"
#include "..\DataTypes.h"
#include "DvmDeviceMap.h"
#include "..\..\StringCmp\StringCmp.h"
#include "..\..\KeyDb\XMatchToolBase.h"
#include "..\..\KeyDb\XKeyDB.h"
#include "..\..\Office\msword9.h"
#include "DvmCmpKeyDataTypes.h"
#include "..\DataGroup.h"

#define CMP_STATE_NONE      -1
#define CMP_STATE_DATASET   0
#define CMP_STATE_DATA      1

#define WM_OPEN_DVMCMP_DATASET  (WM_USER + 2115)

#define DVM_MAP_CONFIG_FILE      _T("DvmMapConfig.xml")
#define DVM_MAP_CONFIG_LDEVICE   _T("LDevice")
#define DVM_MAP_CONFIG_DATASET   _T("Dataset")

class CDvmMapTool : public CExBaseList
{
public:
	CDvmMapTool();
	virtual ~CDvmMapTool();

	HTREEITEM     m_hStand;
	HTREEITEM     m_hDestCmp;

	CDvmDevice *m_pStand;
	CDvmDevice *m_pMap;
	CDataGroup *m_pDvmMapConfig;
	BOOL OpenDvmMapConfigFile();

	CDvmDeviceMap m_oDvmDeviceMap;

	static BOOL g_bDvmCmdDataID;
	//static BOOL g_bDvmCmdDataNameFull;
	static BOOL g_bOnlyShowNoMap;
public:
	virtual UINT GetClassID() {    return DMPCLASSID_CDVMMAPTOOL;   }

public:
	BOOL OpenDvmCmpFile(const CString &strFile);
	void CmpDeviceFile(const CString &strStandDvmFile, const CString &strDestDvmFile);
	void CmpDevice(CDvmDevice *pStand, CDvmDevice *pDest);
	void OpenDvmCmpRptExportFile();
	CString SaveDvmCmpMapFile();
	CDvmDeviceMap* GetDvmDeviceMap()	{	return &m_oDvmDeviceMap;	}
	CDvmDevice* GetMapDvmDevice()		{	return m_pMap;				}

	void CmpDvmDataset(CDvmDatasetMap *pDatasetMap, BOOL bFullCmp);
	void UpdateDvmDataMap(CDvmDataMap *pMap, CDvmData *pDestCmpData);
	void UpdateDvmDataMap(CDvmData *pStandData, CDvmData *pDestCmpData);
	void UpdateDvmValueMap(CDvmValueMap *pValueMap, CDvmValue *pDestCmpValue);

	void ClearDatasetMap(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStandDataset);  //«Âø’”≥…‰πÿœµ  shaolei 20220209
protected:
	void OepnDeviceFile(const CString &strStandDvmFile, const CString &strDestDvmFile);
	void AfterOpenDeviceFile();  //shaolei  20220209
	void RemoveLdevice(CDataGroup *pLDeviceConfig, CDvmDevice *pDvmDevice);
	void RemoveDataset(CDataGroup *pDatasetConfig, CDvmLogicDevice *pLDevice);
	BOOL IsIDExist(const CString &strID, CDataGroup *pGroup);
	void CmpDvmDevice();
// 	void CmpDvmDevice_DsMap(CDvmDevice *pStand, CDvmDevice *pDestCmp);
// 	void CmpDvmDevice_DsDataMap();
	void OpenDvmCmpMapFile();
	void CmpDvmData(CDvmDataMap *pDvmCmpObj);

//////////////////////////////////////////////////////////////////////////
protected:
	void UpdateMapDevice_Stand();
	void UpdateMapLdevice_Stand(CDvmLDeviceMap *pLDviceMap, CDvmLogicDevice *pStandLdevice);
	void UpdateMapDataset_Stand(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStandDataset);
	void UpdateMapData_StandData(CDvmDataMap *pDataMap, CDvmData *pStandData);
	void UpdateMapValue_Stand(CDvmValueMap *pValueMap, CExBaseList *pParentDestList);
	//CDvmValue* UpdateMapValue_FindValue(const CString &strID, CExBaseList *pParentDestList, CDvmDataset *pDestDataset);

	void UpdateMapDvice_Map();
	void UpdateMapLdevice_Map(CDvmLDeviceMap *pLDviceMap);
	void UpdateMapDataset_Map(CDvmDatasetMap *pDatasetMap);
	void UpdateMapData_Map_DestDataset(CDvmDataMap *pDataMap, CDvmDataset *pDestDataset);
	void UpdateMapValue_Map_Dest(CDvmValueMap *pValueMap, CExBaseList *pParentDestList, CDvmDataset *pDestDataset);
	CDvmValue* UpdateMapValue_FindValue(const CString &strID, CExBaseList *pParentDestList, CDvmDataset *pDestDataset);


protected:
// 	void SortByStand();
	CDvmLogicDevice* FindCmpDvmLdevice(CDvmDevice *pDestDvmDevice, CDvmLogicDevice *pStandLdevice);
	long        CanCmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);
// 	CDvmLDeviceMap* CmpDvmLdevice(CDvmDevice *pDestDvmDevice, CDvmLogicDevice *pStandLdevice);
// 	CDvmLDeviceMap* CmpDvmLdevice(CDvmLDeviceMap *pLDviceMap, CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice);
	void CmpDvmLdevice_Dest_StandMap(CDvmDevice *pDestDvmDevice, CDvmLDeviceMap *pStandLdeviceMap);
	void CmpDvmLdevice_Map_Dest(CDvmLDeviceMap *pLDviceMap, CDvmLogicDevice *pDestCmpLdevice, BOOL bFullCmp);

	CDvmDataset* FindCmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset);
	long        CanCmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset);
	CDvmDatasetMap* CmpDvmDataset(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, BOOL bFullCmp);
	CDvmData* FindDvmData_Name(CDvmDataset *pDataset, CDvmData *pStandDvmData, long nStandIdKey, BOOL bFullCmp);
	CDvmDatasetMap* CmpDvmDataset_Name(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, BOOL bFullCmp);
	void CmpDvmDataset_ID(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStand, CDvmDataset *pDestCmpDataset);
	
	CDvmData* FindCmpDvmData(CDvmDataset *pDsDest, CDvmData *pStandData, CDvmDatasetMap *pDatasetMap);
	long        CanCmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData);
	CDvmDataMap* CmpDvmData(CDvmDataset *pDestDataset, CDvmData *pStandData, CDvmDatasetMap *pDatasetMap);
	CDvmDataMap* CmpDvmData(CDvmData *pStandData, CDvmData *pDestData, CDvmDataMap *pDataMap);
	
	CDvmValue* FindCmpDvmValue(CExBaseList *pDest, CDvmValue *pStandValue);
	long        CanCmpDvmValue(CDvmValue *pStand, CDvmValue *pDestCmpValue);
	void CmpDvmValue(CDvmData *pDestData, CDvmValue *pStandValue, CDvmDataMap *pDataMap);
 	void CmpDvmValueEx(CDvmValue *pStand, CDvmValue *pDestCmpValue, CDvmValueMap *pValueMap);
// 	CDvmCmpObj* CmpDvmValueVal(CDvmValue *pStand, CDvmValue *pDestCmpValue);

	CDvmMapObject* GetCmpMatchObject(CExBaseList &listCmpObj);

protected:
	CDvmCmpKeyDataTypes m_oDvmCmpKeyDataTypes;

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
	CString    GetDvmValueKey(CDvmValue *pDvmValue);

protected:
// 	void AddOtherCmpObj_Stand();
// 	long AddOtherCmpObj_Stand(CExBaseList *pStand, CExBaseList *pListCmpObj);
// 	BOOL IsStandInListCmpObj(CExBaseObject *pStand, CExBaseList *pListCmpObj);
// 	long AddOtherCmpObj_DestCmp(CExBaseList *pDestCmp, CExBaseList *pListCmpObj);
// 	BOOL IsDestCmpInListCmpObj(CExBaseObject *pDestCmp, CExBaseList *pListCmpObj);

protected:
	void InitByDvmMap();

// 	void CreateDvmMap();
// 	void CreateDvmMap_Ldevice(CDvmCmpObj *pDvmLdeviceCmp);
// 	void CreateDvmMap(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp);
// 	void CreateDvmMap(CDvmDataMap *pMap, CDvmCmpObj *pDvmDataCmp);

protected:
	void UpdateByMap_DsCmp(CDvmDatasetMap *pMap, CDvmDatasetMap *pDvmDatasetCmp);
	void UpdateByMap_DataCmp(CDvmDatasetMap *pMap, CDvmDataMap *pDvmDataCmp);

protected:
	CXKeyDB m_oKeyDB;
	CXMatchToolBase m_oXMatchTool;

	virtual void OpenKeyDbFile();
	virtual void XMatchDataset(CDvmDataset *pDsDestCmp, CDvmDataset *pDsStand);


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

	void ExportReport_DsCmp(CDvmDatasetMap *pDsCmp);
	void ExportReport_DataCmp(CDvmDataMap *pDataCmp, MSWord::Table &oTable, long &nRowIndex);
	void ExportReport_ValueCmp(CDvmValueMap *pValueCmp, MSWord::Table &oTable, long &nRowIndex);
	long ExportReport_DataCmp_GetRows(CDvmDataMap *pDataCmp);
	void InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit=TRUE);
	void MergeRow(MSWord::Row &oRow);
	void GetRowCell(MSWord::Row &oRow, MSWord::Cell &oCell, long nIndex);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, CStringCmpBlocks *pStrCmpBlcks);
};

/*extern BOOL g_bDvmCmdDataNameFull;*/