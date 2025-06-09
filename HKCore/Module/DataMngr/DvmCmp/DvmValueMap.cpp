//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValueMap.cpp  CDvmValueMap


#include "stdafx.h"
#include "DvmValueMap.h"
#include "DvmLDeviceMap.h"

CDvmValueMap::CDvmValueMap()
{
	//初始化属性


	//初始化成员变量
}

CDvmValueMap::~CDvmValueMap()
{
#ifdef DVM_USE_MAP

	if (m_pStand != NULL)
	{
		((CDvmValue*)m_pStand)->m_pDvmMapObj = NULL;
	}

	if (m_pMap != NULL)
	{
		//20231103 huangliang 因新增了CDvmData与CDvmValue的映射
		if (m_pMap->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)m_pMap)->m_pDvmMapObj = NULL;
		}
		else 
		{
		((CDvmValue*)m_pMap)->m_pDvmMapObj = NULL;
	}
	}
#endif
}

long CDvmValueMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmMapObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmValueMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmMapObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CDvmValueMap::InitAfterRead()
{
}

BOOL CDvmValueMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmValueMap *p = (CDvmValueMap*)pObj;

	return CDvmMapObject::IsEqualOwn(pObj);
}

BOOL CDvmValueMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmValueMap *p = (CDvmValueMap*)pDest;

	return CDvmMapObject::CopyOwn(pDest);
}

CBaseObject* CDvmValueMap::Clone()
{
	CDvmValueMap *p = new CDvmValueMap();
	Copy(p);
	return p;
}

BOOL CDvmValueMap::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CDvmValueMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDvmValueMapKey)
	{
		pNew = new CDvmValueMap();
	}

	return pNew;
}

CExBaseObject* CDvmValueMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}


CDvmMapObject* CDvmValueMap::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
{
	CDvmValueMap *pNew = new CDvmValueMap();
	pNew->SetMap(pStand, pMap);

#ifdef DVM_USE_MAP
	((CDvmValue*)pStand)->m_pDvmMapObj = pNew;

	if (pMap != NULL)
	{
		((CDvmValue*)pMap)->m_pDvmMapObj = pNew;
	}
#endif

	return pNew;
}

CDvmValueMap* CDvmValueMap::AddDvmMap(CDvmValue *pStand, CDvmValue *pDest)
{
	CDvmValueMap *pFind = (CDvmValueMap*)FindDvmMap_Dest(pDest);

	if (pFind != NULL)
	{
		return pFind;
	}

	CDvmValueMap *pNew = new CDvmValueMap();
	pNew->SetMap(pStand, pDest);
	AddNewChild(pNew);

#ifdef DVM_USE_MAP
	pStand->m_pDvmMapObj = pNew;

	if (pDest != NULL)
	{
		pDest->m_pDvmMapObj = pNew;
	}
#endif

	return pNew;
}


BOOL CDvmValueMap::CanFindDvmMapChild(UINT nClassID)
{
	if (nClassID == DMPCLASSID_CDVMVALUEMAP)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CDvmValueMap::SetMap0(CExBaseObject *pMap)
{
	CDvmMapObject::SetMap0(pMap);

	if (pMap != NULL)
	{
#ifdef DVM_USE_MAP
		//20231103 huangliang
		if (pMap->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)pMap)->m_pDvmMapObj = this;
		}
		else if (pMap->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
		((CDvmValue*)pMap)->m_pDvmMapObj = this;
		}
#endif
	}
}


void CDvmValueMap::SetStand0(CExBaseObject *pStand)
{
	CDvmMapObject::SetStand0(pStand);

	if (pStand != NULL)
	{
#ifdef DVM_USE_MAP
		//20231103 huangliang
		if (pStand->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)pStand)->m_pDvmMapObj = this;
		}
		else if (pStand->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
		((CDvmValue*)pStand)->m_pDvmMapObj = this;
		}
#endif
	}
}

CString CDvmValueMap::GetMapID()
{
	CString strMapID;

	if (m_pMap != NULL)
	{
		strMapID = m_pMap->m_strID;
	}
	else
	{
		//通过到其它映射中，查找MapID
		strMapID = GetMapIDBySameName();
	}

	return strMapID;
}

CString CDvmValueMap::GetMapIDBySameName()
{
	if (m_pMap != NULL)
	{
		return m_pMap->m_strID;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)GetAncestor(DMPCLASSID_CDVMDATASETMAP);
	CString strDatasetID = pDatasetMap->m_strID;

	CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)pDatasetMap->GetParent();
	POS pos = pLDeviceMap->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDatasetMap *pSetMap = (CDvmDatasetMap *)pLDeviceMap->GetNext(pos);

		if (pSetMap->m_strID != strDatasetID)
		{
			continue;
		}

		//递归查询，根据ID，查找是否有映射，返回映射的ID
		CString strMapID = pSetMap->GetMapIDByValueID(m_strID);

		if (strMapID.GetLength() > 0)
		{
			return strMapID;
		}
	}

	return _T("");
}