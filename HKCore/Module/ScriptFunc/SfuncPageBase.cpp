//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SfuncPageBase.cpp  CSfuncPageBase


#include "stdafx.h"
#include "SfuncPageBase.h"

CSfuncPageBase::CSfuncPageBase()
{
	//初始化属性

	//初始化成员变量
}

CSfuncPageBase::~CSfuncPageBase()
{
}

long CSfuncPageBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSfuncPageBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

