//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetMap.cpp  CSetMap


#include "stdafx.h"
#include "SetMap.h"

CSetMap::CSetMap()
{
	//初始化属性

	//初始化成员变量
}

CSetMap::~CSetMap()
{
}

long CSetMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapKey, oNode, m_strMap);
	return 0;
}

long CSetMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapKey, oElement, m_strMap);
	return 0;
}

long CSetMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMap);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMap);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMap);
	}
	return 0;
}

void CSetMap::InitAfterRead()
{
}

BOOL CSetMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSetMap *p = (CSetMap*)pObj;

	if(m_strMap != p->m_strMap)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSetMap *p = (CSetMap*)pDest;

	p->m_strMap = m_strMap;
	return TRUE;
}

CBaseObject* CSetMap::Clone()
{
	CSetMap *p = new CSetMap();
	Copy(p);
	return p;
}

