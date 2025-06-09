//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmMapObject.cpp  CDvmMapObject


#include "stdafx.h"
#include "DvmMapObject.h"
//#include "DvmMapTool.h"
#include "DvmLDeviceMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL g_bDvmCmdDataNameFull = FALSE;

CDvmMapObject::CDvmMapObject()
{
	//初始化属性

	//初始化成员变量
	m_pStand          = NULL;
	m_pMap            = NULL;
	m_pStringCmp_Name = NULL;
	m_pStringCmp_ID   = NULL;
	m_nCmpResult      = 0;   //对象的不同之处
	m_dwItemDataStand = 0;
	m_dwItemDataMap   = 0;
	m_nCmpRate        = 0;
	m_nCmpErrCount = 0;
}

CDvmMapObject::~CDvmMapObject()
{
	if (m_pStringCmp_Name != NULL)
	{
		delete m_pStringCmp_Name;
		m_pStringCmp_Name = NULL;
	}

	if (m_pStringCmp_ID != NULL)
	{
		delete m_pStringCmp_ID;
		m_pStringCmp_ID = NULL;
	}
}

long CDvmMapObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapNameKey, oNode, m_strMapName);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIDKey, oNode, m_strMapID);

	return 0;
}

long CDvmMapObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapNameKey, oElement, m_strMapName);
	xml_SetAttributeValue(pXmlKeys->m_strMapIDKey, oElement, m_strMapID);
	return 0;
}

void CDvmMapObject::InitAfterRead()
{
}

BOOL CDvmMapObject::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmMapObject *p = (CDvmMapObject*)pObj;

	if(m_strMapName != p->m_strMapName)
	{
		return FALSE;
	}

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDvmMapObject::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmMapObject *p = (CDvmMapObject*)pDest;

	p->m_strMapName = m_strMapName;
	p->m_strMapID = m_strMapID;
	p->m_strName = m_strName;
	p->m_strID = m_strID;

	return TRUE;
}

CDvmMapObject* CDvmMapObject::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	ASSERT (FALSE);
	return NULL;
}

void CDvmMapObject::StringCmp()
{
	if (m_pStand == NULL || m_pMap == NULL)
	{
		return;
	}

	if (m_pStringCmp_ID == NULL)
	{
		m_pStringCmp_ID = new CStringCmp;
	}

	if (m_pStringCmp_Name == NULL)
	{
		m_pStringCmp_Name = new CStringCmp;
	}

	if ((m_pStand->m_strName.GetLength() > 0) && (m_pMap->m_strName.GetLength() > 0) )
	{
		//if (!m_pStringCmp_Name->IsSameStrCmp(&m_pStand->m_strName, &m_pMap->m_strName))
		{
			m_pStringCmp_Name->StrCmp(&m_pStand->m_strName, &m_pMap->m_strName);
		}
	}

	if (m_pStand->m_strID.GetLength() > 0 && m_pMap->m_strID.GetLength() > 0)
	{
		//if (!m_pStringCmp_ID->IsSameStrCmp(&m_pStand->m_strID, &m_pMap->m_strID))
		{
			m_pStringCmp_ID->StrCmp(&m_pStand->m_strID, &m_pMap->m_strID);
		}
	}
}

void CDvmMapObject::FreeStringCmp()
{
	if (m_pStringCmp_Name != NULL)
	{
		delete m_pStringCmp_Name;
		m_pStringCmp_Name = NULL;
	}

	if (m_pStringCmp_ID != NULL)
	{
		delete m_pStringCmp_ID;
		m_pStringCmp_ID = NULL;
	}
}

