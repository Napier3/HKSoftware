//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDatasetMap.cpp  CDvmDatasetMap


#include "stdafx.h"
#include "DvmDatasetMap.h"
#include "DvmLDeviceMap.h"

CDvmDatasetMap::CDvmDatasetMap()
{
	//初始化属性
	m_bAddMapFindByStand = TRUE;

	//初始化成员变量
}

CDvmDatasetMap::~CDvmDatasetMap()
{
}

long CDvmDatasetMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strCDvmLogicDeviceKey, oNode, m_strLdvice);
	xml_GetAttibuteValue(pXmlKeys->m_strCDvmLogicDeviceMapKey, oNode, m_strLdviceMap);

	return 0;
}

long CDvmDatasetMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strCDvmLogicDeviceKey, oElement, m_strLdvice);
	xml_SetAttributeValue(pXmlKeys->m_strCDvmLogicDeviceMapKey, oElement, m_strLdviceMap);

	return 0;
}

long CDvmDatasetMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CDvmDatasetMap::InitAfterRead()
{
	ClearEmptyMap();
}

void CDvmDatasetMap::ClearEmptyMap()
{
	POS pos = GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)GetNext(pos);

		if (pDataMap->IsMapEmpty())
		{
			Delete(pDataMap);
		}
	}
}

BOOL CDvmDatasetMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmDatasetMap *p = (CDvmDatasetMap*)pObj;

	return CDvmMapObject::IsEqualOwn(pObj);
}

BOOL CDvmDatasetMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDatasetMap *p = (CDvmDatasetMap*)pDest;

	return CDvmMapObject::CopyOwn(pDest);
}

CBaseObject* CDvmDatasetMap::Clone()
{
	CDvmDatasetMap *p = new CDvmDatasetMap();
	Copy(p);
	return p;
}

BOOL CDvmDatasetMap::CanPaste(UINT nClassID)
{
	if (nClassID == DMPCLASSID_CDVMDATAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDvmDatasetMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDataMapKey)
	{
		pNew = new CDvmDataMap();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetMapKey)
	{
		pNew = new CDvmDatasetMap();
	}

	return pNew;
}

CExBaseObject* CDvmDatasetMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DMPCLASSID_CDVMDATAMAP)
	{
		pNew = new CDvmDataMap();
	}
	else if (nClassID == DMPCLASSID_CDVMDATASETMAP)
	{
		pNew = new CDvmDataMap();
	}

	return pNew;
}


CDvmMapObject* CDvmDatasetMap::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	CDvmDataMap *pNew = new CDvmDataMap();
	pNew->SetMap(pStand, pMap);

#ifdef DVM_USE_MAP
	((CDvmData*)pStand)->m_pDvmMapObj = pNew;

	if (pMap != NULL)
	{
		((CDvmData*)pMap)->m_pDvmMapObj = pNew;
	}
#endif

	return pNew;
}


CDvmDataMap* CDvmDatasetMap::FindMapData(const CString &strDataID)
{
	CDvmDataMap *pFind = (CDvmDataMap*)FindByID(strDataID);

	return pFind;
}

