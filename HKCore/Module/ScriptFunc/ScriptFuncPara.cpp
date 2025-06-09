//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFuncPara.cpp  CScriptFuncPara


#include "stdafx.h"
#include "ScriptFuncPara.h"

CScriptFuncPara::CScriptFuncPara()
{
	//初始化属性

	//初始化成员变量
}

CScriptFuncPara::~CScriptFuncPara()
{
}

long CScriptFuncPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CScriptFuncPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