CStringCmpBlocks* CDvmMapObject::GetNameCmp_Stand()
{
	if (m_pStringCmp_Name == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_Name->m_oStrCmpBlks1;
}

CStringCmpBlocks* CDvmMapObject::GetNameCmp_Dest()
{
	if (m_pStringCmp_Name == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_Name->m_oStrCmpBlks2;
}

CStringCmpBlocks* CDvmMapObject::GetIDCmp_Stand()
{
	if (m_pStringCmp_ID == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_ID->m_oStrCmpBlks1;
}

CStringCmpBlocks* CDvmMapObject::GetIDCmp_Dest()
{
	if (m_pStringCmp_ID == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_ID->m_oStrCmpBlks2;
}

void CDvmMapObject::SetMap0(CExBaseObject *pMap)
{
	pMap->m_dwReserved = 1;

	m_pMap = pMap;

	if (m_pMap != NULL)
	{
		m_strMapID = m_pMap->m_strID;
		m_strMapName = m_pMap->m_strName;
	}
	else
	{
		m_strMapID.Empty();
		m_strMapName.Empty();
	}
}

void CDvmMapObject::SetStand0(CExBaseObject *pStand)
{
	ASSERT (m_pStand == NULL);

	m_pStand = pStand;

	if (m_pStand != NULL)
	{
		m_strID = m_pStand->m_strID;
		m_strName = m_pStand->m_strName;
	}
	else
	{
		m_strID.Empty();
		m_strName.Empty();
	}
}

void CDvmMapObject::SetMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	m_pStand = pStand;
	m_pMap = pMap;

	m_strName = m_pStand->m_strName;
	m_strID = m_pStand->m_strID;

	if (m_pMap != NULL)
	{
		m_strMapID = m_pMap->m_strID;
		m_strMapName = m_pMap->m_strName;
	}
}

BOOL CDvmMapObject::IsInChild_Stand(CExBaseObject *pStand)
{
	POS pos = GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);

		if (p->m_pStand == pStand)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CDvmMapObject::IsInChild_Map(CExBaseObject *pMap)
{
	POS pos = GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);

		if (p->m_pMap == pMap)
		{
			return TRUE;
		}
	}

	return FALSE;
}

CDvmMapObject* CDvmMapObject::FindDvmMap_Stand(CExBaseObject *pStand)
{
#ifdef DVM_USE_MAP
	if (pStand->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		return (CDvmMapObject*)((CDvmData*)pStand)->m_pDvmMapObj;
	}
	else if (pStand->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		return (CDvmMapObject*)((CDvmValue*)pStand)->m_pDvmMapObj;
	}
#endif
	

	POS pos = GetHeadPosition();
	CDvmMapObject *p = NULL;
	CDvmMapObject *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);

		if (p->m_pStand == pStand)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmMapObject* CDvmMapObject::FindDvmMap_Dest(CExBaseObject *pDest)
{
	if (pDest == NULL)
	{
		return NULL;
	}

#ifdef DVM_USE_MAP
	if (pDest->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		return (CDvmMapObject*)((CDvmData*)pDest)->m_pDvmMapObj;
	}
	else if (pDest->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		return (CDvmMapObject*)((CDvmValue*)pDest)->m_pDvmMapObj;
	}
#endif


	POS pos = GetHeadPosition();
	CDvmMapObject *p = NULL;
	CDvmMapObject *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);

		if (p->m_pMap == pDest)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CDvmMapObject::AddNullDvmMap_Stand()
{
	CExBaseList *pStand = (CExBaseList*)m_pStand;
	POS pos = pStand->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmMapObject *pDvmMap = NULL;

	while (pos != NULL)
	{
		p = pStand->GetNext(pos);

// 		if (p->m_dwReserved == 1)
// 		{
// 			continue;
// 		}

		pDvmMap = FindDvmMap_Stand(p);

		if (pDvmMap == NULL)
		{
			pDvmMap = CreateNewDvmMap(p, NULL);
			AddNewChild(pDvmMap);
		}
		//在已有数据集上，创建新的数据集映射时，pDvmMap已经不为空
		//但是需要在新的数据集映射下添加数据映射对象
// 		else
// 		{
// 			if (FindIndex(pDvmMap) == -1)
// 			{
// 				AddNewChild((CDvmMapObject *)pDvmMap->Clone());
// 			}
// 		}
		
		pDvmMap->AddNullDvmMap_Stand();
	}
}

void CDvmMapObject::SortDvmMap_Stand()
{
	CExBaseList *pStand = (CExBaseList*)m_pStand;
	POS pos = pStand->GetHeadPosition();
	CExBaseList listTemp;
	long nIndex = 0;
	CExBaseObject *p = NULL;
	CDvmMapObject *pDvmMap = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pStand->GetNext(pos);

		POS posMap = GetHeadPosition();

		while(posMap != NULL)
		{
			pDvmMap = (CDvmMapObject*)GetNext(posMap);

			if (pDvmMap->m_pStand == p)
			{
				listTemp.AddTail(pDvmMap);
			}
		}
	}

	RemoveAll();
	Append(listTemp);
	listTemp.RemoveAll();

	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDvmMap = (CDvmMapObject *)GetNext(pos);
		pDvmMap->SortDvmMap_Stand();
	}
}

