//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenBase.cpp  CEpCapGenBase


#include "stdafx.h"
#include "EpCapGenBase.h"

CEpCapGenBase::CEpCapGenBase()
{
	//初始化属性

	//初始化成员变量
}

CEpCapGenBase::~CEpCapGenBase()
{
}

long CEpCapGenBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);
	return 0;
}

long CEpCapGenBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	return 0;
}

BOOL CEpCapGenBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpCapGenBase *p = (CEpCapGenBase*)pObj;

	if(m_strFile != p->m_strFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapGenBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEpCapGenBase *p = (CEpCapGenBase*)pDest;

	p->m_strFile = m_strFile;
	return TRUE;
}

CBaseObject* CEpCapGenBase::Clone()
{
	CEpCapGenBase *p = new CEpCapGenBase();
	Copy(p);
	return p;
}

