//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDatasetMap.cpp  CDvmDeviceMap


#include "stdafx.h"
#include "DvmDeviceMap.h"
#include "../../API/FileApi.h"

CDvmDeviceMap::CDvmDeviceMap()
{
	//初始化属性

	//初始化成员变量
	m_bDvmDeviceMapExist = FALSE;
	m_bModifiedFlag = FALSE;
}

CDvmDeviceMap::~CDvmDeviceMap()
{
	m_listDatasetMap.RemoveAll();
}

long CDvmDeviceMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CDvmDeviceMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CDvmDeviceMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDvmDeviceMap::InitAfterRead()
{
	m_listDatasetMap.RemoveAll();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList listLdevice;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DMPCLASSID_CDVMLDVICEMAP)
		{
			m_listDatasetMap.Append((CExBaseList*)p);
		}
		else if (p->GetClassID() == DMPCLASSID_CDVMDATASETMAP)
		{//兼容之前版本的映射关系
			CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)p;
			CDvmLDeviceMap *pLdeviceMap = (CDvmLDeviceMap *)FindByID(pDatasetMap->m_strLdvice);

			if (pLdeviceMap == NULL)
			{
				pLdeviceMap = (CDvmLDeviceMap *)listLdevice.FindByID(pDatasetMap->m_strLdvice);
			}

			if (pLdeviceMap == NULL)
			{
				pLdeviceMap = new CDvmLDeviceMap();
				pLdeviceMap->m_strID = pDatasetMap->m_strLdvice;
				pLdeviceMap->m_strName = pLdeviceMap->m_strID;
				listLdevice.AddTail(pLdeviceMap);
			}

			pLdeviceMap->AddNewChild(p);
			Remove(p);
			m_listDatasetMap.AddTail(p);
		}
	}

	AppendEx(listLdevice);
	listLdevice.RemoveAll();
}

BOOL CDvmDeviceMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmDeviceMap *p = (CDvmDeviceMap*)pObj;

	return CDvmMapObject::IsEqualOwn(pObj);
}

BOOL CDvmDeviceMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDeviceMap *p = (CDvmDeviceMap*)pDest;

	return CDvmMapObject::CopyOwn(pDest);
}

CBaseObject* CDvmDeviceMap::Clone()
{
	CDvmDeviceMap *p = new CDvmDeviceMap();
	Copy(p);
	return p;
}

BOOL CDvmDeviceMap::CanPaste(UINT nClassID)
{
	if (nClassID == DMPCLASSID_CDVMDEVICEMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDvmDeviceMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDatasetMapKey)
	{
		pNew = new CDvmDatasetMap();
	}
	else if (strClassID == pXmlKeys->m_strCDvmLDeviceMapKey)
	{
		pNew = new CDvmLDeviceMap();
	}

	return pNew;
}

CExBaseObject* CDvmDeviceMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DMPCLASSID_CDVMDATASETMAP)
	{
		pNew = new CDvmDatasetMap();
	}

	return pNew;
}

CDvmMapObject* CDvmDeviceMap::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	CDvmLDeviceMap *pNew = new CDvmLDeviceMap();
	pNew->SetMap(pStand, pMap);

	return pNew;
}

void CDvmDeviceMap::AddNullDvmMap_Stand()
{
	CExBaseList *pStand = (CExBaseList*)m_pStand;
	POS pos = pStand->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmMapObject *pDvmMap = NULL;

	while (pos != NULL)
	{
		p = pStand->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			continue;
		}

		pDvmMap = FindDvmMap_Stand(p);

		if (pDvmMap == NULL)
		{
			pDvmMap = CreateNewDvmMap(p, NULL);
			AddNewChild(pDvmMap);
		}

		pDvmMap->AddNullDvmMap_Stand();
	}
}

BOOL CDvmDeviceMap::OpenDvmMapFile(const CString &strFile)
{
	DeleteAll();
	CString strTemp = strFile;
	strTemp = ChangeFilePostfix(strFile, g_strDvmDataMapFilePostfix);
	m_strFile = strTemp;
	
	m_bDvmDeviceMapExist = OpenXmlFile(strTemp, CDataMngrXmlRWKeys::g_pXmlKeys);

	return m_bDvmDeviceMapExist;
}

BOOL CDvmDeviceMap::IsDvmMapFileExist()
{
	return (GetCount() > 0);
}