BOOL CDvmDatasetMap::FindMapData(const CString &strDataID, CString &strMapID, CString &strMapName)
{
	CDvmDataMap *pFind = FindMapData(strDataID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	strMapName = pFind->m_strMapName;
	strMapID   = pFind->m_strMapID;

	return TRUE;
}


CDvmDataMap* CDvmDatasetMap::FindDataByMapID(const CString &strMapID)
{
	POS pos = GetHeadPosition();
	CDvmDataMap *p = NULL;
	CDvmDataMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataMap *)GetNext(pos);

		if (p->m_strMapID == strMapID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDvmDatasetMap::FindDataByMapID(const CString &strMapID, CString &strDataID, CString &strDataName)
{
	CDvmDataMap *pFind = FindDataByMapID(strMapID);
	
	if (pFind == NULL)
	{
		return FALSE;
	}

	strDataName = pFind->m_strName;
	strDataID   = pFind->m_strID;

	return TRUE;
}

void CDvmDatasetMap::TransToMap(CDvmDataset *pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmDataMap *pMap = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDataset->GetNext(pos);
		pMap = FindMapData(pData->m_strID);

		if (pMap != NULL)
		{
			ReplaceDvmValueID(pData, pData->m_strID, pMap->m_strMapID);
			pData->m_strID = pMap->m_strMapID;
			pData->m_strName = pMap->m_strMapName;
#ifdef exbase_not_use_m_dwReserved
			pData->m_dwItemData = 1;
#else
			pData->m_dwReserved = 1;
#endif
		}
	}
}

void CDvmDatasetMap::TransFromMap(CDvmDataset *pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmDataMap *pMap = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDataset->GetNext(pos);
		pMap = FindDataByMapID(pData->m_strID);

		if (pMap != NULL)
		{
			TransFromMap(pMap, pData);
			//ReplaceDvmValueID(pData, pData->m_strID, pMap->m_strID);
			pData->m_strID = pMap->m_strID;
			pData->m_strName = pMap->m_strName;
		}
	}
}

void CDvmDatasetMap::TransFromMap(CDvmDataMap *pDataMap, CDvmData *pData)
{
	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValueMap *pValueMap = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		pValueMap = pDataMap->FindByMap(pValue->m_strID);

		if (pValueMap != NULL)
		{
			pValue->m_strID = pValueMap->m_strID;
			pValue->m_strName = pValueMap->m_strName;
		}
	}
}

void CDvmDatasetMap::ReplaceDvmValueID(CExBaseList *pList, const CString &strSrc, const CString &strDest)
{
	CExBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		p->m_strID.Replace(strSrc, strDest);

		ReplaceDvmValueID((CExBaseList*)p, strSrc, strDest);
	}
}


CDvmDataMap* CDvmDatasetMap::AddDvmMap(CDvmData *pStand, CDvmData *pDest)
{
	CDvmDataMap *pFind = NULL;
	
	if (m_bAddMapFindByStand)
	{
		pFind = (CDvmDataMap*)FindDvmMap_Stand(pStand);
	}
	else
	{
		pFind = (CDvmDataMap*)FindDvmMap_Dest(pDest);
	}

	if (pFind == NULL)
	{
		pFind = new CDvmDataMap();
		AddNewChild(pFind);
	}

	pFind->SetMap(pStand, pDest);

#ifdef DVM_USE_MAP
	pStand->m_pDvmMapObj = pFind;

	if (pDest != NULL)
	{
		pDest->m_pDvmMapObj = pFind;
	}
#endif

	return pFind;
}

CString CDvmDatasetMap::GetDvmCmpID()
{
	return m_pStand->m_strID;
}


BOOL CDvmDatasetMap::CanFindDvmMapChild(UINT nClassID)
{
	if ((nClassID == DMPCLASSID_CDVMDATAMAP)
		|| (nClassID == DMPCLASSID_CDVMVALUEMAP))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CDvmDatasetMap::SetDataset_Map(CDvmDataset *pDataset_Map)
{
	m_pMap = pDataset_Map;

	if (m_pMap == NULL)
	{
		m_strMapName.Empty();
		m_strMapID.Empty();
		m_strLdviceMap.Empty();
	}
	else
	{
		m_strMapID = m_pMap->m_strID;
		m_strMapName = m_pMap->m_strName;
		m_strLdviceMap = ((CExBaseObject*)m_pMap->GetParent())->m_strID;
	}
}

void CDvmDatasetMap::GetAllMaps(CExBaseList &listVarMaps)
{
	CString  m_strLdviceMap;
	CString  m_strLdvice;
	CDvmMapObject *pNew = NULL;

	if (m_strLdviceMap != m_strLdvice && m_strLdvice.GetLength() > 0)
	{
		if (listVarMaps.FindByID(m_strLdvice) == NULL)
		{
			pNew = new CDvmMapObject();
			pNew->m_strID = m_strLdvice;
			pNew->m_strName = m_strLdvice;
			pNew->m_strMapID = m_strLdviceMap;
			pNew->m_strMapName = m_strLdviceMap;
			listVarMaps.AddTail(pNew);
		}
	}

	CDvmMapObject::GetAllMaps(listVarMaps);
}

void CDvmDatasetMap::ClearDatasetMap()
{
	if (m_pStand == NULL)
	{
		return;
	}

	CDvmDataset *pDataset = (CDvmDataset *)m_pStand;
 	POS pos = pDataset->GetHeadPosition();
 	CDvmData *pData = NULL;
 
 	while (pos != NULL)
 	{
 		pData = (CDvmData *)pDataset->GetNext(pos);
		pData->ResetDvmMap();
 		//pData->m_dwReserved = 0;
 	}

	if (m_pMap == NULL)
	{
		return;
	}

	pDataset = (CDvmDataset *)m_pMap;
	pos = pDataset->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		pData->ResetDvmMap();
		//pData->m_dwReserved = 0;
	}
}

