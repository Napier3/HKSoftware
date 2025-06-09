//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StateWordBit.cpp  CIecCfg91StateWordBit


#include "stdafx.h"
#include "IecCfg91StateWordBit.h"

CIecCfg91StateWordBit::CIecCfg91StateWordBit()
{
	//初始化属性

	//初始化成员变量
}

CIecCfg91StateWordBit::~CIecCfg91StateWordBit()
{
}

long CIecCfg91StateWordBit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CIecCfg91StateWordBit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

BOOL CIecCfg91StateWordBit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg91StateWordBit *p = (CIecCfg91StateWordBit*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg91StateWordBit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfg91StateWordBit *p = (CIecCfg91StateWordBit*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;
	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CIecCfg91StateWordBit::Clone()
{
	CIecCfg91StateWordBit *p = new CIecCfg91StateWordBit();
	Copy(p);
	return p;
}

