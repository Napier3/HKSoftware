// MmsApi.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MmsDatasetMapTool.h"

//////////////////////////////////////////////////////////////////////////
//CMmsDvmDs_LdNode_Map
CMmsDvmDs_LdNode_Map::CMmsDvmDs_LdNode_Map()
{
	m_pACSI_NODE = NULL;  //设备的指针
	m_pLD_NODE = NULL;      //逻辑设备的指针
	m_pDataset = NULL; // 数据集指针
	m_pDstasetMap = NULL;	//数据集映射

	m_nACSI_NODE    = -1;
	m_nLD_NODE      = -1;
	m_nDATASET_INFO = -1;
}

CMmsDvmDs_LdNode_Map::~CMmsDvmDs_LdNode_Map()
{
	
}

long CMmsDvmDs_LdNode_Map::GetDataIndex(const CString &strDataID)
{
	long nDataIndex=-1, nIndex=0;

	for (nIndex=0; nIndex<m_pDataset->numData; nIndex++)
	{
#ifdef _use_mms_string
		if (strDataID == mms_string(&m_pDataset->DataSet[nIndex].DAValue.mmsName) )
#else
		if (strDataID == m_pDataset->DataSet[nIndex].DAValue.mmsName)
#endif
		{
			nDataIndex = nIndex;
			break;
		}
	}

	return nDataIndex;
}	

void CMmsDvmDs_LdNode_Map::GetDatasetFromAcsiNode(CDvmDataset *pDataset)
{
	POS pos = m_pDstasetMap->GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)m_pDstasetMap->GetNext(pos);
		GetDatasetFromAcsiNode(pDataMap, pDataset);
	}
}

void mmsmap_GetDatasetFromAcsiNode(CDvmDataMap *pDataMap, CDvmDataset *pDataset)
{
	CDvmData *pNew = new CDvmData();
	pDataset->AddNewChild(pNew);
	pNew->m_strName = pDataMap->m_strName;
	pNew->m_strID   = pDataMap->m_strID;

	tagDA *pDA = (tagDA *)pDataMap->m_dwItemData;

	if (pDA != NULL)
	{
		pNew->m_strValue = mms_GetDAValue(pDA);
		pNew->m_strDataType = pDA->DataType;
	}

	POS pos = pDataMap->GetHeadPosition();
	CDvmValueMap *pValMap = NULL;

	while (pos != NULL)
	{
		pValMap = (CDvmValueMap *)pDataMap->GetNext(pos);
		mmsmap_GetDatasetFromAcsiNode(pValMap, pNew);
	}
}

void mmsmap_GetDatasetFromAcsiNode(CDvmValueMap *pValueMap, CExBaseList *pList)
{
	CDvmValue *pNew = new CDvmValue();
	pNew->m_strName = pValueMap->m_strName;
	pNew->m_strID = pValueMap->m_strID;
	pList->AddNewChild(pNew);

	tagDA *pDA = (tagDA *)pValueMap->m_dwItemData;

	if (pDA != NULL)
	{
		pNew->m_strValue = mms_GetDAValue(pDA);
		pNew->m_strDataType = pDA->DataType;
	}

	POS pos = pValueMap->GetHeadPosition();
	CDvmValueMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmValueMap *)pValueMap->GetNext(pos);
		mmsmap_GetDatasetFromAcsiNode(pMap, pNew);
	}
}

void CMmsDvmDs_LdNode_Map::GetDatasetFromAcsiNode(CDvmDataMap *pDataMap, CDvmDataset *pDataset)
{
	mmsmap_GetDatasetFromAcsiNode(pDataMap, pDataset);
}

void CMmsDvmDs_LdNode_Map::GetDatasetFromAcsiNode(CDvmValueMap *pValueMap, CExBaseList *pList)
{
	mmsmap_GetDatasetFromAcsiNode(pValueMap, pList);
}


void CMmsDvmDs_LdNode_Map::SetAcsiNodeByDataset(CDvmDataset *pDataset)
{
	POS pos = m_pDstasetMap->GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)m_pDstasetMap->GetNext(pos);
		nCount += SetAcsiNodeByDataset(pDataMap, pDataset);
	}
}


