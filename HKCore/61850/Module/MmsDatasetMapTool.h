// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MMSAPI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MMSAPI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "EnumType.h"
#include "MmsGlobal.h"
#include "../../Module/DataMngr/DvmCmp/DvmDeviceMap.h"

#define  DVMMAP_ACSI_NODETYPE_DATASET   0
#define  DVMMAP_ACSI_NODETYPE_DATA      1
#define  DVMMAP_ACSI_NODETYPE_VALUE     2


void mmsmap_GetDatasetFromAcsiNode(CDvmDataMap *pDataMap, CDvmDataset *pDataset);
void mmsmap_GetDatasetFromAcsiNode(CDvmValueMap *pValueMap, CExBaseList *pList);


class CMmsDvmDs_LdNode_Map : public CExBaseObject
{
public:
	CMmsDvmDs_LdNode_Map();
	virtual ~CMmsDvmDs_LdNode_Map();


	ACSI_NODE *m_pACSI_NODE;  //设备的指针
	LD_NODE *m_pLD_NODE;      //逻辑设备的指针
	LD_DATASET_INFO *m_pDataset; // 数据集指针
	CDvmDatasetMap *m_pDstasetMap;	//数据集映射
	long m_nACSI_NODE;
	long m_nLD_NODE;
	long m_nDATASET_INFO;

public:
	long GetDataIndex(const CString &strDataID);
	void GetDatasetFromAcsiNode(CDvmDataset *pDataset);
	void SetAcsiNodeByDataset(CDvmDataset *pDataset);

protected:
	void GetDatasetFromAcsiNode(CDvmDataMap *pDataMap, CDvmDataset *pDataset);
	void GetDatasetFromAcsiNode(CDvmValueMap *pValueMap, CExBaseList *pList);

	long SetAcsiNodeByDataset(CDvmDataMap *pDataMap, CDvmDataset *pDataset);
	void SetAcsiNodeByDataset(CDvmValueMap *pValueMap, CExBaseList *pList);
};

class CMmsDatasetMapTool : public CExBaseList
{
public:
	CMmsDatasetMapTool();
	virtual ~CMmsDatasetMapTool();

	void Attach(ACSI_NODE *pACSI_NODE, CDvmDeviceMap *pDeviceMap,long nDeviceIndex);
	void SetStandPath(const CString &strStandDsPath);
	void SetAcsiNodeByDataset(CDvmDataset *pDataset);
	void GetDatasetFromAcsiNode(CDvmDataset *pDataset);

	BOOL FindDataId(const CString &strRetDataID, long &nLdIndex, long &nDsIndex, long &nDaIndex);

	void SetProcedureID(const CString &strID)	{	m_strProcedureID = strID;	}
	void SetDataPath(const CString &strID)		{	m_strDataPath = strID;		}

	CDvmDataMap* FindDvmDataMapByStandID(const CString &strID);
public:
	CString m_strStandDsPath;
	ACSI_NODE *m_pACSI_NODE;  //设备的指针
	long  m_nACSI_NODE;
	CDvmDeviceMap *m_pDeviceMap;

	CString m_strProcedureID;
	CString m_strDataPath;

protected:
	void AddNew(CDvmDatasetMap *m_pDstasetMap);

public:
	void mms_Init_ACSI_NODE_Map(ACSI_NODE *pACSI_NODE, CDvmDeviceMap *pDeviceMap);
	void mms_Init_DATASET_NODE_Map(LD_DATASET_INFO *pDATASET_INFO, CDvmDatasetMap *pDatasetMap);

private:
	void mms_Init_DATA_NODE_Map(LD_DATASET_INFO *pDATASET_INFO, CDvmDataMap *pDataMap);
	void mms_Init_DATA_NODE_ValueMap(LD_DATASET_INFO *pDATASET_INFO, tagDA *pData, CDvmValueMap *pValueMap);
	tagDA* mms_FindDA_By_DataMapID(LD_DATASET_INFO *pDATASET_INFO, const CString &strDataMapID);
	tagDA* mms_FindDA_ByID(LD_DATASET_INFO *pDATASET_INFO, tagDA *pDA, const CString &strID);
	tagDA* mms_FindDA_ByID(LD_DATASET_INFO *pDATASET_INFO, const CString &strID);
	tagDA* mms_FindDA_ByID(tagDA *pDA, const CString &strID);
	tagDA* mms_FindDA_ByID(const CString &strID);

};


