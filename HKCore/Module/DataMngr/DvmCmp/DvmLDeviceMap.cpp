//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDatasetMap.cpp  CDvmLDeviceMap


#include "stdafx.h"
#include "DvmLDeviceMap.h"
#include "../../API/FileApi.h"

CDvmLDeviceMap::CDvmLDeviceMap()
{
	//初始化属性

	//初始化成员变量
}

CDvmLDeviceMap::~CDvmLDeviceMap()
{
}

long CDvmLDeviceMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CDvmLDeviceMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CDvmMapObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CDvmLDeviceMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDvmLDeviceMap::InitAfterRead()
{
}

BOOL CDvmLDeviceMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmLDeviceMap *p = (CDvmLDeviceMap*)pObj;

	return CDvmMapObject::IsEqualOwn(pObj);
}

BOOL CDvmLDeviceMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmLDeviceMap *p = (CDvmLDeviceMap*)pDest;

	return CDvmMapObject::CopyOwn(pDest);
}

CBaseObject* CDvmLDeviceMap::Clone()
{
	CDvmLDeviceMap *p = new CDvmLDeviceMap();
	Copy(p);
	return p;
}

BOOL CDvmLDeviceMap::CanPaste(UINT nClassID)
{
	if (nClassID == DMPCLASSID_CDVMDATASETMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDvmLDeviceMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDatasetMapKey)
	{
		pNew = new CDvmDatasetMap();
	}

	return pNew;
}

CExBaseObject* CDvmLDeviceMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DMPCLASSID_CDVMDATASETMAP)
	{
		pNew = new CDvmDatasetMap();
	}

	return pNew;
}

CDvmMapObject* CDvmLDeviceMap::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	CDvmDatasetMap *pNew = new CDvmDatasetMap();
	pNew->SetMap(pStand, pMap);
	pNew->m_strLdvice = m_strID;

	return pNew;
}


BOOL CDvmLDeviceMap::OpenDvmMapFile(const CString &strFile)
{
	DeleteAll();
	CString strTemp = strFile;
	strTemp = ChangeFilePostfix(strFile, g_strDvmDataMapFilePostfix);
	
	m_bDvmLDeviceMapExist = OpenXmlFile(strTemp, CDataMngrXmlRWKeys::g_pXmlKeys);

	return m_bDvmLDeviceMapExist;
}

BOOL CDvmLDeviceMap::IsDvmMapFileExist()
{
	return (GetCount() > 0);
}

CDvmDatasetMap* CDvmLDeviceMap::FindDsMap(const CString &strLdId, const CString &strDsID)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		if (p->m_strLdvice == strLdId && p->m_strID == strDsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDataMap* CDvmLDeviceMap::FindDataMap(const CString &strDataPath)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDataMap *pFind = NULL;
	CDvmDataMap *pData = NULL;
	POS posData = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);
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

CDvmDataMap* CDvmLDeviceMap::FindDataMapObj(const CString &strLdID, const CString &strDataPath)
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

CDvmDataMap* CDvmLDeviceMap::FindDataMapObj(const CString &strDataPath)
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

BOOL CDvmLDeviceMap::FindDataMap(const CString &strDataPath, CString &strDataMapID)
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

CDvmDatasetMap* CDvmLDeviceMap::FindByDsMap(const CString &strLdId, const CString &strDsID)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		if (p->m_strLdviceMap == strLdId && p->m_strMapID == strDsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDatasetMap* CDvmLDeviceMap::FindDsMap(const CString &strLdId, const CString &strDsID, const CString &strLdMapId, const CString &strDsMapID)
{
	POS pos = GetHeadPosition();
	CDvmDatasetMap *p = NULL;
	CDvmDatasetMap *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDatasetMap *)GetNext(pos);

		if (p->m_strLdvice == strLdId          && p->m_strID == strDsID
			&& p->m_strLdviceMap == strLdMapId && p->m_strMapID == strDsMapID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}
CDvmDatasetMap* CDvmLDeviceMap::FindDsMap(const CString &strDsPath)
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

CDvmDatasetMap* CDvmLDeviceMap::FindByDsMap(const CString &strDsPath)
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

void CDvmLDeviceMap::TransFromMap(const CString &strLdId, const CString &strDsID, CDvmData *pDvmData)
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

void CDvmLDeviceMap::TransToMap(CDvmDataset *pDataset, const CString &strSrcDsID)
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

CDvmDatasetMap* CDvmLDeviceMap::AddDvmMap(CDvmDataset *pStand, CDvmDataset *pDest)
{
// 	CDvmDatasetMap *pFind = (CDvmDatasetMap*)FindDvmMap_Stand(pStand);
// 
// 	if (pFind != NULL)
// 	{
// 		return pFind;
// 	}

	CDvmDatasetMap *pNew = new CDvmDatasetMap();
	pNew->SetMap(pStand, pDest);
	AddNewChild(pNew);

	pNew->m_strLdvice = m_strID;

	if (pDest != NULL)
	{
		pNew->m_strLdviceMap = ((CExBaseObject*)pDest->GetParent())->m_strID;
	}

	return pNew;
}


BOOL CDvmLDeviceMap::CanFindDvmMapChild(UINT nClassID)
{
	if ((nClassID == DMPCLASSID_CDVMDATASETMAP)
		|| (nClassID == DMPCLASSID_CDVMDATAMAP)
		|| (nClassID == DMPCLASSID_CDVMVALUEMAP))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CDvmDatasetMap* CDvmLDeviceMap::AddDvmMap(CDvmDatasetMap *pDatasetMap, CDvmDataset *pDest, BOOL bNewStandDataset)
{
	if (pDatasetMap->m_pMap == NULL)
	{
		pDatasetMap->m_pMap = pDest;
		return pDatasetMap;
	}
	else
	{
		CDvmDatasetMap *pFind = (CDvmDatasetMap*)FindDvmMapObj(pDatasetMap->m_pStand, pDest);

		if (pFind == NULL)
		{
			pFind = (CDvmDatasetMap *)FindDvmMapObj_ByStandID(pDatasetMap->m_pStand->m_strID, pDest);
		}

		if (pFind == NULL)
		{
			if (bNewStandDataset)
			{
				//此处需要New一个标准数据集，防止双加打开数据集映射页面时，页面展示的数据映射错乱
				CDvmDataset *pStand = (CDvmDataset*)pDatasetMap->m_pStand;
				CDvmDataset *pNewStand = (CDvmDataset *)pStand->CloneEx(TRUE, TRUE);
				CExBaseList *pParent = (CExBaseList *)pDatasetMap->m_pStand->GetParent();
				pParent->AddNewChild(pNewStand);

				POS pos = pNewStand->GetHeadPosition();
				CDvmData *pData = NULL;

				while (pos != NULL)
				{
					pData = (CDvmData *)pNewStand->GetNext(pos);
					pData->ResetDvmMapEx();
				}

				pFind = (CDvmDatasetMap*)AddDvmMap((CDvmDataset*)pNewStand, pDest);
			}
			else
			{
				pFind = (CDvmDatasetMap*)AddDvmMap((CDvmDataset*)pDatasetMap->m_pStand, pDest);
			}
		}

		return pFind;
	}
}

