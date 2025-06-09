//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DinWzdFromSclGinCh.cpp  CDinWzdFromSclGinCh


#include "stdafx.h"
#include "DinWzdFromSclGinCh.h"

CDinWzdFromSclGinCh::CDinWzdFromSclGinCh()
{
	//初始化属性

	//初始化成员变量
}

CDinWzdFromSclGinCh::~CDinWzdFromSclGinCh()
{
}

long CDinWzdFromSclGinCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAppIDKey, oNode, m_strAppID);
	xml_GetAttibuteValue(pXmlKeys->m_strGsChIndexKey, oNode, m_strGsChIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	return 0;
}

long CDinWzdFromSclGinCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAppIDKey, oElement, m_strAppID);
	xml_SetAttributeValue(pXmlKeys->m_strGsChIndexKey, oElement, m_strGsChIndex);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	return 0;
}

void CDinWzdFromSclGinCh::InitAfterRead()
{
}

BOOL CDinWzdFromSclGinCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDinWzdFromSclGinCh *p = (CDinWzdFromSclGinCh*)pObj;

	if(m_strAppID != p->m_strAppID)
	{
		return FALSE;
	}

	if(m_strGsChIndex != p->m_strGsChIndex)
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDinWzdFromSclGinCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDinWzdFromSclGinCh *p = (CDinWzdFromSclGinCh*)pDest;

	p->m_strAppID = m_strAppID;
	p->m_strGsChIndex = m_strGsChIndex;
	p->m_strDataType = m_strDataType;
	return TRUE;
}

CBaseObject* CDinWzdFromSclGinCh::Clone()
{
	CDinWzdFromSclGinCh *p = new CDinWzdFromSclGinCh();
	Copy(p);
	return p;
}