CString CDvmDatasetMap::GetDvmCmpPropGridPropertyName()
{
	CString strName;

    strName.Format(_T("%s_(%s)"), m_pStand->m_strName.GetString(), m_pStand->m_strID.GetString());
	long nFullMapCount = 0;
	long nTotalCount = 0;
	GetMapsCount(nFullMapCount, nTotalCount);
	strName.AppendFormat(_T("------------------%d/%d"), nFullMapCount, nTotalCount);

	return strName;
}

void CDvmDatasetMap::GetMapsCount(long &nFullMapCount, long &nTotalCount)
{
	if (m_pStand == NULL)
	{
		return;
	}

	CString strID = m_pStand->m_strID;

	//对于定值、压板、设备参数数据集，分子为匹配映射的数据个数，分母为目标数据集中数据个数
	if (strID.Find(_T("Setting")) >= 0 || strID.Find(_T("Ena")) >= 0 || strID.Find(_T("Parameter")) >= 0)
	{
		CDvmDataset *pMap = (CDvmDataset *)m_pMap;

		if (pMap != NULL)
		{
			nTotalCount = pMap->GetCount();
		}
	}
	else
	{
		nTotalCount = GetCount();
	}

	nFullMapCount = GetCount() - m_nCmpErrCount;
}

BOOL CDvmDatasetMap::IsAllMaped()
{
	if (m_pStand == NULL || m_pMap == NULL)
	{
		return FALSE;
	}

	long nFullMapCount = 0;
	long nTotalCount = 0;
	GetMapsCount(nFullMapCount, nTotalCount);

	if (nFullMapCount == nTotalCount)
	{
		return TRUE;
	}

	//对于跨数据集映射，需要根据m_pStand的ID，查找相同源数据集的映射对象，累加统计已映射的数据的数量
	CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)GetParent();
	POS pos = pLDeviceMap->GetHeadPosition();
	CDvmDatasetMap *pDatasetMap = NULL;
	long nAllFullMapCount = 0;

	while (pos != NULL)
	{
		pDatasetMap = (CDvmDatasetMap *)pLDeviceMap->GetNext(pos);

		if (pDatasetMap->m_pStand == NULL || pDatasetMap->m_pMap == NULL)
		{
			continue;
		}

		if (pDatasetMap->m_pStand->m_strID != m_pStand->m_strID)
		{
			continue;
		}

		long nMapTotalCount = 0;
		pDatasetMap->GetMapsCount(nFullMapCount, nMapTotalCount);
		nAllFullMapCount += nFullMapCount;
	}

	if (nAllFullMapCount == nTotalCount)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CDvmDatasetMap::HasValidMap()
{
	BOOL bValid = FALSE;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataMap *pDataMap = (CDvmDataMap *)GetNext(pos);

		if (pDataMap->m_strMapName.GetLength() > 0 || pDataMap->m_strMapID.GetLength())
		{
			bValid = TRUE;
			break;
		}
	}

	return bValid;
}