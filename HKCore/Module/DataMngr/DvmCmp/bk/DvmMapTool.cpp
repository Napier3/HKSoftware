//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmMapTool.cpp  CDvmMapTool


#include "stdafx.h"
#include "DvmMapTool.h"
#include "..\..\API\FileApi.h"
#include "..\..\XLanguage\XLanguageResource.h"
BOOL CDvmMapTool::g_bDvmCmdDataID = FALSE;
BOOL CDvmMapTool::g_bOnlyShowNoMap = FALSE;
//BOOL CDvmMapTool::g_bDvmCmdDataNameFull = TRUE;

CDvmMapTool::CDvmMapTool()
{
	m_hStand   = NULL;
	m_hDestCmp = NULL;

	m_pStand   = NULL;
	m_pMap = NULL;

	m_WordApp = NULL;
	m_doc     = NULL;

	m_dwCmpState = CMP_STATE_NONE;

	m_pStand = new CDvmDevice();
	m_pMap = new CDvmDevice();

	m_pDvmMapConfig = NULL;
}

CDvmMapTool::~CDvmMapTool()
{
	m_oDvmDeviceMap.DeleteAll();
	delete m_pMap;
	delete m_pStand;

	m_pMap = NULL;
	m_pStand   = NULL;

	if (m_pDvmMapConfig != NULL)
	{
		delete m_pDvmMapConfig;
		m_pDvmMapConfig = NULL;
	}
}

BOOL CDvmMapTool::OpenDvmMapConfigFile()
{
	BOOL bRet = FALSE;

	if (m_pDvmMapConfig == NULL)
	{
		m_pDvmMapConfig = new CDataGroup();
	}

	m_pDvmMapConfig->DeleteAll();

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += DVM_MAP_CONFIG_FILE;

	bRet = m_pDvmMapConfig->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		delete m_pDvmMapConfig;
		m_pDvmMapConfig = NULL;
	}

	return bRet;
}

BOOL CDvmMapTool::OpenDvmCmpFile(const CString &strFile)
{
	CString strPath;
	CString strStandDvmFile, strDestDvmFile;
	m_oDvmDeviceMap.OpenDvmMapFile(strFile);

	strPath = GetPathFromFilePathName(strFile);
	strDestDvmFile = ChangeFilePostfix(strFile, _T("xml"));//strPath + m_oDvmDeviceMap.m_strName;

	if (m_oDvmDeviceMap.m_strName.GetLength() <= 5)
	{
		strStandDvmFile = strPath;
		dvm_PopOpenDvmDlg(strStandDvmFile, AfxGetMainWnd(), CXLanguageResourceBase::g_sLangTxt_SelStdDataFile/*_T("请选择标准设备数据模型文件")*/);
	}
	else
	{
		strStandDvmFile  = strPath + m_oDvmDeviceMap.m_strName;
	}

	if (strStandDvmFile.GetLength() == 0)
	{
		return FALSE;
	}

	OepnDeviceFile(strStandDvmFile, strDestDvmFile);

	m_oDvmDeviceMap.SetMap(m_pStand, m_pMap);
	UpdateMapDevice_Stand();
	UpdateMapDvice_Map();

	m_oDvmDeviceMap.AddNullDvmMap_Stand();
	m_oDvmDeviceMap.SortDvmMap_Stand();

	return TRUE;
}

void CDvmMapTool::CmpDeviceFile(const CString &strStandDvmFile, const CString &strDestDvmFile)
{
	m_oDvmDeviceMap.DeleteAll();
	OepnDeviceFile(strStandDvmFile, strDestDvmFile);

	CmpDvmDevice();
}

void CDvmMapTool::CmpDevice(CDvmDevice *pStand, CDvmDevice *pDest)
{
	m_oDvmDeviceMap.DeleteAll();
	m_pStand = pStand;
	m_pMap = pDest;
	CmpDvmDevice();
}

void CDvmMapTool::OepnDeviceFile(const CString &strStandDvmFile, const CString &strDestDvmFile)
{
	m_pStand->DeleteAll();
	m_pMap->DeleteAll();
	
	m_pMap->OpenXmlFile(strDestDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	m_pStand->OpenXmlFile(strStandDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	m_pStand->m_strName = GetPathFileNameFromFilePathName(strStandDvmFile);
	m_pMap->m_strName = GetPathFileNameFromFilePathName(strDestDvmFile);

	m_pStand->m_strID = strStandDvmFile;
	m_pMap->m_strID   = strDestDvmFile;

	AfterOpenDeviceFile();
}

/*
<group name="模型映射时，需要映射的逻辑设备和数据集" id="">
	<group name="需要映射的逻辑设备" id="LDevicve">
		<data name="保护逻辑设备" id="PROT"/>
	</group>
	<group name="需要映射的数据集" id="Dataset">
		<data name="定值" id="dsSetting"/>
		<data name="压板" id="Ena"/>
		<data name="遥测" id="Ain"/>
		<data name="遥信" id="Din"/>
		<data name="保护动作信息" id="TripInfo"/>
		<data name="保护告警" id="Warnging"/>
		<data name="遥控" id="Dout"/>
		<data name="装置参数" id="Parameter"/>
	</group>
</group>
*/

//打开模型文件后，根据配置，删除不必对的数据集和逻辑设备
void CDvmMapTool::AfterOpenDeviceFile()
{
	OpenDvmMapConfigFile();

	if (m_pDvmMapConfig == NULL)
	{
		return;
	}

	CDataGroup *pLDeviceConfig = (CDataGroup *)m_pDvmMapConfig->FindByID(DVM_MAP_CONFIG_LDEVICE);

	if (pLDeviceConfig == NULL)
	{
		return;
	}
	
	RemoveLdevice(pLDeviceConfig, m_pStand);
	//目标模型文件中，不移除不需要的逻辑设备和数据集，以便标准文件数据集与不同的数据集建立映射
	//RemoveLdevice(pLDeviceConfig, m_pMap);
}

void CDvmMapTool::RemoveLdevice(CDataGroup *pLDeviceConfig, CDvmDevice *pDvmDevice)
{
	if (pLDeviceConfig == NULL)
	{
		return;
	}

	if (m_pDvmMapConfig == NULL)
	{
		return;
	}

	POS pos = pDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pLDevice = NULL;
	CDataGroup *pDatasetConfig = (CDataGroup *)m_pDvmMapConfig->FindByID(DVM_MAP_CONFIG_DATASET);
	//CExBaseList oList;

	while (pos != NULL)
	{
		pLDevice = (CDvmLogicDevice *)pDvmDevice->GetNext(pos);

		if (!IsIDExist(pLDevice->m_strID, pLDeviceConfig))
		{
			//oList.AddNewChild(pLDevice);
			pDvmDevice->Delete(pLDevice);
			continue;
		}

		RemoveDataset(pDatasetConfig, pLDevice);
	}

	//oList.DeleteAll();
}

void CDvmMapTool::RemoveDataset(CDataGroup *pDatasetConfig, CDvmLogicDevice *pLDevice)
{
	if (pDatasetConfig == NULL)
	{
		return;
	}

	POS pos = pLDevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLDevice->GetNext(pos);

		if (!IsIDExist(pDataset->m_strID, pDatasetConfig))
		{
			pLDevice->Delete(pDataset);
			continue;
		}
	}

}

BOOL CDvmMapTool::IsIDExist(const CString &strID, CDataGroup *pGroup)
{
	if (pGroup == NULL)
	{
		return TRUE;   //默认全存在
	}

	POS pos = pGroup->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pGroup->GetNext(pos);

		if (strID.Find(pData->m_strID) >= 0)
		{
			return TRUE;
		}

		if (pData->m_strID.Find(strID) >= 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

//////////////////////////////////////////////////////////////////////////
//更新映射关系
void CDvmMapTool::UpdateMapDevice_Stand()
{
	CDvmLDeviceMap *pLDviceMap = NULL;
	POS pos = m_oDvmDeviceMap.GetHeadPosition();
	CDvmLogicDevice *pStand = NULL;

	while (pos != NULL)
	{
		pLDviceMap = (CDvmLDeviceMap*)m_oDvmDeviceMap.GetNext(pos);
		pStand = (CDvmLogicDevice *)m_pStand->FindByID(pLDviceMap->m_strID);

		if (pStand == NULL)
		{
			m_oDvmDeviceMap.Delete(pLDviceMap);
		}
		else
		{
			UpdateMapLdevice_Stand(pLDviceMap, pStand);
		}
	}

}

void CDvmMapTool::UpdateMapLdevice_Stand(CDvmLDeviceMap *pDvmMap, CDvmLogicDevice *pStandLdevice)
{
	pDvmMap->SetStand0(pStandLdevice);
	CDvmDatasetMap *pMap = NULL;
	POS pos = pDvmMap->GetHeadPosition();
	CDvmDataset *pStand = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmDatasetMap*)pDvmMap->GetNext(pos);
		pStand = (CDvmDataset *)pStandLdevice->FindByID(pMap->m_strID);

		if (pStand == NULL)
		{
			pDvmMap->Delete(pMap);
		}
		else
		{
			UpdateMapDataset_Stand(pMap, pStand);
		}
	}
}

void CDvmMapTool::UpdateMapDataset_Stand(CDvmDatasetMap *pDvmMap, CDvmDataset *pStandDataset)
{
	pDvmMap->SetStand0(pStandDataset);
	CDvmDataMap *pMap = NULL;
	POS pos = pDvmMap->GetHeadPosition();
	CDvmData *pStand = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmDataMap*)pDvmMap->GetNext(pos);
		pStand = (CDvmData *)pStandDataset->FindByID(pMap->m_strID);

		if (pStand == NULL)
		{
			pDvmMap->Delete(pMap);
		}
		else
		{
			UpdateMapData_StandData(pMap, pStand);
		}
	}
}

void CDvmMapTool::UpdateMapData_StandData(CDvmDataMap *pDvmMap, CDvmData *pStandData)
{
	pDvmMap->SetStand0(pStandData);
	CDvmValueMap *pMap = NULL;
	POS pos = pDvmMap->GetHeadPosition();
	CDvmValue *pStand = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmValueMap*)pDvmMap->GetNext(pos);
		pStand = (CDvmValue *)pStandData->FindByID(pMap->m_strID);

		if (pStand == NULL)
		{
			pDvmMap->Delete(pMap);
		}
		else
		{
			UpdateMapValue_Stand(pMap, pStand);
		}
	}
}