long CDvmMapObject::FindDvmMapObj_ByStand(UINT nClassID, CExBaseObject *pStand, CExBaseList &listDvmMap, BOOL bFindIdSame)
{
	POS pos = GetHeadPosition();
	CDvmMapObject *pDvmMap = NULL;

	if (!CanFindDvmMapChild(nClassID))
	{
		return 0;
	}

	while (pos != NULL)
	{
		pDvmMap = (CDvmMapObject *)GetNext(pos);

		if (pDvmMap->GetClassID() == nClassID)
		{
			if (pStand == pDvmMap->m_pStand)
			{
				listDvmMap.AddTail(pDvmMap);
			}
			else
			{
				//把ID相同的也添加到链表中
				if (bFindIdSame)
				{
					if (pStand->m_strID == pDvmMap->m_pStand->m_strID)
					{
						listDvmMap.AddTail(pDvmMap);
					}
				}
			}
		}

		pDvmMap->FindDvmMapObj_ByStand(nClassID, pStand, listDvmMap, bFindIdSame);
	}

	return listDvmMap.GetCount();
}

CDvmMapObject* CDvmMapObject::FindDvmMapObj_ByStand(UINT nClassID, CExBaseObject *pStand)
{
	CExBaseList listMap;
	CDvmMapObject *pDvmMap = NULL;
	long nCount = FindDvmMapObj_ByStand(nClassID, pStand, listMap);

	if (nCount > 0)
	{
		pDvmMap = (CDvmMapObject *)listMap.GetHead();
	}

	listMap.RemoveAll();

	return pDvmMap;
}

long CDvmMapObject::FindDvmMapObj_ByMap(UINT nClassID, CExBaseObject *pMap, CExBaseList &listDvmMap)
{
	POS pos = GetHeadPosition();
	CDvmMapObject *pDvmMap = NULL;

	if (!CanFindDvmMapChild(nClassID))
	{
		return 0;
	}

	while (pos != NULL)
	{
		pDvmMap = (CDvmMapObject *)GetNext(pos);

		if (pDvmMap->GetClassID() == nClassID)
		{
			if (pMap == pDvmMap->m_pMap)
			{
				listDvmMap.AddTail(pDvmMap);
			}
		}

		pDvmMap->FindDvmMapObj_ByMap(nClassID, pMap, listDvmMap);
	}

	return listDvmMap.GetCount();
}

 CDvmMapObject* CDvmMapObject::FindDvmMapObj(CExBaseObject *pStand, CExBaseObject *pMap)
 {
	 POS pos = GetHeadPosition();
	 CDvmMapObject *pDvmMap = NULL;
	 CDvmMapObject *pDvmMapFind = NULL;

	 while (pos != NULL)
	 {
		 pDvmMap = (CDvmMapObject *)GetNext(pos);

		 if (pMap == pDvmMap->m_pMap && pStand == pDvmMap->m_pStand)
		 {
			 pDvmMapFind = pDvmMap;
			 break;
		 }
	 }

	 return pDvmMapFind;
 }