long CMmsDvmDs_LdNode_Map::SetAcsiNodeByDataset(CDvmDataMap *pDataMap, CDvmDataset *pDataset)
{
	CDvmData *pFind = (CDvmData*)pDataset->FindByID(pDataMap->m_strID);

	if (pFind != NULL)
	{
		tagDA *pDA = (tagDA *)pDataMap->m_dwItemData;
		mms_SetByDvmData(pFind, pDA);
		return 1;
	}

	return 0;
// 	POS pos = pDataMap->GetHeadPosition();
// 	CDvmValueMap *pValMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pValMap = (CDvmValueMap *)pDataMap->GetNext(pos);
// 		GetDatasetFromAcsiNode(pValMap, pNew);
// 	}
}
// 
// void CMmsDvmDs_LdNode_Map::SetAcsiNodeByDataset(CDvmValueMap *pValueMap, CExBaseList *pList)
// {
// 	CDvmValue *pNew = new CDvmValue();
// 	pNew->m_strName = pValueMap->m_strName;
// 	pNew->m_strID = pValueMap->m_strID;
// 	pList->AddNewChild(pNew);
// 
// 	tagDA *pDA = (tagDA *)pValueMap->m_dwItemData;
// 
// 	if (pDA != NULL)
// 	{
// 		pNew->m_strValue = mms_GetDAValue(pDA);
// 		pNew->m_strDataType = pDA->DataType;
// 	}
// 
// 	POS pos = pValueMap->GetHeadPosition();
// 	CDvmValueMap *pMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pMap = (CDvmValueMap *)pValueMap->GetNext(pos);
// 		GetDatasetFromAcsiNode(pMap, pNew);
// 	}
// }

//////////////////////////////////////////////////////////////////////////
//CMmsDatasetMapTool
CMmsDatasetMapTool::CMmsDatasetMapTool()
{
	m_pACSI_NODE = NULL;
	m_pDeviceMap = NULL;
	m_nACSI_NODE = -1;
}

CMmsDatasetMapTool::~CMmsDatasetMapTool()
{

}

void CMmsDatasetMapTool::Attach(ACSI_NODE *pACSI_NODE, CDvmDeviceMap *pDeviceMap, long nDeviceIndex)
{
	m_pACSI_NODE = pACSI_NODE;
	m_pDeviceMap = pDeviceMap;
	m_nACSI_NODE = nDeviceIndex;
}

void CMmsDatasetMapTool::SetStandPath(const CString &strStandDsPath)
{
	if (m_strStandDsPath == strStandDsPath)
	{
		return;
	}

	m_strStandDsPath = strStandDsPath;
	DeleteAll();

	if (!m_pDeviceMap->m_bDvmDeviceMapExist)
	{
		return;
	}

	CString strLdeviceID, strDsID;

	long nPos = strStandDsPath.Find('$');

	if (nPos == 0)
	{
		return;
	}

	strLdeviceID = strStandDsPath.Left(nPos);
	strDsID      = strStandDsPath.Mid(nPos+1);

	CExBaseList *pList = &m_pDeviceMap->m_listDatasetMap;
	POS pos = pList->GetHeadPosition();
	CDvmDatasetMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmDatasetMap *)pList->GetNext(pos);

		if (pMap->m_strID == strDsID && pMap->m_strLdvice == strLdeviceID)
		{
			AddNew(pMap);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ds-SRC=%s  ds-MAP=%s  LD-SRC=%s  LD-MAP=%s")
                , pMap->m_strID.GetString(), pMap->m_strMapID.GetString(), pMap->m_strLdvice.GetString(), pMap->m_strLdviceMap.GetString());
		}
	}
}

void CMmsDatasetMapTool::SetAcsiNodeByDataset(CDvmDataset *pDataset)
{
	POS pos = GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)GetNext(pos);
		p->SetAcsiNodeByDataset(pDataset);
	}
}