void CDvmMapTool::UpdateMapValue_Stand(CDvmValueMap *pDvmMap, CExBaseList *pParentDestList)
{
	pDvmMap->SetStand0(pParentDestList);
	CDvmValueMap *pMap = NULL;
	POS pos = pDvmMap->GetHeadPosition();
	CDvmValue *pStand = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmValueMap*)pDvmMap->GetNext(pos);
		pStand = (CDvmValue *)pParentDestList->FindByID(pMap->m_strID);

		if (pStand == NULL)
		{
			pDvmMap->Delete(pMap);
		}
		else
		{
			UpdateMapValue_Stand(pMap, pStand);
		}
	}
}

void CDvmMapTool::UpdateMapDvice_Map()
{
	POS pos = m_oDvmDeviceMap.GetHeadPosition();
	CDvmLDeviceMap *pLdeviceMap = NULL;

	while (pos != NULL)
	{
		pLdeviceMap = (CDvmLDeviceMap *)m_oDvmDeviceMap.GetNext(pos);
		UpdateMapLdevice_Map(pLdeviceMap);
	}
}


void CDvmMapTool::UpdateMapLdevice_Map(CDvmLDeviceMap *pLDviceMap)
{
	POS pos = pLDviceMap->GetHeadPosition();
	CDvmDatasetMap *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)pLDviceMap->GetNext(pos);
		UpdateMapDataset_Map(p);
	}
}

void CDvmMapTool::UpdateMapDataset_Map(CDvmDatasetMap *pDatasetMap)
{
	POS pos = pDatasetMap->GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	CString strPath;

	if (pDatasetMap->m_strMapID.GetLength() == 0)
	{
		return;
	}

	strPath.Format(_T("%s$%s"), pDatasetMap->m_strLdviceMap, pDatasetMap->m_strMapID);
	CExBaseList listDataset;
	m_pMap->SelectDatas(strPath, listDataset, _T("$"));

	if (listDataset.GetCount() == 0)
	{
		pDatasetMap->m_strLdviceMap.Empty();
		pDatasetMap->SetMap0(NULL);
		return;
	}
	
	if (listDataset.GetCount() > 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceBase::g_sLangTxt_DataSetNoOnly/*_T("数据集【%s】不唯一")*/, strPath);
	}

	CDvmDataset *pDestDataset = (CDvmDataset*)listDataset.GetHead();
	listDataset.RemoveAll();
	pDatasetMap->SetMap0(pDestDataset);

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)pDatasetMap->GetNext(pos);
		UpdateMapData_Map_DestDataset(pDataMap, pDestDataset);
	}

	pDatasetMap->InitAfterRead();
}

void CDvmMapTool::UpdateMapData_Map_DestDataset(CDvmDataMap *pDataMap, CDvmDataset *pDestDataset)
{
	CDvmData *pData = (CDvmData*)pDestDataset->FindByID(pDataMap->m_strMapID);
	pDataMap->SetMap0(pData);

	POS pos = pDataMap->GetHeadPosition();
	CDvmValueMap *pValueMap = NULL;

	while (pos != NULL)
	{
		pValueMap = (CDvmValueMap *)pDataMap->GetNext(pos);
		UpdateMapValue_Map_Dest(pValueMap, pData, pDestDataset);;
	}
}


void CDvmMapTool::UpdateMapValue_Map_Dest(CDvmValueMap *pValueMap, CExBaseList *pParentDestList, CDvmDataset *pDestDataset)
{
	//无子对象
	if (pValueMap->GetCount() == 0)
	{
		//已经更新了映射对象
		if(pValueMap->m_pMap != NULL)
		{
			return;
		}

		//无映射对象
		if (pValueMap->m_strMapID.GetLength() == 0)
		{
			return;
		}

		CDvmValue *pFind = UpdateMapValue_FindValue(pValueMap->m_strMapID, pParentDestList, pDestDataset);
		pValueMap->SetMap0(pFind);
	}
	else
	{
		CDvmValue *pFind = UpdateMapValue_FindValue(pValueMap->m_strMapID, pParentDestList, pDestDataset);
		pValueMap->SetMap0(pFind);

		POS pos = pValueMap->GetHeadPosition();
		CDvmValueMap *p = NULL;

		while (pos != NULL)
		{
			p = (CDvmValueMap *)pValueMap->GetNext(pos);
			UpdateMapValue_Map_Dest(p, pFind, pDestDataset);
		}
	}
	
}

CDvmValue* CDvmMapTool::UpdateMapValue_FindValue(const CString &strID, CExBaseList *pList, CDvmDataset *pDestDataset)
{
	if (strID.GetLength() == 0)
	{
		return NULL;
	}

	CDvmValue *pFind = NULL;

	if (pList != NULL)
	{
		pFind = (CDvmValue*)pList->FindByID(strID);
	}

	if (pFind == NULL)
	{
		CExBaseList oList;
		if ( pDestDataset->QueryByID(strID, oList)> 0 )
		{
			pFind = (CDvmValue *)oList.GetHead();
		}

		oList.RemoveAll();
	}

	if (pFind == NULL)
	{
		CExBaseList oList;

		if ( m_pMap->QueryByID(strID, oList)> 0 )
		{
			pFind = (CDvmValue *)oList.GetHead();
		}

		oList.RemoveAll();
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////



void CDvmMapTool::CmpDvmDevice()
{
	OpenKeyDbFile();
	m_oDvmDeviceMap.DeleteAll();

	CDvmLogicDevice *pStandLdevice = NULL;
	CDvmLDeviceMap *pLdeviceMap = NULL;

	m_oDvmDeviceMap.SetMap(m_pStand, m_pMap);  //建立CDvmDevice这一层级的映射关系
	m_oDvmDeviceMap.AddNullDvmMap_Stand();

	POS pos = m_oDvmDeviceMap.GetHeadPosition();

	while (pos != NULL)
	{
		pLdeviceMap = (CDvmLDeviceMap *)m_oDvmDeviceMap.GetNext(pos);
		CmpDvmLdevice_Dest_StandMap(m_pMap, pLdeviceMap);;
	}
	
	m_oDvmDeviceMap.AddNullDvmMap_Stand();
	m_oDvmDeviceMap.SortDvmMap_Stand();
	dvmmap_SetDvmMapModifiedFlag(&m_oDvmDeviceMap);
	m_oDvmDeviceMap.CountErrMapCount();
	//遍历m_pStand中的每一个Ldevice，与m_pMap比较
/*
	POS pos = m_pStand->GetHeadPosition();

	while (pos != NULL)
	{
		pStandLdevice = (CDvmLogicDevice *)m_pStand->GetNext(pos);
		CmpDvmLdevice(m_pMap, pStandLdevice);
	}
*/
// 	m_oDvmDeviceMap.SortDvmMap_Stand();
}
// 
// void CDvmMapTool::CmpDvmDevice_DsMap(CDvmDevice *pStand, CDvmDevice *pDestCmp)
// {
// 	m_dwCmpState = CMP_STATE_DATASET;
// 
// 	OpenKeyDbFile();
// 	DeleteAll();
// 
// 	m_pStand   = pStand;
// 	m_pMap = pDestCmp;
// 
// 	POS pos = pDestCmp->GetHeadPosition();
// 	CDvmLogicDevice *pLdevice = NULL;
// 
// 	//遍历pDestCmp中的每一个Ldevice，与pStand比较
// 	while (pos != NULL)
// 	{
// 		pLdevice = (CDvmLogicDevice *)pDestCmp->GetNext(pos);
// 		CmpDvmLdevice(pStand, pLdevice);
// 	}
// 
// 
// }
// void CDvmMapTool::CmpDvmDevice_DsDataMap()
// {
// 	m_dwCmpState = CMP_STATE_DATA;
// 
// 	//处理没有定义的Ldevcie
// 	AddOtherCmpObj_Stand(m_pStand, this);
// 
// 	//打开映射关系文件，根据映射关系更新比较
// 	OpenDvmCmpMapFile();
// 	InitByDvmMap();
// 	AddOtherCmpObj_Stand();
// 	SortByStand();
// 
// 	m_dwCmpState = CMP_STATE_NONE;
// }
// 
// void CDvmMapTool::SortByStand()
// {
// 	POS pos = GetHeadPosition();
// 	CDvmCmpObj *pLdCmp = NULL;
// 	POS posDsCmp = NULL;
// 	CDvmCmpObj *pDsCmp;
// 	CDvmDatasetMap *pDsMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		//遍历ldevice的比较对象
// 		pLdCmp = (CDvmCmpObj *)GetNext(pos);
// 
// 		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		//遍历逻辑设备比较对象
// 		posDsCmp = pLdCmp->GetHeadPosition();
// 
// 		while (posDsCmp != NULL)
// 		{
// 			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);
// 
// 			if (pDsCmp->m_pStand == NULL)
// 			{
// 				continue;
// 			}
// 
// 			SortByStand(pDsCmp, (CDvmDataset*)pDsCmp->m_pStand, (CDvmDataset*)pDsCmp->m_pMap);
// 		}
// 	}
// }

CString CDvmMapTool::SaveDvmCmpMapFile()
{
	//shaolei 20210325 修改保存的映射文件的命名方式
	CString strFile, strPath;
	strPath = m_pMap->m_strID;
	strPath = GetPathFromFilePathName(strPath);
	strFile = m_pStand->m_strName.Left(m_pStand->m_strName.GetLength() - 4);
	strFile = strFile + _T("_") + m_pMap->m_strName.Left(m_pMap->m_strName.GetLength() - 4) +_T(".") + g_strDvmDataMapFilePostfix;
	strFile = strPath + strFile;
	m_oDvmDeviceMap.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	dvmmap_SetDvmMapModifiedFlag(&m_oDvmDeviceMap, FALSE);

	return strFile;
}

void CDvmMapTool::OpenDvmCmpMapFile()
{
	CString strFile;
	strFile = m_pMap->m_strID;
	strFile = ChangeFilePostfix(strFile, g_strDvmDataMapFilePostfix);

	m_oDvmDeviceMap.DeleteAll();
	m_oDvmDeviceMap.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CDvmMapTool::OpenDvmCmpRptExportFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("DvmMapReportConfig.xml");

	m_oRptDstaset.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CDvmLogicDevice* CDvmMapTool::FindCmpDvmLdevice(CDvmDevice *pDestDvmDevice, CDvmLogicDevice *pStandLdevice)
{
	POS pos = pDestDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;
	CDvmMapObject *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;

	while (pos != NULL)
	{
		//遍历pStand的每一个Ldevice，判断是否可以与pDestCmpLdevice进行比较
		pLdevice = (CDvmLogicDevice *)pDestDvmDevice->GetNext(pos);
		nCmpRate = CanCmpDvmLdevice(pStandLdevice, pLdevice);

		if (nCmpRate > 0)
		{
			listCmp.AddTail(dvmmap_NewMpObject(pStandLdevice, pLdevice, nCmpRate));
		}
	}

	//获取相似程度最高的
	CDvmMapObject *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmLogicDevice*)pCmpObj->m_pMap;
	}
}


long CDvmMapTool::CanCmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpLdevice);

	if (nCmp > 0)
	{
		return nCmp;
	}

	//比较逻辑设备的关键字
	long nKeyStand = GetLdeviceKey(pStand->m_strID);
	long nKeyDestCmp = GetLdeviceKey(pDestCmpLdevice->m_strID);

	if ((nKeyDestCmp == nKeyStand) && (nKeyStand != -1))
	{
		return 50;
	}
	else
	{
		return 0;
	}
}
// 
// CDvmLDeviceMap* CDvmMapTool::CmpDvmLdevice(CDvmDevice *pDestDvmDevice, CDvmLogicDevice *pStandLdevice)
// {
// 	POS pos = pDestDvmDevice->GetHeadPosition();
// 	CDvmLogicDevice *pLdevice = NULL;
// 
// 	//在pDestDvmDevice中找与pDestCmpLdevice相匹配的pLdevice
// 	pLdevice = FindCmpDvmLdevice(pDestDvmDevice, pStandLdevice);
// 	CDvmLDeviceMap *pLdeviceMap = NULL;
// 
// 	if (pLdevice != NULL)
// 	{
// 		pLdeviceMap = m_oDvmDeviceMap.AddDvmMap(pStandLdevice, pLdevice);
// 		pLdeviceMap = CmpDvmLdevice(pLdeviceMap, pStandLdevice, pLdevice);
// 	}
// 
// 	return pLdeviceMap;
// }