CDvmMapObject* CDvmMapObject::FindDvmMapObj_ByMap(UINT nClassID, CExBaseObject *pMap)
{
	CExBaseList listMap;
	CDvmMapObject *pDvmMap = NULL;
	long nCount = FindDvmMapObj_ByMap(nClassID, pMap, listMap);

	if (nCount > 0)
	{
		pDvmMap = (CDvmMapObject *)listMap.GetHead();
	}

	listMap.RemoveAll();

	return pDvmMap;
}

CDvmMapObject* CDvmMapObject::FindDvmMapObj_ByStandID(const CString &strStandID, CExBaseObject *pMap)
{
	POS pos = GetHeadPosition();
	CDvmMapObject *pDvmMap = NULL;
	CDvmMapObject *pDvmMapFind = NULL;

	while (pos != NULL)
	{
		pDvmMap = (CDvmMapObject *)GetNext(pos);

		if (pMap == pDvmMap->m_pMap && strStandID == pDvmMap->m_pStand->m_strID)
		{
			pDvmMapFind = pDvmMap;
			break;
		}
	}

	return pDvmMapFind;
}

BOOL CDvmMapObject::CanFindDvmMapChild(UINT nClassID)
{
	return TRUE;
}

void CDvmMapObject::DeleteMap()
{
	POS pos = GetHeadPosition();
	CDvmMapObject *pMap = NULL;
	m_strMapName.Empty();
	m_strMapID.Empty();

	m_pStand->InitReserved(0x0FFFFFFF);

	if (m_pMap != NULL)
	{
		m_pMap->InitReserved(0x0FFFFFFF);
	}

	while (pos != NULL)
	{
		pMap = (CDvmMapObject *)GetNext(pos);
		pMap->DeleteMap();
	}

	if (m_pMap == NULL)
	{
		return;
	}

#ifdef DVM_USE_MAP
	if (m_pMap->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		((CDvmData*)m_pMap)->m_pDvmMapObj = NULL;
	}
	else if (m_pMap->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		((CDvmValue*)m_pMap)->m_pDvmMapObj = NULL;
	}
#endif

	m_pMap = NULL;
}

BOOL CDvmMapObject::IsMapEmpty()
{
	POS pos = GetHeadPosition();
	CDvmMapObject *pMap = NULL;
	BOOL bEmpty = TRUE;

	while (pos != NULL)
	{
		pMap = (CDvmMapObject *)GetNext(pos);
		
		if (!pMap->IsMapEmpty())
		{
			bEmpty = FALSE;
		}
	}

	if (bEmpty)
	{
		if (m_strMapID.GetLength() > 0)
		{
			bEmpty = FALSE;
		}
	}

	return bEmpty;
}

CDvmMapObject* CDvmMapObject::FindMapObj(const CString &strID, const CString &strMapID)
{
	CDvmMapObject *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);

		if (p->m_strID == strID && p->m_strMapID == strMapID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//获取MAP对象
void CDvmMapObject::GetAllMaps(CExBaseList &listVarMaps)
{
	if (m_strID != m_strMapID)
	{
		CDvmMapObject *pNew  =new CDvmMapObject();
		pNew->m_strID = m_strID;
		pNew->m_strMapID = m_strMapID;
		pNew->m_strName = m_strName;
		pNew->m_strMapName = m_strMapName;
		pNew->m_pStand = m_pStand;
		pNew->m_pMap = m_pMap;
		listVarMaps.AddTail(pNew);
	}

	POS pos = GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)GetNext(pos);
		p->GetAllMaps(listVarMaps);
	}
}