CDvmDatasetMap* CDvmDeviceMap::FindDsMap(const CString &strLdId, const CString &strDsID)
{
	POS pos = m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)m_listDatasetMap.GetNext(pos);

		if (p->m_strLdvice == strLdId && p->m_strID == strDsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDataMap* CDvmDeviceMap::FindDataMap(const CString &strDataPath)
{
	POS pos = m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDataMap *pFind = NULL;
	CDvmDataMap *pData = NULL;
	POS posData = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)m_listDatasetMap.GetNext(pos);
		posData = p->GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CDvmDataMap *)p->GetNext(posData);

			if (pData->m_strID == strDataPath)
			{
				pFind = pData;
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

CDvmDataMap* CDvmDeviceMap::FindDataMapObj(const CString &strLdID, const CString &strDataPath)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDataMap *pFind = NULL;
	CDvmDataMap *pData = NULL;
	POS posData = NULL;
	CString strDsID;
	CString strDataID;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		if (p->m_strLdvice != strLdID)
		{
			continue;
		}

		posData = p->GetHeadPosition();
		strDsID = p->m_strID + _T("$");

		if (strDataPath.Find(strDsID) >= 0)
		{
			strDataID = strDataPath.Mid(strDsID.GetLength());
		}
		else
		{
			continue;
		}

		while (posData != NULL)
		{
			pData = (CDvmDataMap *)p->GetNext(posData);

			if (pData->m_strID == strDataID)
			{
				pFind = pData;
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

CDvmDataMap* CDvmDeviceMap::FindDataMapObj(const CString &strDataPath)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDataMap *pFind = NULL;
	CDvmDataMap *pData = NULL;
	POS posData = NULL;
	CString strDsID;
	CString strDataID;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		posData = p->GetHeadPosition();
		strDsID = p->m_strID + _T("$");

		if (strDataPath.Find(strDsID) >= 0)
		{
			strDataID = strDataPath.Mid(strDsID.GetLength());
		}
		else
		{
			strDataID = strDataPath;
		}

		while (posData != NULL)
		{
			pData = (CDvmDataMap *)p->GetNext(posData);

			if (pData->m_strID == strDataID)
			{
				pFind = pData;
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

CDvmDataMap* CDvmDeviceMap::FindDataMapObj_DsKey(const CString &strDsKey, const CString &strDataPath)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDataMap *pFind = NULL;
	CDvmDataMap *pData = NULL;
	POS posData = NULL;
	CString strDsID;
	CString strDataID;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		posData = p->GetHeadPosition();
		strDsID = p->m_strID + _T("$");

		if (strDataPath.Find(strDsID) >= 0)
		{
			strDataID = strDataPath.Mid(strDsID.GetLength());
		}
		else
		{
			strDataID = strDataPath;
		}

		if (p->m_strID.Find(strDsKey) < 0)
		{
			continue;
		}

		while (posData != NULL)
		{
			pData = (CDvmDataMap *)p->GetNext(posData);

			if (pData->m_strID == strDataID)
			{
				pFind = pData;
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

BOOL CDvmDeviceMap::FindDataMap(const CString &strDataPath, CString &strDataMapID)
{
	CDvmDataMap *pData = FindDataMap(strDataPath);

	if (pData != NULL)
	{
		strDataMapID = pData->m_strMapID;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CDvmDatasetMap* CDvmDeviceMap::FindByDsMap(const CString &strLdId, const CString &strDsID)
{
	POS pos = m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)m_listDatasetMap.GetNext(pos);

		if (p->m_strLdviceMap == strLdId && p->m_strMapID == strDsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDatasetMap* CDvmDeviceMap::FindDsMap(const CString &strLdId, const CString &strDsID, const CString &strLdMapId, const CString &strDsMapID)
{
	POS pos = m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)m_listDatasetMap.GetNext(pos);

		if (p->m_strLdvice == strLdId          && p->m_strID == strDsID
			&& p->m_strLdviceMap == strLdMapId && p->m_strMapID == strDsMapID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}
CDvmDatasetMap* CDvmDeviceMap::FindDsMap(const CString &strDsPath)
{
	CDvmDatasetMap *pFind = NULL;
	long nPos = strDsPath.Find(_T("LLN0$"));

	if (nPos >= 0)
	{
		CString strLdId, strDsId;
		strLdId = strDsPath.Left(nPos);
		strDsId = strDsPath.Mid(nPos);
		pFind = FindDsMap(strLdId, strDsId);
	}
	else
	{
		CDvmDatasetMap *p = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			p = (CDvmDatasetMap *)GetNext(pos);

			if (p->m_strID == strDsPath)
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

CDvmDatasetMap* CDvmDeviceMap::FindByDsMap(const CString &strDsPath)
{
	CDvmDatasetMap *pFind = NULL;
	long nPos = strDsPath.Find(_T("LLN0$"));

	if (nPos >= 0)
	{
		CString strLdId, strDsId;
		strLdId = strDsPath.Left(nPos);
		strDsId = strDsPath.Mid(nPos);
		pFind = FindByDsMap(strLdId, strDsId);
	}
	else
	{
		CDvmDatasetMap *p = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			p = (CDvmDatasetMap *)GetNext(pos);

			if (p->m_strMapID == strDsPath)
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

void CDvmDeviceMap::TransFromMap(const CString &strLdId, const CString &strDsID, CDvmData *pDvmData)
{
	CDvmDatasetMap *pDsMap = FindByDsMap(strLdId, strDsID);

	if(pDsMap == NULL)
	{
		return;
	}

	CDvmDataMap *pDataMap = pDsMap->FindDataByMapID(pDvmData->m_strID);

	if (pDataMap != NULL)
	{
		pDsMap->ReplaceDvmValueID(pDvmData, pDvmData->m_strID, pDataMap->m_strID);
		pDvmData->m_strID = pDataMap->m_strID;
		pDvmData->m_strName = pDataMap->m_strName;
	}
}

void CDvmDeviceMap::TransToMap(CDvmDataset *pDataset, const CString &strSrcDsID)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		if (p->m_strID == strSrcDsID)
		{
			p->TransToMap(pDataset);
		}
	}
}

CDvmLDeviceMap* CDvmDeviceMap::AddDvmMap(CDvmLogicDevice *pStand, CDvmLogicDevice *pDest)
{
// 	CDvmLDeviceMap *pFind = (CDvmLDeviceMap*)FindDvmMap_Stand(pStand);
// 
// 	if (pFind != NULL)
// 	{
// 		return pFind;
// 	}

	CDvmLDeviceMap *pNew = new CDvmLDeviceMap();
	pNew->SetMap(pStand, pDest);
	AddNewChild(pNew);

	return pNew;
}

CDvmDatasetMap* CDvmDeviceMap::FindDsMap_ByMapID(const CString &strLdId, const CString &strDsID)
{
	POS pos = m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)m_listDatasetMap.GetNext(pos);

		if (p->m_strLdviceMap == strLdId && p->m_strMapID == strDsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDatasetMap* CDvmDeviceMap::FindDsMap_ByStandDest(CDvmDataset *pDsStand, CDvmDataset *pDsDest)
{
	CDvmLDeviceMap *pLdeviceMap = NULL;
	CDvmDatasetMap *p = NULL, *pFind = NULL;
	POS posLd = GetHeadPosition();
	POS posDs = NULL;

	while (posLd != NULL)
	{
		pLdeviceMap = (CDvmLDeviceMap *)GetNext(posLd);
		posDs = pLdeviceMap->GetHeadPosition();

		while (posDs != NULL)
		{
			p = (CDvmDatasetMap *)pLdeviceMap->GetNext(posDs);

			if (p->m_pStand == pDsStand && p->m_pMap == pDsDest)
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

BOOL dvmmap_GetDvmMapModifiedFlag(CExBaseObject *pObj)
{
	CDvmDeviceMap *pDeviceMap = (CDvmDeviceMap*)pObj->GetAncestor(DMPCLASSID_CDVMDEVICEMAP);

	if (pDeviceMap == NULL)
	{
		return FALSE;
	}

	return pDeviceMap->m_bModifiedFlag;
}

void dvmmap_SetDvmMapModifiedFlag(CExBaseObject *pObj, BOOL b)
{
	CDvmDeviceMap *pDeviceMap = (CDvmDeviceMap*)pObj->GetAncestor(DMPCLASSID_CDVMDEVICEMAP);

	if (pDeviceMap == NULL)
	{
		return;
	}

	pDeviceMap->m_bModifiedFlag = b;
}