void CDvmMapTool::CmpDvmLdevice_Dest_StandMap(CDvmDevice *pDestDvmDevice, CDvmLDeviceMap *pStandLdeviceMap)
{
	POS pos = pDestDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;
	CDvmLogicDevice *pStandLdevice = (CDvmLogicDevice*)pStandLdeviceMap->m_pStand;

	//在pDestDvmDevice中找与pDestCmpLdevice相匹配的pLdevice
	pLdevice = FindCmpDvmLdevice(pDestDvmDevice, pStandLdevice);

	if (pLdevice != NULL)
	{
		//CmpDvmLdevice_Map_Dest(pStandLdeviceMap, pLdevice, TRUE);
		CmpDvmLdevice_Map_Dest(pStandLdeviceMap, pLdevice, FALSE);
	}
}

//此处可以考虑仅保留匹配度最高的，待讨论修改  //20210507
//shaolei  20220209 修改为只保留匹配度最高的，不考虑一对多的情况
void CDvmMapTool::CmpDvmLdevice_Map_Dest(CDvmLDeviceMap *pLDviceMap, CDvmLogicDevice *pDestCmpLdevice, BOOL bFullCmp)
{
	CDvmDatasetMap *p = NULL;
	
	//比较数据集
	POS pos = pLDviceMap->GetHeadPosition();
	CDvmDataset *pDvmDataset = NULL;
	CDvmDatasetMap *pDvmDatasetMap = NULL;
	CDvmDataset *pStandDataset = NULL;
	long nCmpRate = 0;
	CExBaseList listNewMap;
	long nMaxCmpRate = 0;   //记录最大的匹配度

	while (pos!= NULL)
	{
		pDvmDatasetMap = (CDvmDatasetMap *)pLDviceMap->GetNext(pos);
		pStandDataset = (CDvmDataset *)pDvmDatasetMap->m_pStand;
		POS posDs = pDestCmpLdevice->GetHeadPosition();
		nMaxCmpRate = 0;

		while (posDs != NULL)
		{
			pDvmDataset = (CDvmDataset *)pDestCmpLdevice->GetNext(posDs);
			nCmpRate = CanCmpDvmDataset(pDvmDataset, pStandDataset);

			if (nCmpRate == 0)
			{
				continue;
			}

			if (pDvmDataset->m_dwReserved == 1 && nCmpRate != 100)
			{
				continue;
			}
				
			if (pDvmDatasetMap->m_pMap == NULL)
			{
				//刚开始的时候，创建了全部的空的映射，所以对于第一个对象，就不要创建
				pDvmDatasetMap->m_bAddMapFindByStand = TRUE;
				pDvmDatasetMap->SetMap0(pDvmDataset);
				CmpDvmDataset(pDvmDatasetMap, bFullCmp);
				pDvmDatasetMap->m_strLdviceMap = pDestCmpLdevice->m_strID;
				pDvmDatasetMap->InitAfterRead();
			}
			else if (nCmpRate > nMaxCmpRate)
			{
				//如果匹配度大，应该删除原来的匹配关系，并建立新的匹配关系
				//即删除pDvmDatasetMap
				ClearDatasetMap(pDvmDatasetMap, pStandDataset);   //先清空所有映射
				pDvmDatasetMap->SetMap0(pDvmDataset);
				pDvmDatasetMap->AddNullDvmMap_Stand();

				CDvmDatasetMap *pNewDsMap = (CDvmDatasetMap*)pLDviceMap->FindDvmMapObj(pStandDataset, pDvmDataset);

				if (pNewDsMap == NULL)
				{
					pNewDsMap = pLDviceMap->AddDvmMap(pStandDataset, pDvmDataset);
					//listNewMap.AddTail(pNewDsMap);
					//pLDviceMap->Remove(pNewDsMap);
				}

				//对于一对多的映射关系，因为是空的数据集映射，所以要增加新的映射数据对象
				//pNewDsMap->m_bAddMapFindByStand = FALSE;
				CmpDvmDataset(pNewDsMap, bFullCmp);
				pNewDsMap->m_strLdviceMap = pDestCmpLdevice->m_strID;

				if(nCmpRate == 100 
					&& (pStandDataset->m_strID.Find(_T("dsSetting")) < 0 && pStandDataset->m_strID.Find(_T("dsRelayEna")) < 0) )
					break;
			}
 			else if (pStandDataset->m_strID.Find(_T("dsSetting")) >= 0 || pStandDataset->m_strID.Find(_T("dsRelayEna")) >= 0)
 			{
 				//定值和压板数据集，保留一对多
 				CDvmDatasetMap *pAdd = pLDviceMap->AddDvmMap(pDvmDatasetMap, pDvmDataset, TRUE);
				pLDviceMap->Remove(pAdd);
				listNewMap.AddTail(pAdd);
 				pAdd->m_strMapName = pDvmDataset->m_strName;
 				pAdd->m_strMapID   = pDvmDataset->m_strID;
 				pAdd->m_strLdviceMap = pDestCmpLdevice->m_strID;
 				pAdd->AddNullDvmMap_Stand();
 				CmpDvmDataset(pAdd, FALSE);
 			}
			else
				continue;

			if (nCmpRate > nMaxCmpRate)
			{
				nMaxCmpRate = nCmpRate;
			}
		}
	}

	pLDviceMap->AppendEx(listNewMap);
	listNewMap.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

CDvmDataset* CDvmMapTool::FindCmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset)
{
	POS pos = pStand->GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;

	while (pos != NULL)
	{
		//遍历pStand的每一个Dataset，判断是否可以与pDestCmpDataset进行比较
		pDataset = (CDvmDataset *)pStand->GetNext(pos);
		nCmpRate = CanCmpDvmDataset(pDataset, pDestCmpDataset);

		if (nCmpRate > 0)
		{
			listCmp.AddTail(dvmmap_NewMpObject(pDataset, pDestCmpDataset, nCmpRate));
		}
	}

	//获取相似程度最高的
	CDvmMapObject *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmDataset*)pCmpObj->m_pMap;
	}
}

long CDvmMapTool::CanCmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpDataset);

	if (nCmp > 0)
	{
		return nCmp;
	}

	//比较数据集的关键字
	long nKeyStand = GetDatasetKey(pStand->m_strID);
	long nKeyDestCmp = GetDatasetKey(pDestCmpDataset->m_strID);

	if ((nKeyDestCmp == nKeyStand) && (nKeyStand != -1))
	{
		return 50;
	}
	else
	{
		return 0;
	}
}

CDvmDatasetMap* CDvmMapTool::CmpDvmDataset(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, BOOL bFullCmp)
{
	if (g_bDvmCmdDataID == 1)
	{
		//比较id
		CmpDvmDataset_ID(pDatasetMap, pStand, pDestCmpDataset);
	}
	else
	{
		//比较数据集数据：根据名称比较
		CmpDvmDataset_Name(pDatasetMap, pStand, pDestCmpDataset, bFullCmp);

		if (g_bDvmCmdDataNameFull == 0)
		{//全名称匹配，不执行智能化匹配
			//XMatch
			XMatchDataset(pStand, pDestCmpDataset);

			//比较数据集的数据
			POS pos = pStand->GetHeadPosition();
			CDvmData *pStandDvmData = NULL;

			while (pos!= NULL)
			{
				pStandDvmData = (CDvmData *)pStand->GetNext(pos);

				if (pStandDvmData->m_dwReserved == 1)
				{
					continue;
				}

				CmpDvmData(pDestCmpDataset, pStandDvmData, pDatasetMap);
			}
		}

	}

	//pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_Stand(pStand, pDvmCmpObj);

	//按照标准进行排序
	//SortByStand(pDvmCmpObj, pStand, pDestCmpDataset);

	return pDatasetMap;
}


void CDvmMapTool::CmpDvmDataset(CDvmDatasetMap *pDatasetMap, BOOL bFullCmp)
{
	CDvmDataset *pStand = (CDvmDataset*)pDatasetMap->m_pStand;
	CDvmDataset *pDestCmpDataset = (CDvmDataset*)pDatasetMap->m_pMap;

	ASSERT (pStand != NULL && pDestCmpDataset != NULL);

	if (pStand == NULL && pDestCmpDataset == NULL)
	{
		return;
	}

	CmpDvmDataset(pDatasetMap, pStand, pDestCmpDataset, bFullCmp);
}

