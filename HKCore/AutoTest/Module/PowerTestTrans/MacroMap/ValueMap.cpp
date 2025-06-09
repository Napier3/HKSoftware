//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ValueMap.cpp  CValueMap


#include "stdafx.h"
#include "ValueMap.h"

CValueMap::CValueMap()
{
	//初始化属性

	//初始化成员变量
}

CValueMap::~CValueMap()
{
}

long CValueMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapIDKey, oNode, m_strMapID);
	xml_GetAttibuteValue(pXmlKeys->m_strMapNameKey, oNode, m_strMapName);
	return 0;
}

long CValueMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapIDKey, oElement, m_strMapID);
	xml_SetAttributeValue(pXmlKeys->m_strMapNameKey, oElement, m_strMapName);
	return 0;
}

long CValueMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMapID);
		BinarySerializeCalLen(oBinaryBuffer, m_strMapName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMapID);
		BinarySerializeRead(oBinaryBuffer, m_strMapName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMapID);
		BinarySerializeWrite(oBinaryBuffer, m_strMapName);
	}
	return 0;
}

void CValueMap::InitAfterRead()
{
}

BOOL CValueMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CValueMap *p = (CValueMap*)pObj;

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	if(m_strMapName != p->m_strMapName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CValueMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CValueMap *p = (CValueMap*)pDest;

	p->m_strMapID = m_strMapID;
	p->m_strMapName = m_strMapName;
	return TRUE;
}

CBaseObject* CValueMap::Clone()
{
	CValueMap *p = new CValueMap();
	Copy(p);
	return p;
}