BOOL CDvmMapObject::IsMapFull()
{
	if (m_pMap == NULL)
	{
		return FALSE;
	}

	if (m_pStand == NULL)
	{
		return FALSE;
	}

	if (g_bDvmCmdDataNameFull != 0)
	{
		if (m_pStand->m_strName != m_pMap->m_strName && m_pMap->m_strID != m_pStand->m_strID)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CDvmMapObject::CountErrMapCount()
{
	m_nCmpErrCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmMapObject *pMapObj = NULL;

// 	if (!IsMapFull())
// 	{
// 		m_nCmpErrCount++;
// 	}

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DMPCLASSID_CDVMVALUEMAP)
		{
			continue;
		}

		pMapObj = (CDvmMapObject *)pObj;
		
		if (!pMapObj->IsMapFull())
		{
			BOOL IsFull = TRUE;		//20231103 luozibing 当任一子结点中存在m_pmap则说明存在数据
			POS pos = pMapObj->GetHeadPosition();
			while(pos != NULL)
			{
				CDvmValueMap * Tmp = (CDvmValueMap *)pMapObj->GetNext(pos);
				if(Tmp->m_pMap != NULL)
					IsFull = FALSE;
			}
			if(IsFull)
			{
				m_nCmpErrCount++;
			}
		}

		pMapObj->CountErrMapCount();
	}
}

CString CDvmMapObject::GetMapIDByValueID(const CString &strID)
{
	CString strMapID;

	if (m_pMap != NULL)
	{
		if (m_strID == strID)
		{
			return m_pMap->m_strID;
		}
	}

	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		CDvmMapObject *pMapObj = (CDvmMapObject *)GetNext(pos);

		strMapID = pMapObj->GetMapIDByValueID(strID);

		if (strMapID.GetLength() > 0)
		{
			return strMapID;
		}
	}

	return strMapID;
}

CDvmMapObject* CDvmMapObject::GetMapByID(const CString &strID)
{
	CDvmMapObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CDvmMapObject *pMapObj = (CDvmMapObject *)GetNext(pos);

		if (pMapObj->m_pMap != NULL)
		{
			if (pMapObj->m_strID == strID)
			{
				return pMapObj;
			}
		}

		pObj = pMapObj->GetMapByID(strID);

		if (pObj != NULL)
		{
			return pObj;
		}
	}

	return pObj;
}

CDvmMapObject* CDvmMapObject::GetMapByIDEx(const CString &strID)
{
	CDvmMapObject *pNewDataMap = NULL;
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)GetAncestor(DMPCLASSID_CDVMDATASETMAP);
	CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)pDatasetMap->GetParent();
	POS pos = pLDeviceMap->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDatasetMap *pMap = (CDvmDatasetMap *)pLDeviceMap->GetNext(pos);

		if (pMap->m_strID != pDatasetMap->m_strID)
		{
			continue;
		}

		pNewDataMap = pMap->GetMapByID(strID);

		if (pNewDataMap != NULL)
		{
			break;
		}
	}

	return pNewDataMap;
}

CDvmMapObject* dvmmap_NewMpObject(CExBaseObject *pStand, CExBaseObject *pMap, long nCmpRate)
{
	CDvmMapObject *pNew = new CDvmMapObject();
	pNew->m_pStand = pStand;
	pNew->m_pMap = pMap;
	pNew->m_nCmpRate = nCmpRate;

	return pNew;
}

CDvmMapObject* dvmmap_GetMpObject(CExBaseObject *pDvmObject)
{
	if (pDvmObject == NULL)
	{
		return NULL;
	}

	if (pDvmObject->GetClassID() == DMPCLASSID_CDVMDATAMAP)
	{
		return (CDvmMapObject*)pDvmObject;
	}

	if (pDvmObject->GetClassID() == DMPCLASSID_CDVMVALUEMAP)
	{
		return (CDvmMapObject*)pDvmObject;
	}

#ifdef DVM_USE_MAP
	if (pDvmObject->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		return (CDvmMapObject*)((CDvmData*)pDvmObject)->m_pDvmMapObj;
	}

	if (pDvmObject->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		return (CDvmMapObject*)((CDvmValue*)pDvmObject)->m_pDvmMapObj;
	}
#endif

	return NULL;
}