// 
// void CDvmMapTool::SortByStand(CDvmCmpObj *pDvmCmpDataset, CDvmDataset *pDsStand, CDvmDataset *pDsDest)
// {
// 	POS pos = pDsStand->GetHeadPosition();
// 	CDvmData *pDvmData = NULL;
// 	CDvmCmpObj *pDataCmp = NULL;
// 	CExBaseList listTemp;
// 	long nIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pDvmData = (CDvmData *)pDsStand->GetNext(pos);
// 		pDataCmp = FindByStand(pDvmCmpDataset, pDvmData);
// 
// 		if (pDataCmp != NULL)
// 		{
// 			pDataCmp->m_nStandIndex = nIndex;
// 			listTemp.AddTail(pDataCmp);
// 			nIndex++;
// 		}
// 	}
// 
// 	listTemp.Append(pDvmCmpDataset);
// 	pDvmCmpDataset->RemoveAll();
// 	pDvmCmpDataset->Append(listTemp);
// 	listTemp.RemoveAll();
// 
// 	pos = pDvmCmpDataset->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pDataCmp = (CDvmCmpObj *)pDvmCmpDataset->GetNext(pos);
// 
// 		if (pDataCmp->m_pMap != NULL)
// 		{
// 			pDataCmp->m_nDestIndex = pDsDest->FindIndex(pDataCmp->m_pMap);
// 		}
// 	}
// }
// 
// CDvmCmpObj* CDvmMapTool::FindByStand(CDvmCmpObj *pDvmCmpDataset, CDvmData *pDvmData)
// {
// 	CDvmCmpObj *p = NULL;
// 	CDvmCmpObj *pFind = NULL;
// 	POS pos = pDvmCmpDataset->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmCmpObj *)pDvmCmpDataset->GetNext(pos);
// 
// 		if (p->m_pStand == pDvmData)
// 		{
// 			pFind = p;
// 			break;
// 		}
// 	}
// 
// 	pDvmCmpDataset->Remove(pFind);
// 
// 	return pFind;
// }

CDvmData* CDvmMapTool::FindDvmData_Name(CDvmDataset *pDataset, CDvmData *pStandDvmData, long nStandIdKey, BOOL bFullCmp)
{
	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	CExBaseObject *pFirstFind = NULL;
	long nDestKey = -1;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->m_strName == pStandDvmData->m_strName)
		{
			//跳过跳闸矩阵：一边是跳闸矩阵，一边是定值。有可能存在名称全匹配，不应建立映射关系  shaolei 20220512
			if (p->m_strID.Find(_T("OUTMATR")) >= 0 && pStandDvmData->m_strID.Find(_T("OUTMATR")) < 0)
			{
				continue;
			}

			if (p->m_dwReserved != 1)
			{
				if (g_bDvmCmdDataNameFull == 1)
				{
					if (pFirstFind == NULL)
					{
						pFirstFind = p;
					}

					nDestKey = GetCmpFullNameIdKey(p->m_strID);

					if (nDestKey == nStandIdKey)
					{
						pFind = p;
						break;
					}
				}
				else
				{
					pFind = p;
					break;
				}
				
			}
		}
	}

	if (pFind == NULL && (!bFullCmp))
	{
		pFind = pFirstFind;
	}

	return (CDvmData*)pFind;
}

CDvmDatasetMap* CDvmMapTool::CmpDvmDataset_Name(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, BOOL bFullCmp)
{
	if (g_bDvmCmdDataID == 1)
	{
		return pDatasetMap;
	}

	//比较数据集的数据
	POS pos = pStand->GetHeadPosition();
	CDvmData *pStandDvmData = NULL;
	CDvmData *pDestDvmData = NULL;
	long nStandIdKey = -1;

	while (pos!= NULL)
	{
		pStandDvmData = (CDvmData *)pStand->GetNext(pos);

		if (pStandDvmData->m_dwReserved == 1)
		{
			continue;
		}

		nStandIdKey = GetCmpFullNameIdKey(pStandDvmData->m_strID);
		pDestDvmData = FindDvmData_Name(pDestCmpDataset, pStandDvmData, nStandIdKey, bFullCmp);

		if (pDestDvmData != NULL)
		{
			CDvmDataMap *pMap = pDatasetMap->AddDvmMap(pStandDvmData, pDestDvmData);
			CmpDvmData(pStandDvmData, pDestDvmData, pMap);
		}
	}

	return pDatasetMap;
}

void CDvmMapTool::CmpDvmDataset_ID(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStandDataset, CDvmDataset *pDestCmpDataset)
{
	//比较数据集的数据
	POS pos = pStandDataset->GetHeadPosition();
	CDvmData *pStandDvmData = NULL;
	CDvmData *pFind = NULL;

	while (pos!= NULL)
	{
		pStandDvmData = (CDvmData *)pStandDataset->GetNext(pos);

		if (pStandDvmData->m_dwReserved == 1)
		{
			continue;
		}

		pFind = (CDvmData *)pDestCmpDataset->FindByID(pStandDvmData->m_strID);

		if (pFind != NULL)
		{
			if (pFind->m_dwReserved == 1)
			{
				continue;
			}

			CDvmDataMap *pDataMap = pDatasetMap->AddDvmMap(pStandDvmData, pFind);
			pFind->m_dwReserved = 1;
			pStandDvmData->m_dwReserved = 1;
			CmpDvmData(pStandDvmData, pFind, pDataMap);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
CDvmData* CDvmMapTool::FindCmpDvmData(CDvmDataset *pDsDest, CDvmData *pStandData, CDvmDatasetMap *pDatasetMap)
{
	POS pos = pDsDest->GetHeadPosition();
	CDvmData *pData = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;

	if (g_bDvmCmdDataID == 1)
	{
		while (pos != NULL)
		{
			//遍历pStand的每一个Data，判断是否可以与pDestCmpData进行比较
			pData = (CDvmData *)pDsDest->GetNext(pos);

			if (pData->m_dwReserved == 1)
			{
				continue;
			}

// 			if (pDatasetMap->IsInChild_Stand(pData))
// 			{
// 				continue;
// 			}

			nCmpRate = CanCmpDvmObject_ID(pData, pStandData);

			if (nCmpRate > 0)
			{
				listCmp.AddTail(dvmmap_NewMpObject(pStandData, pData, nCmpRate));
			}
		}
	}
	//XMastch获取
	//if (listCmp.GetCount() == 0)
	else //g_bDvmCmdDataID == 0
	{
		CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
		POS pos = pList->GetHeadPosition();
		CXMatchObject *pXMatch = NULL;
		CExBaseObject *pMatchRef = NULL;

		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)pList->GetNext(pos);

			if (pXMatch->m_pRefObject == pStandData)
			{
				POS posMatch = pXMatch->m_listMacthRefObject.GetHeadPosition();
				
				while (posMatch != NULL)
				{
					pMatchRef = pXMatch->m_listMacthRefObject.GetNext(posMatch);

					if (pMatchRef->m_dwReserved == 1)
					{
						continue;;
					}

					//跳过跳闸矩阵：一边是跳闸矩阵，一边是定值。有可能存在名称全匹配，不应建立映射关系  shaolei 20220512
					if (pMatchRef->m_strID.Find(_T("OUTMATR")) >= 0 && pStandData->m_strID.Find(_T("OUTMATR")) < 0)
					{
						continue;
					}

					listCmp.AddTail(dvmmap_NewMpObject(pStandData, pMatchRef, 100));
// 					CDvmCmpObj *pNew = new CDvmCmpObj(pMatchRef, pStandData);
// 					pNew->m_nCmpRate = 100;
// 					listCmp.AddTail(pNew);
				}
			}
		}
	}

	//获取相似程度最高的
	CDvmMapObject *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmData*)pCmpObj->m_pMap;
	}
}

long CDvmMapTool::CanCmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData)
{
	if (pStand->m_dwReserved == 1 || pDestCmpData->m_dwReserved == 1)
	{
		return 0;
	}

	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpData);

	return nCmp;
}

CDvmDataMap* CDvmMapTool::CmpDvmData(CDvmDataset *pDestDataset, CDvmData *pStandData, CDvmDatasetMap *pDatasetMap)
{
	POS pos = pDestDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmDataMap *pDvmCmpObj = NULL;

	//for debug
// 	if (pStandData->m_strName == _T("接地变零序过流Ⅱ段定值") || pStandData->m_strName == _T("接地变零序过流Ⅱ段时间"))
// 	{
// 		int x = 0;
// 	}

	//查找可以与pDestCmpData比较的data
	pData = FindCmpDvmData(pDestDataset, pStandData, pDatasetMap);

	if (pData != NULL)
	{
		pDvmCmpObj = pDatasetMap->AddDvmMap(pStandData, pData);
		CmpDvmData(pStandData, pData, pDvmCmpObj);
	}

	return pDvmCmpObj;
}

CDvmDataMap* CDvmMapTool::CmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData, CDvmDataMap *pDataMap)
{
	pStand->m_dwReserved = 1;
	pDestCmpData->m_dwReserved = 1;

	//比较数据的属性
	POS pos = pStand->GetHeadPosition();
	CDvmValue *pDvmValue = NULL;
	CDvmValueMap *pMap = NULL;

	while (pos!= NULL)
	{
		pDvmValue = (CDvmValue*)pStand->GetNext(pos);
		CmpDvmValue(pDestCmpData, pDvmValue, pDataMap);
	}

	return pDataMap;
}

void CDvmMapTool::UpdateDvmDataMap(CDvmDataMap *pDataMap, CDvmData *pDestCmpData)
{
	pDestCmpData->m_dwReserved = 1;
	pDestCmpData->m_pDvmMapObj = pDataMap;
	pDataMap->SetMap0(pDestCmpData);

	pDataMap->StringCmp();

	//比较数据的属性
	POS pos = pDataMap->GetHeadPosition();
	CDvmValue *pDvmValue = NULL;
	CDvmValueMap *pMap = NULL;

	while (pos!= NULL)
	{
		pMap = (CDvmValueMap *)pDataMap->GetNext(pos);
		
		//查找可以与pDestCmpValue比较的Value
		pDvmValue = FindCmpDvmValue(pDestCmpData, (CDvmValue*)pMap->m_pStand);

		if (pDvmValue != NULL)
		{
			UpdateDvmValueMap(pMap, pDvmValue);
		}
	}
}

void CDvmMapTool::UpdateDvmDataMap(CDvmData *pStandData, CDvmData *pDestCmpData)
{
	CDvmDataset *pStandDataset = (CDvmDataset*)pStandData->GetParent();
	CDvmDataset *pDestDataset = (CDvmDataset*)pDestCmpData->GetParent();
	CDvmDatasetMap *pDatasetMap = NULL;

	//找到相应的MAP
	pDatasetMap = m_oDvmDeviceMap.FindDsMap_ByStandDest(pStandDataset, pDestDataset);
	CDvmDataMap *pStandDataMap = (CDvmDataMap *)pStandData->m_pDvmMapObj;
	CDvmDatasetMap *pStandDsMap = (CDvmDatasetMap*)pStandDataMap->GetParent();

	if (pStandDsMap == pDatasetMap)
	{
		UpdateDvmDataMap(pStandDataMap, pDestCmpData);
	}
	else
	{
		pDatasetMap->AddNewChild(pStandDataMap);
		pStandDsMap->Remove(pStandDataMap);
		UpdateDvmDataMap(pStandDataMap, pDestCmpData);
	}
}