CDvmDataMap* CMmsDatasetMapTool::FindDvmDataMapByStandID(const CString &strID)
{
	CDvmDataMap *pFind = NULL;
	POS pos = GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)GetNext(pos);
		pFind = (CDvmDataMap*)p->m_pDstasetMap->FindByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

void CMmsDatasetMapTool::GetDatasetFromAcsiNode(CDvmDataset *pDataset)
{
	if (m_strProcedureID == CMDID_ReadDataOne)
	{
		CDvmDataMap *pDataMap = FindDvmDataMapByStandID(m_strDataPath);

		if (pDataMap != NULL)
		{
			mmsmap_GetDatasetFromAcsiNode(pDataMap, pDataset);
		}

		return;
	}
	
	POS pos = GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)GetNext(pos);
		p->GetDatasetFromAcsiNode(pDataset);
	}
}

BOOL CMmsDatasetMapTool::FindDataId(const CString &strRetDataID, long &nLdIndex, long &nDsIndex, long &nDaIndex)
{
	if (GetCount() == 0)
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;

	p = (CMmsDvmDs_LdNode_Map *)GetHead();
	CString strLdID, strDsID, strDaID;
	
	if (strRetDataID.Find(p->m_pDstasetMap->m_strLdvice) > 0)
	{
		strLdID = p->m_pDstasetMap->m_strID;
	}

	if (strRetDataID.Find(p->m_pDstasetMap->m_strID)> 0)
	{
		strDsID = p->m_pDstasetMap->m_strID;
	}
	
	strDaID = strRetDataID;

	if (strLdID.GetLength() > 0)
	{
		strDaID = strDaID.Mid(strLdID.GetLength()+1);
	}

	if (strDsID.GetLength() > 0)
	{
		strDaID = strDaID.Mid(strDsID.GetLength()+1);
	}

	CDvmDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)GetNext(pos);
		pDataMap = p->m_pDstasetMap->FindMapData(strDaID);

		if (pDataMap != NULL)
		{
			nLdIndex = p->m_nLD_NODE;
			nDsIndex = p->m_nDATASET_INFO;
			nDaIndex = p->GetDataIndex(pDataMap->m_strMapID);
			break;
		}
	}

	return (nDaIndex >= 0);
}

void CMmsDatasetMapTool::AddNew(CDvmDatasetMap *pDatasetMap)
{
	LD_NODE *pLD_NODE = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	long nLdIndex=-1, nDsIndex = -1;

	for (long nLd=0; nLd<m_pACSI_NODE->numLD; nLd++)
	{
		pLD_NODE = &m_pACSI_NODE->LD[nLd];

		if (pDatasetMap->m_strLdviceMap != pLD_NODE->LDName)
		{
			continue;
		}

		for (long nDs=0; nDs < pLD_NODE->numDaSet; nDs++)
		{
			if (pDatasetMap->m_strMapID == pLD_NODE->DataInfo[nDs].DataSetID)
			{
				nLdIndex = nLd;
				nDsIndex = nDs;
				pDataset = &pLD_NODE->DataInfo[nDs];
				break;
			}
		}

		if (pDataset != NULL)
		{
			break;
		}
	}

	if (pDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_MapNotExist.GetString(), m_strStandDsPath.GetString()//_T("数据集映射关系【%s】=【%s$%s】不存在")
            , pDatasetMap->m_strLdviceMap.GetString(), pDatasetMap->m_strMapID.GetString());
		return;
	}

	CMmsDvmDs_LdNode_Map *pNew = new CMmsDvmDs_LdNode_Map();

	pNew->m_pACSI_NODE = m_pACSI_NODE; 
	pNew->m_pLD_NODE   = pLD_NODE;
	pNew->m_pDataset   = pDataset;
	pNew->m_pDstasetMap = pDatasetMap;

	pNew->m_nACSI_NODE    = m_nACSI_NODE;
	pNew->m_nLD_NODE      = nLdIndex;
	pNew->m_nDATASET_INFO = nDsIndex;

	AddNewChild(pNew);
}



