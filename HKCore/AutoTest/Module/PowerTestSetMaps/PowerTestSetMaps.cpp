//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PowerTestSetMaps.cpp  CPowerTestSetMaps


#include "stdafx.h"
#include "PowerTestSetMaps.h"

CPowerTestSetMaps::CPowerTestSetMaps()
{
	//初始化属性

	//初始化成员变量
}

CPowerTestSetMaps::~CPowerTestSetMaps()
{
}

long CPowerTestSetMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CPowerTestSetMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CPowerTestSetMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPowerTestSetMaps::InitAfterRead()
{
}

BOOL CPowerTestSetMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPowerTestSetMaps *p = (CPowerTestSetMaps*)pObj;

	return TRUE;
}

BOOL CPowerTestSetMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPowerTestSetMaps *p = (CPowerTestSetMaps*)pDest;

	return TRUE;
}

CBaseObject* CPowerTestSetMaps::Clone()
{
	CPowerTestSetMaps *p = new CPowerTestSetMaps();
	Copy(p);
	return p;
}

BOOL CPowerTestSetMaps::CanPaste(UINT nClassID)
{
	if (nClassID == SETMAPMNGRCLASSID_CSETMAP)
	{
		return TRUE;
	}
	else if (nClassID == SETMAPMNGRCLASSID_CPARAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPowerTestSetMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetMapKey)
	{
		pNew = new CSetMap();
	}
	else if (strClassID == pXmlKeys->m_strCParaMapKey)
	{
		pNew = new CSysParaMap();
	}

	return pNew;
}

CExBaseObject* CPowerTestSetMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SETMAPMNGRCLASSID_CSETMAP)
	{
		pNew = new CSetMap();
	}
	else if (nClassID == SETMAPMNGRCLASSID_CPARAMAP)
	{
		pNew = new CSysParaMap();
	}

	return pNew;
}

BOOL CPowerTestSetMaps::SaveXmlFile(const CString &strFile)
{
	return CExBaseObject::SaveXmlFile(strFile,CPowerTestSetMapsXmlRWKeys::g_pXmlKeys);
}

CSetMap* CPowerTestSetMaps::FindSetMapByFullPath(const CString &strFullPath)
{
	CSetMap *pSetMap = NULL;
	CSetMap *pFind = NULL;

	POS pos_map = GetHeadPosition();

	while(pos_map)
	{
		pSetMap = (CSetMap*)GetNext(pos_map);

		if ((pSetMap->GetClassID() == SETMAPMNGRCLASSID_CSETMAP)&&(pSetMap->m_strMap == strFullPath))
		{
			pFind = pSetMap;
			break;
		} 
	}

	return pFind;
}

CSysParaMap* CPowerTestSetMaps::FindSysParaMapByFullPath(const CString &strFullPath)
{
	CSysParaMap *pFind = NULL;
	CSysParaMap *pSysParaMap = NULL;

	POS pos_map = GetHeadPosition();

	while(pos_map)
	{
		pSysParaMap = (CSysParaMap*)GetNext(pos_map);

		if ((pSysParaMap->GetClassID() == SETMAPMNGRCLASSID_CPARAMAP)&&(pSysParaMap->m_strMap == strFullPath))
		{
			pFind = pSysParaMap;
			break;
		} 
	}

	return pFind;
}