void CDvmMapTool::UpdateDvmValueMap(CDvmValueMap *pValueMap, CDvmValue *pDestCmpValue)
{
	if (pDestCmpValue != NULL)
	{
		pDestCmpValue->m_dwReserved = 1;
		pDestCmpValue->m_pDvmMapObj = pValueMap;
	}

	pValueMap->SetMap0(pDestCmpValue);
// 	pValueMap->StringCmp();

	if (pDestCmpValue == NULL)
	{
		return;
	}

	//比较数据的属性
	POS pos = pValueMap->GetHeadPosition();
	CDvmValue *pDvmValue = NULL;
	CDvmValueMap *pMap = NULL;

	while (pos!= NULL)
	{
		pMap = (CDvmValueMap *)pValueMap->GetNext(pos);

		//查找可以与pDestCmpValue比较的Value
		pDvmValue = FindCmpDvmValue(pDestCmpValue, (CDvmValue*)pMap->m_pStand);

		if (pDvmValue != NULL)
		{
			UpdateDvmValueMap(pMap, pDvmValue);
		}
	}
}

void CDvmMapTool::ClearDatasetMap(CDvmDatasetMap *pDatasetMap, CDvmDataset *pStandDataset)
{
	if (pDatasetMap == NULL)
	{
		return;
	}

	pDatasetMap->DeleteAll();
	pDatasetMap->m_pStand = pStandDataset;

	pDatasetMap->ClearDatasetMap();
}

void CDvmMapTool::CmpDvmData(CDvmDataMap *pDvmCmpObj)
{
	if (pDvmCmpObj == NULL)
	{
		return;
	}

	pDvmCmpObj->FreeStringCmp();
	CDvmData *pStand       = (CDvmData*)pDvmCmpObj->m_pStand;
	CDvmData *pDestCmpData = (CDvmData*)pDvmCmpObj->m_pMap;

	//比较名称、id

	//比较数据的属性
	pDvmCmpObj->DeleteAll();

	if (pStand == NULL)
	{
		return;
	}

	if (pDestCmpData != NULL)
	{
		POS pos = pStand->GetHeadPosition();
		CDvmValue *pDvmValue = NULL;

		while (pos!= NULL)
		{
			pDvmValue = (CDvmValue*)pStand->GetNext(pos);
			CmpDvmValue(pDestCmpData, pDvmValue, pDvmCmpObj);
		}

		pDvmCmpObj->AddNullDvmMap_Stand();
		pDvmCmpObj->SortDvmMap_Stand();
	}
	
	pDvmCmpObj->AddNullDvmMap_Stand();
	pDvmCmpObj->SortDvmMap_Stand();
}


//////////////////////////////////////////////////////////////////////////
CString CDvmMapTool::GetDvmValueKey(CDvmValue *pDvmValue)
{
	return m_oDvmCmpKeyDataTypes.GetDvmValueKey(pDvmValue);
}

CDvmValue* CDvmMapTool::FindCmpDvmValue(CExBaseList *pDest, CDvmValue *pStandValue)
{
	POS pos = pDest->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmMapObject *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;
	CString strValueAttr = GetDvmValueKey(pStandValue);
	long nLen = strValueAttr.GetLength();

	while (pos != NULL)
	{
		//遍历pStand的每一个Value，判断是否可以与pDestCmpValue进行比较
		pValue = (CDvmValue *)pDest->GetNext(pos);

		if (pValue->m_dwReserved == 1)
		{
			continue;
		}

		//shaolei  20220326  由CanCmpDvmObject_ID  改为CanCmpDvmObject（增加比较名称）
		nCmpRate = CanCmpDvmObject(pValue, pStandValue);

		if (nCmpRate > 0)
		{
			listCmp.AddTail(dvmmap_NewMpObject(pStandValue, pValue, nCmpRate));
			continue;
		}

		//if (nCmpRate > 0)
		if (pValue->m_strID.Right(nLen) == strValueAttr)
		{
			listCmp.AddTail(dvmmap_NewMpObject(pStandValue, pValue, 1));
		}
	}

	//获取相似程度最高的
	CDvmMapObject *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmValue*)pCmpObj->m_pMap;
	}
}

long CDvmMapTool::CanCmpDvmValue(CDvmValue *pStand, CDvmValue *pDestCmpValue)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpValue);

	return nCmp;
}

void CDvmMapTool::CmpDvmValue(CDvmData *pDestData, CDvmValue *pStandValue, CDvmDataMap *pDataMap)
{
	POS pos = pDestData->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValueMap *pValueMap = NULL;

	//查找可以与pDestCmpValue比较的Value
	pValue = FindCmpDvmValue(pDestData, pStandValue);

	if (pValue != NULL)
	{
		pValueMap = (CDvmValueMap*)pDataMap->FindDvmMap_Stand(pStandValue);

		if (pValueMap != NULL)
		{
			pValueMap->SetMap0(pValue);
		}
		else
		{
			pValueMap = pDataMap->AddDvmMap(pStandValue, pValue);
		}

		CmpDvmValueEx(pStandValue, pValue, pValueMap);
	}
}

void CDvmMapTool::CmpDvmValueEx(CDvmValue *pStand, CDvmValue *pDestCmpValue, CDvmValueMap *pValueMap)
{
	pStand->m_dwReserved = 1;
	pDestCmpValue->m_dwReserved = 1;

	//比较Value的属性，在此，不在深入比较
	POS pos = pStand->GetHeadPosition();
	CDvmValue *pDvmValue = NULL;
	CDvmValue *pDvmValueFind = NULL;

	while (pos!= NULL)
	{
		pDvmValue = (CDvmValue*)pStand->GetNext(pos);
		
		//查找可以与pDestCmpValue比较的Value
		pDvmValueFind = FindCmpDvmValue(pDestCmpValue, pDvmValue);

		if (pDvmValueFind != NULL)
		{
			CDvmValueMap *pNew = (CDvmValueMap*)pValueMap->FindDvmMapObj(pDvmValue, pDvmValueFind);

			if (pNew == NULL)
			{
				pNew = pValueMap->AddDvmMap(pDvmValue, pDvmValueFind);
			}

			CmpDvmValueEx(pDvmValue, pDvmValueFind, pNew);
		}
	}
}
// 
// CDvmCmpObj* CDvmMapTool::CmpDvmValueVal(CDvmValue *pStand, CDvmValue *pDestCmpValue)
// {
// 	return NULL;
// }

CDvmMapObject* CDvmMapTool::GetCmpMatchObject(CExBaseList &listCmpObj)
{
	CDvmMapObject *pFind = (CDvmMapObject*)listCmpObj.GetHead();

	if (listCmpObj.GetCount() <= 1)
	{
		return pFind;
	}

	POS pos = listCmpObj.GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)listCmpObj.GetNext(pos);

		if (pFind->m_nCmpRate < p->m_nCmpRate)
		{
			pFind = p;
		}
	}

	return pFind;
}

//比较名称、ID
long CDvmMapTool::CanCmpDvmObject(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	return m_oDvmCmpKeyDataTypes.CanCmpDvmObject(pStand, pDestCmpObj);
}

long CDvmMapTool::CanCmpDvmObject_ID(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	return m_oDvmCmpKeyDataTypes.CanCmpDvmObject_ID(pStand, pDestCmpObj);
}

void CDvmMapTool::OpenKeyDataTypesFile(const CString &strFile)
{
	m_oDvmCmpKeyDataTypes.OpenKeyDataTypesFile(strFile);
}


long CDvmMapTool::GetLdeviceKey(const CString &strText)
{
	return m_oDvmCmpKeyDataTypes.GetLdeviceKey(strText);
}

long CDvmMapTool::GetDatasetKey(const CString &strText)
{
	return m_oDvmCmpKeyDataTypes.GetDatasetKey(strText);
}

long CDvmMapTool::GetCmpFullNameIdKey(const CString &strText)
{
	return m_oDvmCmpKeyDataTypes.GetCmpFullNameIdKey(strText);
}