//////////////////////////////////////////////////////////////////////////
tagDA* CMmsDatasetMapTool::mms_FindDA_ByID(const CString &strID)
{
	long nLdIndex = 0;
	long nDsIndex = 0;
	tagDA *pFind = NULL;

	for (nLdIndex=0; nLdIndex<m_pACSI_NODE->numLD; nLdIndex++)
	{
		for (nDsIndex=0; nDsIndex<m_pACSI_NODE->LD[nLdIndex].numDaSet; nDsIndex++)
		{
			pFind = mms_FindDA_ByID(&(m_pACSI_NODE->LD[nLdIndex].DataInfo[nDsIndex]), strID);

			if (pFind != NULL)
			{
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

tagDA* CMmsDatasetMapTool::mms_FindDA_ByID(tagDA *pDA, const CString &strID)
{
	if (strID.GetLength() == 0)
	{
		return NULL;
	}

	if (pDA == NULL)
	{
		return NULL;
	}

#ifdef _use_mms_string
	if (strID == mms_string(&pDA->DAValue.mmsName) )
#else
	if (strID == pDA->DAValue.mmsName)
#endif
	{
		return pDA;
	}

	tagDA *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		pFind = mms_FindDA_ByID(&pDA->pSubDA[nIndex], strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}


tagDA* CMmsDatasetMapTool::mms_FindDA_ByID(LD_DATASET_INFO *pDATASET_INFO, const CString &strID)
{
	if (strID.GetLength() == 0)
	{
		return NULL;
	}

	tagDA *p = NULL, *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<pDATASET_INFO->numData; nIndex++)
	{
		pFind = mms_FindDA_ByID(&pDATASET_INFO->DataSet[nIndex], strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

tagDA* CMmsDatasetMapTool::mms_FindDA_ByID(LD_DATASET_INFO *pDATASET_INFO, tagDA *pDA, const CString &strID)
{
	if (strID.GetLength() == 0)
	{
		return NULL;
	}

	tagDA *pFind = NULL;

	pFind = mms_FindDA_ByID(pDA, strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = mms_FindDA_ByID(pDATASET_INFO, strID);

	return pFind;
}


tagDA* CMmsDatasetMapTool::mms_FindDA_By_DataMapID(LD_DATASET_INFO *pDATASET_INFO, const CString &strDataMapID)
{
	tagDA *p = NULL, *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<pDATASET_INFO->numData; nIndex++)
	{
#ifdef _use_mms_string
		if (strDataMapID == mms_string(&pDATASET_INFO->DataSet[nIndex].DAValue.mmsName))
#else
		if (strDataMapID == pDATASET_INFO->DataSet[nIndex].DAValue.mmsName)
#endif
		{
			pFind = &pDATASET_INFO->DataSet[nIndex];
			break;
		}
	}

	return pFind;
}

void CMmsDatasetMapTool::mms_Init_DATA_NODE_ValueMap(LD_DATASET_INFO *pDATASET_INFO, tagDA *pData, CDvmValueMap *pValueMap)
{
	tagDA *pFind = NULL;

	if (pValueMap->m_strMapID.GetLength() > 0)
	{
		pFind = mms_FindDA_ByID(pDATASET_INFO, pData, pValueMap->m_strMapID);

		if (pFind != NULL)
		{
			pFind->dwDsMapObj = (DWORD)pValueMap;
			pValueMap->m_dwItemData = (DWORD)pFind;
		}

		if (pFind == NULL)
		{
			if (pValueMap->GetCount() == 0 && pValueMap->m_strMapID.GetLength() > 0)
			{
				pFind = mms_FindDA_ByID(pValueMap->m_strMapID);

				if (pFind != NULL)
				{
					pFind->dwDsMapObj = (DWORD)pValueMap;
					pValueMap->m_dwItemData = (DWORD)pFind;
				}
			}
		}
	}

	POS pos = pValueMap->GetHeadPosition();
	CDvmValueMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmValueMap *)pValueMap->GetNext(pos);
		mms_Init_DATA_NODE_ValueMap(pDATASET_INFO, pFind, pMap);
	}
}

//根据一个DataMap进行初始化
void CMmsDatasetMapTool::mms_Init_DATA_NODE_Map(LD_DATASET_INFO *pDATASET_INFO, CDvmDataMap *pDataMap)
{
	tagDA *pDA = NULL;

	//首先按照数据分层次映射关系查找
	pDA = mms_FindDA_By_DataMapID(pDATASET_INFO, pDataMap->m_strMapID);

	if (pDA != NULL)
	{
		pDA->dwDsMapObj = (DWORD)pDataMap;
		pDataMap->m_dwItemData = (DWORD)pDA;
	}
	else
	{
		//在Dataset数据树中查找
		pDA = mms_FindDA_ByID(pDATASET_INFO, pDataMap->m_strMapID);

		if (pDA != NULL)
		{
			pDA->dwDsMapObj = (DWORD)pDataMap;
			pDataMap->m_dwItemData = (DWORD)pDA;
		}
	}
	
	//DataMap的数值映射
	POS pos = pDataMap->GetHeadPosition();
	CDvmValueMap *pValueMap = NULL;

	while (pos != NULL)
	{
		pValueMap = (CDvmValueMap *)pDataMap->GetNext(pos);
		mms_Init_DATA_NODE_ValueMap(pDATASET_INFO, pDA, pValueMap);
	}
}

//根据数据集映射对象和本地数据集节点对象，进行初始化
void CMmsDatasetMapTool::mms_Init_DATASET_NODE_Map(LD_DATASET_INFO *pDATASET_INFO, CDvmDatasetMap *pDatasetMap)
{
	pDATASET_INFO->dwDsMapObj = (DWORD)pDatasetMap;

	if (pDatasetMap == NULL)
	{
		return;
	}

	pDatasetMap->m_dwItemData = (DWORD)pDATASET_INFO;
	CDvmDataMap *pDataMap = NULL;
	POS pos = pDatasetMap->GetHeadPosition();

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)pDatasetMap->GetNext(pos);
		mms_Init_DATA_NODE_Map(pDATASET_INFO, pDataMap);
	}
}

void CMmsDatasetMapTool::mms_Init_ACSI_NODE_Map(ACSI_NODE *pACSI_NODE, CDvmDeviceMap *pDeviceMap)
{
	if (!pDeviceMap->m_bDvmDeviceMapExist)
	{
		return;
	}

	LD_NODE *pLD_NODE = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	long nLdIndex=-1, nDsIndex = -1;
	CDvmDatasetMap *pDatasetMap = NULL;
	CString strLdeviceID, strDsID;

	//遍历每个逻辑设备
	for (long nLd=0; nLd<pACSI_NODE->numLD; nLd++)
	{
		pLD_NODE = &pACSI_NODE->LD[nLd];
		strLdeviceID = pLD_NODE->LDName;

		//遍历每个数据集，根据逻辑设备ID和数据集ID，查找相应的数据集映射对象
		for (long nDs=0; nDs < pLD_NODE->numDaSet; nDs++)
		{
			strDsID = pLD_NODE->DataInfo[nDs].DataSetID;

			CExBaseList *pListDatasetMap = &pDeviceMap->m_listDatasetMap;  // 周宏军  20200429  对于基础模板对应多个定值数据集的情况，只能映射第一个的数据集，此处进行修改
			POS pos = pListDatasetMap->GetHeadPosition();
			CDvmDatasetMap *p = NULL;

			while (pos != NULL)
			{
				p = (CDvmDatasetMap *)pListDatasetMap->GetNext(pos);

				if (p->m_strLdviceMap == strLdeviceID && p->m_strMapID == strDsID)
				{
					mms_Init_DATASET_NODE_Map(&pLD_NODE->DataInfo[nDs], p);
				}
			}


// 			pDatasetMap = pDeviceMap->FindDsMap_ByMapID(strLdeviceID, strDsID);  //周宏军  20200429
// 			mms_Init_DATASET_NODE_Map(&pLD_NODE->DataInfo[nDs], pDatasetMap);
		}
	}
}
