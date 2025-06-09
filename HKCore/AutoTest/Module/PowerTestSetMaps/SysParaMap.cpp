//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SysParaMap.cpp  CSysParaMap


#include "stdafx.h"
#include "SysParaMap.h"

CSysParaMap::CSysParaMap()
{
	//初始化属性

	//初始化成员变量
}

CSysParaMap::~CSysParaMap()
{
}

long CSysParaMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapKey, oNode, m_strMap);
	return 0;
}

long CSysParaMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CPowerTestSetMapsXmlRWKeys *pXmlKeys = (CPowerTestSetMapsXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapKey, oElement, m_strMap);
	return 0;
}

long CSysParaMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSysParaMap::InitAfterRead()
{
}

BOOL CSysParaMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSysParaMap *p = (CSysParaMap*)pObj;

	if(m_strMap != p->m_strMap)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSysParaMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSysParaMap *p = (CSysParaMap*)pDest;

	p->m_strMap = m_strMap;
	return TRUE;
}

CBaseObject* CSysParaMap::Clone()
{
	CSysParaMap *p = new CSysParaMap();
	Copy(p);
	return p;
}