// 
// void CDvmMapTool::AddOtherCmpObj_Stand()
// {
// 	POS pos = GetHeadPosition();
// 	CDvmCmpObj *pLdCmp = NULL;
// 	POS posDsCmp = NULL;
// 	CDvmCmpObj *pDsCmp;
// 	CDvmDatasetMap *pDsMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		//遍历ldevice的比较对象
// 		pLdCmp = (CDvmCmpObj *)GetNext(pos);
// 
// 		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		//遍历逻辑设备比较对象
// 		posDsCmp = pLdCmp->GetHeadPosition();
// 
// 		while (posDsCmp != NULL)
// 		{
// 			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);
// 
// 			if (pDsCmp->m_pStand == NULL)
// 			{
// 				continue;
// 			}
// 
// 			AddOtherCmpObj_Stand((CExBaseList*)pDsCmp->m_pStand, pDsCmp);;
// 		}
// 	}
// }
// 
// long CDvmMapTool::AddOtherCmpObj_Stand(CExBaseList *pStand, CExBaseList *pListCmpObj)
// {
// 	POS pos = pStand->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	UINT nClassID = pStand->GetClassID();
// 	long nCount = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = pStand->GetNext(pos);
// 
// 		if (p->m_dwReserved == 1)
// 		{
// 			continue;
// 		}
// 
// 		if (!IsStandInListCmpObj(p, pListCmpObj))
// 		{
// 			CDvmCmpObj *pNew = new CDvmCmpObj(p, NULL);
// 			pNew->m_nCmpResult = 1;
// 			pListCmpObj->AddNewChild(pNew);
// 
// 			if (nClassID == DVMCLASSID_CDVMDEVICE
// 				|| nClassID == DVMCLASSID_CDVMLOGICDEVICE 
// 				|| nClassID == DVMCLASSID_CDVMDATASET
// 				|| nClassID == DVMCLASSID_CDVMDATA)
// 			{
// 				pNew->m_nChildCmp = AddOtherCmpObj_Stand((CExBaseList*)p, pNew);
// 				nCount++;
// 			}
// 		}
// 		
// 		//p->m_dwReserved = 1;
// 	}
// 
// 	return nCount;
// }
// 
// BOOL CDvmMapTool::IsStandInListCmpObj(CExBaseObject *pStand, CExBaseList *pListCmpObj)
// {
// 	POS pos = pListCmpObj->GetHeadPosition();
// 	CDvmCmpObj *p = NULL;
// 	BOOL bFind = FALSE;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmCmpObj*)pListCmpObj->GetNext(pos);
// 
// 		if (pStand == p->m_pStand)
// 		{
// 			bFind = TRUE;
// 		}
// 	}
// 
// 	return bFind;
// }
// 
// 
// long CDvmMapTool::AddOtherCmpObj_DestCmp(CExBaseList *pDestCmp, CExBaseList *pListCmpObj)
// {
// 	POS pos = pDestCmp->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	UINT nClassID = pDestCmp->GetClassID();
// 	long nCount = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = pDestCmp->GetNext(pos);
// 
// 		if (!IsDestCmpInListCmpObj(p, pListCmpObj))
// 		{
// 			CDvmCmpObj *pNew = new CDvmCmpObj(NULL, p);
// 			pListCmpObj->AddNewChild(pNew);
// 			pNew->m_nCmpResult = 1;
// 
// 			if (nClassID == DVMCLASSID_CDVMLOGICDEVICE 
// 				|| nClassID == DVMCLASSID_CDVMDATASET
// 				|| nClassID == DVMCLASSID_CDVMDATA)
// 			{
// 				pNew->m_nChildCmp = AddOtherCmpObj_DestCmp((CExBaseList*)p, pNew);
// 				nCount++;
// 			}
// 		}
// 	}
// 
// 	return nCount;
// }
// 
// BOOL CDvmMapTool::IsDestCmpInListCmpObj(CExBaseObject *pDestCmp, CExBaseList *pListCmpObj)
// {
// 	POS pos = pListCmpObj->GetHeadPosition();
// 	CDvmCmpObj *p = NULL;
// 	BOOL bFind = FALSE;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmCmpObj*)pListCmpObj->GetNext(pos);
// 
// 		if (pDestCmp == p->m_pMap)
// 		{
// 			bFind = TRUE;
// 		}
// 	}
// 
// 	return bFind;
// }
// 
// 
// void CDvmMapTool::CreateDvmMap()
// {
// 	POS pos = GetHeadPosition();
// 	CDvmCmpObj *pDvmCmp = NULL;
// 
// 	//Dataset
// 	while (pos != NULL)
// 	{
// 		pDvmCmp = (CDvmCmpObj *)GetNext(pos);
// 
// 		if (pDvmCmp->m_pStand == NULL)
// 		{
// 			continue;
// 		}
// 
// 		CreateDvmMap_Ldevice(pDvmCmp);
// 	}
// }
// 
// void CDvmMapTool::CreateDvmMap_Ldevice(CDvmCmpObj *pDvmLdeviceCmp)
// {
// 	CDvmDatasetMap *pDatasetMap = NULL;
// 	POS pos = pDvmLdeviceCmp->GetHeadPosition();
// 	CDvmCmpObj *pDsCmp = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDsCmp = (CDvmCmpObj *)pDvmLdeviceCmp->GetNext(pos);
// 
// 		if (pDsCmp->m_pStand == NULL)
// 		{
// 			continue;
// 		}
// 
// 		pDatasetMap = new CDvmDatasetMap();
// 		pDatasetMap->m_strName = pDsCmp->m_pStand->m_strName;
// 		pDatasetMap->m_strID = pDsCmp->m_pStand->m_strID;
// 		pDatasetMap->m_strLdvice    = pDvmLdeviceCmp->m_pStand->m_strID;
// 
// 		if (pDvmLdeviceCmp->m_pMap != NULL)
// 		{
// 			pDatasetMap->m_strLdviceMap = pDvmLdeviceCmp->m_pMap->m_strID;
// 		}
// 
// 		if (pDsCmp->m_pMap != NULL)
// 		{
// 			pDatasetMap->m_strMapName = pDsCmp->m_pMap->m_strName;
// 			pDatasetMap->m_strMapID   = pDsCmp->m_pMap->m_strID;
// 		}
// 
// 		m_oDvmDeviceMap.AddNewChild(pDatasetMap);
// 		CreateDvmMap(pDatasetMap, pDsCmp);
// 	}
// }
// 
// void CDvmMapTool::CreateDvmMap(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp)
// {
// 	POS pos = pDvmDatasetCmp->GetHeadPosition();
// 	CDvmCmpObj *pDvmCmp = NULL;
// 	CDvmDataMap *pDataMap = NULL;
// 
// 	//Dataset
// 	while (pos != NULL)
// 	{
// 		pDvmCmp = (CDvmCmpObj *)pDvmDatasetCmp->GetNext(pos);
// 	
// 		if (pDvmCmp->m_pStand == NULL || pDvmCmp->m_pMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		pDataMap = new CDvmDataMap();
// 		pDataMap->m_strName = pDvmCmp->m_pStand->m_strName;
// 		pDataMap->m_strID = pDvmCmp->m_pStand->m_strID;
// 		pDataMap->m_strMapName = pDvmCmp->m_pMap->m_strName;
// 		pDataMap->m_strMapID = pDvmCmp->m_pMap->m_strID;
// 
// 		pMap->AddNewChild(pDataMap);
// 		CreateDvmMap(pDataMap, pDvmCmp);
// 	}
// }
// 
// void CDvmMapTool::CreateDvmMap(CDvmDataMap *pMap, CDvmCmpObj *pDvmDataCmp)
// {
// 	POS pos = pDvmDataCmp->GetHeadPosition();
// 	CDvmCmpObj *pDvmCmp = NULL;
// 	CDvmValueMap *pValueMap = NULL;
// 
// 	//Dataset
// 	while (pos != NULL)
// 	{
// 		pDvmCmp = (CDvmCmpObj *)pDvmDataCmp->GetNext(pos);
// 
// 		if (pDvmCmp->m_pStand == NULL)
// 		{
// 			continue;
// 		}
// 
// 		if (pDvmCmp->m_pMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		pValueMap = new CDvmValueMap();
// 		pValueMap->m_strName = pDvmCmp->m_pStand->m_strName;
// 		pValueMap->m_strID = pDvmCmp->m_pStand->m_strID;
// 		pValueMap->m_strMapName = pDvmCmp->m_pMap->m_strName;
// 		pValueMap->m_strMapID = pDvmCmp->m_pMap->m_strID;
// 
// 		pMap->AddNewChild(pValueMap);
// 	}
// }

//////////////////////////////////////////////////////////////////////////
//
void CDvmMapTool::InitByDvmMap()
{
// 	POS pos = GetHeadPosition();
// 	CDvmCmpObj *pLdCmp = NULL;
// 	POS posDsCmp = NULL;
// 	CDvmCmpObj *pDsCmp;
// 	CDvmDatasetMap *pDsMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		//遍历ldevice的比较对象
// 		pLdCmp = (CDvmCmpObj *)GetNext(pos);
// 
// 		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		//遍历逻辑设备比较对象
// 		posDsCmp = pLdCmp->GetHeadPosition();
// 
// 		while (posDsCmp != NULL)
// 		{
// 			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);
// 
// 			if (pDsCmp->m_pStand == NULL || pDsCmp->m_pMap == NULL)
// 			{
// 				continue;
// 			}
// 
// 			//数据集比较对象：查找数据映射关联对象
// 			pDsMap = m_oDvmDeviceMap.FindDsMap(pLdCmp->m_pStand->m_strID, pDsCmp->m_pStand->m_strID
// 				, pLdCmp->m_pMap->m_strID, pDsCmp->m_pMap->m_strID);
// 
// 			if (pDsMap != NULL)
// 			{
// 				//根据数据集比较对象，数据集关联对象，更新数据集比较对象
// 				UpdateByMap_DsCmp(pDsMap, pDsCmp);
// 			}
// 		}
// 	}
}

void CDvmMapTool::UpdateByMap_DsCmp(CDvmDatasetMap *pMap, CDvmDatasetMap *pDvmDatasetCmp)
{
// 	POS pos = pDvmDatasetCmp->GetHeadPosition();
// 	CDvmCmpObj *pDvmDataCmp = NULL;
// 	CDvmDataset *pDsStand = (CDvmDataset*)pDvmDatasetCmp->m_pStand;
// 	CDvmDataset *pDsDest = (CDvmDataset*)pDvmDatasetCmp->m_pMap;
// 	CDvmDataMap *pDaStandMap = NULL;
// 	CDvmData *pDestData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDvmDataCmp = (CDvmCmpObj *)pDvmDatasetCmp->GetNext(pos);
// 		
// 		if (pDvmDataCmp->m_pStand == NULL)
// 		{
// 			continue;
// 		}
// 
// 		//根据比较对象的Stand对象，查找映射关系中的DataMap对象
// // 		if (pDvmDataCmp->m_pStand->m_strName.Find(_T("1时限")) >= 0)
// // 		{
// // 			int kk = 0;
// // 		}
// 
// 		pDaStandMap = pMap->FindMapData(pDvmDataCmp->m_pStand->m_strID);
// 
// 		if (pDaStandMap == NULL)
// 		{
// 			continue;
// 		}
// 
// 		//目标数据集中查找映射关系的数据对象
// 		pDestData = (CDvmData *)pDsDest->FindByID(pDaStandMap->m_strMapID);
// 
// 		if (pDestData != NULL)
// 		{
// 			CDvmCmpObj *pFind = pDvmDataCmp->SetDest(pDestData);
// 
// 			if (pFind != NULL)
// 			{
// 				CmpDvmData(pDvmDataCmp);
// 				CmpDvmData(pFind);
// 			}
// 		}
// 	}
}
// 
// void CDvmMapTool::UpdateByMap_DataCmp(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDataCmp)
// {
// 
// }


//////////////////////////////////////////////////////////////////////////

void CDvmMapTool::OpenKeyDbFile()
{
	CString strFile;
	strFile = _P_GetCommonLibraryPath();
	strFile += _T("RelayTestKeyDb.xml");
	m_oKeyDB.OpenKeyDbFile(strFile);
}

void CDvmMapTool::XMatchDataset(CDvmDataset *pDsDestCmp, CDvmDataset *pDsStand)
{
	//匹配度阈值，设置在key-db文件中   shaolei 20220517
	//<key-db min-rate="70" >
	m_oXMatchTool.Match(&m_oKeyDB, pDsStand, pDsDestCmp, /*70*/m_oKeyDB.m_nMinRate);
}

