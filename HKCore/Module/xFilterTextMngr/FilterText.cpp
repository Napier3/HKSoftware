//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterText.cpp  CFilterText


#include "stdafx.h"
#include "FilterText.h"

CFilterText::CFilterText()
{
	//初始化属性

	//初始化成员变量
}

CFilterText::~CFilterText()
{
}

long CFilterText::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey, oNode, m_strName);	
	//xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);
	m_strID = m_strName;

	CGlobalDataMngrXmlRWKeys *pXmlKeys = (CGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CFilterText::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);

	CGlobalDataMngrXmlRWKeys *pXmlKeys = (CGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CFilterText::InitAfterRead()
{
}

BOOL CFilterText::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CFilterText *p = (CFilterText*)pObj;

	return TRUE;
}

BOOL CFilterText::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CFilterText *p = (CFilterText*)pDest;

	return TRUE;
}

CExBaseObject* CFilterText::Clone()
{
	CFilterText *p = new CFilterText();
	Copy(p);
	return p;
}

