//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataMap.cpp  CDvmDataMap


#include "stdafx.h"
#include "DvmDataMap.h"

CDvmDataMap::CDvmDataMap()
{
	//初始化属性

	//初始化成员变量
}

CDvmDataMap::~CDvmDataMap()
{
#ifdef DVM_USE_MAP
	if (m_pStand != NULL)
	{
		if (m_pStand->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)m_pStand)->m_pDvmMapObj = NULL;
		}
	}

	if (m_pMap != NULL)
	{
		if (m_pMap->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)m_pMap)->m_pDvmMapObj = NULL;
		}
	}
#endif
}

long CDvmDataMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmMapObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmDataMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmMapObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CDvmDataMap::InitAfterRead()
{
}

BOOL CDvmDataMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmDataMap *p = (CDvmDataMap*)pObj;

	return CDvmMapObject::IsEqualOwn(pObj);
}

BOOL CDvmDataMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataMap *p = (CDvmDataMap*)pDest;

	return CDvmMapObject::CopyOwn(pDest);
}

CBaseObject* CDvmDataMap::Clone()
{
	CDvmDataMap *p = new CDvmDataMap();
	Copy(p);
	return p;
}

BOOL CDvmDataMap::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CDvmDataMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDvmValueMapKey)
	{
		pNew = new CDvmValueMap();
	}

	return pNew;
}

CExBaseObject* CDvmDataMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}


CDvmMapObject* CDvmDataMap::CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap)
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


CDvmValueMap* CDvmDataMap::FindByMap(const CString &strMapID)
{
	POS pos = GetHeadPosition();
	CDvmValueMap *pMap = NULL;
	CDvmValueMap *pFind = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmValueMap *)GetNext(pos);

		if (pMap->m_strMapID == strMapID)
		{
			pFind = pMap;
			break;
		}
	}

	return pFind;
}

CDvmValueMap* CDvmDataMap::AddDvmMap(CDvmValue *pStand, CDvmValue *pDest)
{
	CDvmValueMap *pFind = (CDvmValueMap*)FindDvmMap_Dest(pDest);

	if (pFind == NULL)
	{
		pFind = new CDvmValueMap();
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
//20231103 huangliang 
CDvmValueMap* CDvmDataMap::AddDvmMap(CDvmValue *pStand, CDvmData *pDest)
{
	CDvmValueMap *pFind = (CDvmValueMap*)FindDvmMap_Dest(pDest);

	if (pFind == NULL)
	{
		pFind = new CDvmValueMap();
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

BOOL CDvmDataMap::CanFindDvmMapChild(UINT nClassID)
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


void CDvmDataMap::SetMap0(CExBaseObject *pMap)
{
	CDvmMapObject::SetMap0(pMap);

	if (pMap != NULL)
	{
#ifdef DVM_USE_MAP
		((CDvmData*)pMap)->m_pDvmMapObj = this;
#endif
	}
}


void CDvmDataMap::SetStand0(CExBaseObject *pStand)
{
	CDvmMapObject::SetStand0(pStand);

	if (pStand != NULL)
	{
		//ASSERT (((CDvmData*)pStand)->m_pDvmMapObj == NULL);

#ifdef DVM_USE_MAP
		((CDvmData*)pStand)->m_pDvmMapObj = this;
#endif
	}
}