//////////////////////////////////////////////////////////////////////////
void CDvmMapTool::ExportReportFile(const CString &strFile)
{
// 	CreateWordApplication(TRUE);
// 
// 	if (!NewWordReportFile())
// 	{
// 		return;
// 	}
// 
// 	POS pos = GetHeadPosition();
// 	CDvmCmpObj *pLdCmp = NULL;
// 	POS posDsCmp = NULL;
// 	CDvmCmpObj *pDsCmp;
// 	CDvmDatasetMap *pDsMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		//遍历ldevice的比较对象
// 		pLdCmp = (CDvmCmpObj *)GetNext(pos);
// 
// 		if (pLdCmp->m_pMap == NULL || pLdCmp->m_pStand == NULL)
// 		{
// 			continue;
// 		}
// 
// 
// 		if (pLdCmp->m_pStand->m_strID != pLdCmp->m_pMap->m_strID)
// 		{
// 			CString strTitle;
// 			strTitle.Format(_T("%s : %s"), pLdCmp->m_pStand->m_strID, pLdCmp->m_pMap->m_strID);
// 			InsertTitle(pLdCmp->m_pStand->m_strID , 1);
// 		}
// 		else
// 		{
// 			InsertTitle(pLdCmp->m_pStand->m_strID, 1);
// 		}
// 
// 		//遍历逻辑设备比较对象
// 		posDsCmp = pLdCmp->GetHeadPosition();
// 
// 		while (posDsCmp != NULL)
// 		{
// 			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);
// 			ExportReport_DsCmp(pDsCmp);
// 		}
// 	}
// 
// 	//Doc文件保存
// 	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	
// 
// 	m_doc.SaveAs(COleVariant(strFile), vOpt, vOpt, vOpt,
// 		vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
}

void CDvmMapTool::ExportReport_DsCmp(CDvmDatasetMap *pDsCmp)
{
// 	if (pDsCmp->m_pStand == NULL || pDsCmp->m_pMap == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_oRptDstaset.FindByID(pDsCmp->m_pStand->m_strID) == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (!pDsCmp->IsCmpError_Child())
// 	{
// 		return;
// 	}
// 
// 	CString strTitle;
// 	
// 	strTitle = pDsCmp->m_pStand->m_strID;
// 
// 	if (pDsCmp->m_pMap != NULL)
// 	{
// 		if (pDsCmp->m_pMap->m_strID != pDsCmp->m_pStand->m_strID)
// 		{
// 			strTitle.AppendFormat(_T(" : %s"), pDsCmp->m_pMap->m_strID);
// 		}
// 	}
// 	
// 	InsertTitle(strTitle, 2);
// 	POS pos = pDsCmp->GetHeadPosition();
// 	CDvmCmpObj *pDataCmp = NULL;
// 
// 	long nVal = MSWord::wdWord9TableBehavior;
// 	CComVariant vTableBehavior(nVal); 
// 	nVal = MSWord::wdAutoFitFixed;
// 	CComVariant vAutoFitBehavior(nVal); 
// 
// 	MSWord::Selection oSelection = m_WordApp.GetSelection();
// 	MSWord::Range oRange = oSelection.GetRange();
// 	MSWord::Tables oTables = m_doc.GetTables();
// 	MSWord::Table oTable   = oTables.Add(oRange, 1, 4, &vTableBehavior, &vAutoFitBehavior);
// 	MSWord::Columns oCols = oTable.GetColumns();
// 	MSWord::Column  oCol  = NULL;
// 	
// 	try
// 	{
// 		oCol  = oCols.Item(1);
// 		float fWidth = oCol.GetWidth();
// 		float fWidthTotl = fWidth * 4;
// 		float fTemp = fWidth / 6;
// 		m_fWidthCol1 = fTemp;
// 		oCol.SetWidth(fTemp);
// 		fWidthTotl -= fTemp;
// 		//oCol.Select();
// 		//oSelection = m_WordApp.GetSelection();
// 		//oSelection.TypeText(_T("比较项"));
// 
// 		oCol  = oCols.Item(2);
// 		fTemp = fWidth * 0.6f;
// 		fWidthTotl -= fTemp;
// 		oCol.SetWidth(fTemp);
// 		m_fWidthCol2 = fTemp;
// 		oCol.Select();
// 		//oSelection = m_WordApp.GetSelection();
// 		oSelection.TypeText(_T("比较项"));
// 
// 		oCol  = oCols.Item(3);
// 		fTemp = fWidthTotl / 2;
// 		oCol.SetWidth(fTemp);
// 		oCol.Select();
// 		//oSelection = m_WordApp.GetSelection();
// 		oSelection.TypeText(_T("标准值"));
// 
// 		oCol  = oCols.Item(4);
// 		oCol.SetWidth(fTemp);
// 		oCol.Select();
// 		//oSelection = m_WordApp.GetSelection();
// 		oSelection.TypeText(_T("实际值"));
// 		m_fWidthCol3 = m_fWidthCol4 = fTemp;
// 	}
// 	catch (...)
// 	{
// 		
// 	}
// 	
// 	long nRowIndex = 1;
// 
// 	while (pos != NULL)
// 	{
// 		pDataCmp = (CDvmCmpObj *)pDsCmp->GetNext(pos);
// 		try
// 		{
// 			ExportReport_DataCmp(pDataCmp, oTable, nRowIndex);
// 		}
// 		catch (...)
// 		{
// 
// 		}
// 	}
}

void CDvmMapTool::MergeRow(MSWord::Row &oRow)
{
	MSWord::Cells oCells = oRow.GetCells();

	if (oCells.GetCount() == 3)
	{
		return;
	}

	MSWord::Cell  oCell = oCells.Item(1);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();

	long nVal;
	nVal = MSWord::wdCharacter;
	CComVariant vUnit(nVal); 
	CComVariant vCount(long(1)); 
	nVal = MSWord::wdExtend;
	CComVariant vExtend(nVal); 
	oSelection.MoveRight(&vUnit, &vCount, &vExtend);
	oCells = oSelection.GetCells();
	oCells.Merge();
}

void CDvmMapTool::InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit)
{
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 
	oSelection.InsertRowsBelow(&vCount);
	MSWord::Rows oRows = oTable.GetRows();
	oRow = oRows.Item(oRows.GetCount());
	MSWord::Cells oCells = oRow.GetCells();
	
	if (!bSplit)
	{
		return;
	}

	if (oCells.GetCount() == 3)
	{
		CComVariant vCols(long(2)); 
		CComVariant vMergeBeforeSplit(long(0)); 
		MSWord::Cell oCell = oCells.Item(1);
		oCell.Select();
		oSelection = m_WordApp.GetSelection();
		oCells = oSelection.GetCells();
		oCells.Split(&vCount, &vCols, &vMergeBeforeSplit);

		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.SetWidth(m_fWidthCol1);

		oCell = oCells.Item(2);
		oCell.SetWidth(m_fWidthCol2);

		oCell = oCells.Item(3);
		oCell.SetWidth(m_fWidthCol3);

		oCell = oCells.Item(4);
		oCell.SetWidth(m_fWidthCol4);
	}
}

void CDvmMapTool::GetRowCell(MSWord::Row &oRow, MSWord::Cell &oCell, long nIndex)
{
	MSWord::Cells oCells = oRow.GetCells();
	oCell = oCells.Item(nIndex);
}

void CDvmMapTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(RGB(0, 0, 0));
	oSelection.TypeText(strText);
}

void CDvmMapTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(color);
	oSelection.TypeText(strText);
	oFont.SetColor(RGB(0, 0, 0));
}

void CDvmMapTool::SetRowCellText(MSWord::Row &oRow, long nIndex, CStringCmpBlocks *pStrCmpBlcks)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();

	POS pos = pStrCmpBlcks->GetHeadPosition();
	CStringCmpBlock *pStrCmpBlck = NULL;
	CString strText;
	MSWord::_Font oFont = oSelection.GetFont();

	ASSERT (pos != NULL);

	while (pos != NULL)
	{
		pStrCmpBlck = (CStringCmpBlock *)pStrCmpBlcks->GetNext(pos);
		strText = pStrCmpBlck->m_pStringRef->Mid(pStrCmpBlck->m_nBeginPos, pStrCmpBlck->m_nLength);

		if (pStrCmpBlck->IsMatch())
		{
			oFont.SetColor(RGB(0, 0, 0));
		}
		else
		{
			oFont.SetColor(RGB(255, 0, 0));
		}

		pStrCmpBlck->GetString(strText);
		oSelection.TypeText(strText);
	}

	oFont.SetColor(RGB(0, 0, 0));
}

void CDvmMapTool::ExportReport_DataCmp(CDvmDataMap *pDataCmp, MSWord::Table &oTable, long &nRowIndex)
{
// 	if (pDataCmp->m_pStand == NULL && pDataCmp->m_pMap == NULL)
// 	{
// 		return;
// 	}
// 
// 	long nRows = 0;
// 	MSWord::Rows oRows = oTable.GetRows();
// 	MSWord::Row  oRow  = NULL;
// 	MSWord::Cell oCell = NULL;
// 	MSWord::Selection oSelection = m_WordApp.GetSelection();
// 	MSWord::Range oRange = oSelection.GetRange();
// 	CComVariant vCount(long(1)); 
// 
// 	if (pDataCmp->m_pStand == NULL)
// 	{
// 		InsertRow(oRow, oTable, FALSE);
// 		MergeRow(oRow);
// 		SetRowCellText(oRow, 1, _T("名称"));
// 		SetRowCellText(oRow, 3, pDataCmp->m_pMap->m_strName, RGB(255, 0, 0));
// 		nRowIndex++;
// 		return;
// 	}
// 
// 	if (pDataCmp->m_pMap == NULL)
// 	{
// 		InsertRow(oRow, oTable, FALSE);
// 		MergeRow(oRow);
// 		SetRowCellText(oRow, 1, _T("名称"));
// 		SetRowCellText(oRow, 2, pDataCmp->m_pStand->m_strName, RGB(255, 0, 0));
// 		nRowIndex++;
// 		return;
// 	}
// 
// 	pDataCmp->StringCmp();
// 
// 	if (ExportReport_DataCmp_GetRows(pDataCmp) == 0)
// 	{
// 		return;
// 	}
// 
// 	InsertRow(oRow, oTable, FALSE);
// 	MergeRow(oRow);
// 	SetRowCellText(oRow, 1, _T("名称"));
// 	CDvmData *pStand = (CDvmData *)pDataCmp->m_pStand;
// 	CDvmData *pDest  = (CDvmData *)pDataCmp->m_pMap;
// 
// 	if (pDataCmp->IsNameCmpError())
// 	{
// 		SetRowCellText(oRow, 2, pDataCmp->GetNameCmp_Stand());
// 		SetRowCellText(oRow, 3, pDataCmp->GetNameCmp_Dest());
// 	}
// 	else
// 	{
// 		SetRowCellText(oRow, 2, pStand->m_strName);
// 		SetRowCellText(oRow, 3, pDest->m_strName);
// 	}
// 
// 	nRowIndex++;
// 
// 	if (pDataCmp->IsMaxCmpError())	
// 	{
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("最大值"));
// 		SetRowCellText(oRow, COL_STAND, pStand->m_strMax, RGB(255, 0, 0));
// 		SetRowCellText(oRow, COL_DEST, pDest->m_strMax, RGB(255, 0, 0));
// 		nRowIndex++;
// 	}
// 
// 	if (pDataCmp->IsMinCmpError())
// 	{
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("最小值"));
// 		SetRowCellText(oRow, COL_STAND, pStand->m_strMin, RGB(255, 0, 0));
// 		SetRowCellText(oRow, COL_DEST, pDest->m_strMin, RGB(255, 0, 0));
// 		nRowIndex++;
// 	}
// 
// 	if (pDataCmp->IsStepCmpError())
// 	{
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("步长"));
// 		SetRowCellText(oRow, COL_STAND, pStand->m_strStep, RGB(255, 0, 0));
// 		SetRowCellText(oRow, COL_DEST, pDest->m_strStep, RGB(255, 0, 0));
// 		nRowIndex++;
// 	}
// 
// 	if (pDataCmp->m_nStandIndex != pDataCmp->m_nDestIndex && pDataCmp->m_nDestIndex >= 0)
// 	{
// 		CString strText;
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("编号"));
// 		strText.Format(_T("%d"), pDataCmp->m_nStandIndex);
// 		SetRowCellText(oRow, COL_STAND, strText, RGB(255, 0, 0));
// 		strText.Format(_T("%d"), pDataCmp->m_nDestIndex);
// 		SetRowCellText(oRow, COL_DEST, strText, RGB(255, 0, 0));
// 		nRowIndex++;
// 	}
// 
// 	POS pos = pDataCmp->GetHeadPosition();
// 	CDvmCmpObj *pValueCmp = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pValueCmp = (CDvmCmpObj *)pDataCmp->GetNext(pos);
// 		ExportReport_ValueCmp(pValueCmp, oTable, nRowIndex);
// 	}
}


void CDvmMapTool::ExportReport_ValueCmp(CDvmValueMap *pValueCmp, MSWord::Table &oTable, long &nRowIndex)
{
// 	if (pValueCmp->m_pStand == NULL && pValueCmp->m_pMap == NULL)
// 	{
// 		return;
// 	}
// 
// 	long nRows = 0;
// 	MSWord::Rows oRows = oTable.GetRows();
// 	MSWord::Row  oRow  = NULL;
// 	MSWord::Cell oCell = NULL;
// 	MSWord::Selection oSelection = m_WordApp.GetSelection();
// 	MSWord::Range oRange = oSelection.GetRange();
// 	CComVariant vCount(long(1)); 
// 	CString strKey;
// 
// 	if (pValueCmp->m_pStand == NULL)
// 	{
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("属性"));
// 		SetRowCellText(oRow, COL_DEST, pValueCmp->m_pMap->m_strID, RGB(255, 0, 0));
// 		nRowIndex++;
// 		return;
// 	}
// 
// 	if (pValueCmp->m_pMap == NULL)
// 	{
// 		InsertRow(oRow, oTable);
// 		SetRowCellText(oRow, COL_CMPTYPE, _T("属性"));
// 		SetRowCellText(oRow, COL_STAND, pValueCmp->m_pStand->m_strID, RGB(255, 0, 0));
// 		nRowIndex++;
// 		return;
// 	}
// 
// 	CDvmValue *pStand = (CDvmValue *)pValueCmp->m_pStand;
// 	CDvmValue *pDest  = (CDvmValue *)pValueCmp->m_pMap;
// 
// 	if (pStand->m_strDataType == pDest->m_strDataType)
// 	{
// 		return;
// 	}
// 
// 	strKey = GetDvmValueKey(pStand);
// 
// 	InsertRow(oRow, oTable);
// 	SetRowCellText(oRow, COL_CMPTYPE, strKey);
// 	SetRowCellText(oRow, COL_STAND, pStand->m_strDataType);
// 	SetRowCellText(oRow, COL_DEST, pDest->m_strDataType);
}

long CDvmMapTool::ExportReport_DataCmp_GetRows(CDvmDataMap *pDataCmp)
{
	long nRowIndex = 0;

// 	if (pDataCmp->IsNameCmpError())
// 	{
// 		nRowIndex++;
// 	}
// 
// 	CDvmData *pStand = (CDvmData *)pDataCmp->m_pStand;
// 	CDvmData *pDest  = (CDvmData *)pDataCmp->m_pMap;
// 
// 	if (pDataCmp->IsMaxCmpError())	
// 	{
// 		nRowIndex++;
// 	}
// 
// 	if (pDataCmp->IsMinCmpError())
// 	{
// 		nRowIndex++;
// 	}
// 
// 	if (pDataCmp->IsStepCmpError())
// 	{
// 		nRowIndex++;
// 	}
// 
// 	POS pos = pDataCmp->GetHeadPosition();
// 	CDvmCmpObj *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmCmpObj *)pDataCmp->GetNext(pos);
// 
// 		if (p->m_pStand == NULL || p->m_pMap == NULL)
// 		{
// 			nRowIndex++;
// 			continue;
// 		}
// 
// 		if (((CDvmValue*)p->m_pStand)->m_strDataType != ((CDvmValue*)p->m_pMap)->m_strDataType)
// 		{
// 			nRowIndex++;
// 		}
// 	}

	return nRowIndex++;
}

//目前不使用这种方式创建、打开word，因为这种方式下当word已打开时会弹出**已打开对话框。
BOOL CDvmMapTool::CreateWordApplication(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		return TRUE;
	}

	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			AfxMessageBox(_T("没有安装Word"));
			return FALSE;
		}

		m_WordApp.SetVisible(bVisible);  //This shows the application.
	}
	catch (...)
	{
	}

	return TRUE;
}

BOOL CDvmMapTool::ExitWordApplication()
{
	//关闭文档
	try
	{
		COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		if (m_doc != NULL)
		{
			m_doc.Close(vFalse,covOptional,covOptional);
		}

		m_doc = NULL;
	}
	catch (...)
	{
		m_doc = NULL;

		TRACE(L"Close word doc error...");
	}

	try
	{
		if(m_WordApp)
		{
			COleVariant covTrue((long)TRUE);
			COleVariant covFalse((long)FALSE);
			COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			m_WordApp.Quit(covFalse, covOptional, covOptional);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	return TRUE;
}

BOOL CDvmMapTool::NewWordReportFile()
{
	if (m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_WordApp.SetVisible(TRUE);
	BOOL bTrue = TRUE;
	try
	{
		CComVariant Template(_T("")); 
		CComVariant NewTemplate(false),DocumentType(0),Visible;
		m_doc = docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	}
	catch(...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


void CDvmMapTool::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	wordSelection = m_WordApp.GetSelection();
	wordSelection.EndKey(&vUnit, &vOpt);
	wordSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wordSelection.TypeText(strTitle);
		MSWord::Styles oStyles = m_doc.GetStyles();
		CString strStyle;
		strStyle.Format(_T("标题 %d"), nTitleLevel);
		COleVariant vStyleID = strStyle;
		wordSelection.SetStyle(vStyleID);
	}
	else
	{
		MSWord::_Font font = wordSelection.GetFont();
		float fSize = font.GetSize();
		font.SetBold(TRUE);
		font.SetSize(16);
		wordSelection.TypeText(strTitle);
		font.SetSize(fSize);
		font.SetBold(FALSE);
	}

	wordSelection.TypeParagraph();
}

/*
Sub 宏1()
'
' 宏1 宏
'
'
Selection.Delete Unit:=wdCharacter, Count:=1
Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
Sub 宏2()
'
' 宏2 宏
'
'
Selection.PasteAndFormat (wdFormatOriginalFormatting)
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("标题 1")
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.TypeText Text:="支路4_"
Application.WindowState = wdWindowStateMinimize
Application.WindowState = wdWindowStateNormal
Selection.TypeText Text:="间隔接受压板"
Selection.Style = ActiveDocument.Styles("标题 2")
Selection.TypeParagraph
ActiveDocument.Tables.Add Range:=Selection.Range, NumRows:=3, NumColumns:= _
3, DefaultTableBehavior:=wdWord9TableBehavior, AutoFitBehavior:= _
wdAutoFitFixed
With Selection.Tables(1)
If .Style <> "网格型" Then
.Style = "网格型"
End If
.ApplyStyleHeadingRows = True
.ApplyStyleLastRow = False
.ApplyStyleFirstColumn = True
.ApplyStyleLastColumn = False
.ApplyStyleRowBands = True
.ApplyStyleColumnBands = False
End With
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("正文")
ActiveWindow.Close
End Sub
Sub 宏3()
'
' 宏3 宏
'
'
Selection.TypeText Text:="LLN"
Application.Keyboard (1033)
Selection.TypeText Text:="$dsSetting"
Selection.TypeParagraph
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("标题 1")
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.TypeText Text:="1,"
Application.Keyboard (2052)
Selection.TypeText Text:="支路4_间隔跳闸压板"
Selection.TypeParagraph
ActiveDocument.Tables.Add Range:=Selection.Range, NumRows:=4, NumColumns:= _
3, DefaultTableBehavior:=wdWord9TableBehavior, AutoFitBehavior:= _
wdAutoFitFixed
With Selection.Tables(1)
If .Style <> "网格型" Then
.Style = "网格型"
End If
.ApplyStyleHeadingRows = True
.ApplyStyleLastRow = False
.ApplyStyleFirstColumn = True
.ApplyStyleLastColumn = False
.ApplyStyleRowBands = True
.ApplyStyleColumnBands = False
End With
Selection.TypeText Text:="名称"
Selection.MoveRight Unit:=wdCharacter, Count:=1
Selection.TypeText Text:="支路4"
Selection.MoveLeft Unit:=wdCharacter, Count:=4, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=1, Extend:=wdExtend
Selection.MoveLeft Unit:=wdCharacter, Count:=1, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=1
Selection.TypeText Text:="_间隔接受压板"
Selection.MoveLeft Unit:=wdCharacter, Count:=13
Selection.MoveDown Unit:=wdLine, Count:=3, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=2, Extend:=wdExtend
With Selection.Tables(1)
.TopPadding = CentimetersToPoints(0)
.BottomPadding = CentimetersToPoints(0)
.LeftPadding = CentimetersToPoints(0.19)
.RightPadding = CentimetersToPoints(0.19)
.Spacing = 0
.AllowPageBreaks = True
.AllowAutoFit = True
End With
Selection.EscapeKey
End Sub


Sub 宏1()
'
' 宏1 宏
'
'
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.EndKey Unit:=wdLine, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=9, Extend:=wdExtend
Selection.Cells.Merge
Selection.MoveDown Unit:=wdLine, Count:=3
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
End Sub
Sub 宏2()
'
' 宏2 宏
'
'
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.EndKey Unit:=wdLine, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=5, Extend:=wdExtend
Selection.Cells.Merge
End Sub

*/