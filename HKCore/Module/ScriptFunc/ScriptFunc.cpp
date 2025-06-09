//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFunc.cpp  CScriptFunc


#include "stdafx.h"
#include "ScriptFunc.h"

CScriptFunc::CScriptFunc()
{
	//初始化属性

	//初始化成员变量
}

CScriptFunc::~CScriptFunc()
{
}

long CScriptFunc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strReturnKey, oNode, m_strReturn);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);

	return 0;
}

long CScriptFunc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strReturnKey, oElement, m_strReturn);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);

	return 0;
}

CExBaseObject* CScriptFunc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCScriptFuncParaKey)
	{
		pNew = new CScriptFuncPara();
	}

	return pNew;
}

DWORD CScriptFunc::Filter(const CString &strTxtFilter, DWORD dwMode)
{
	FilterOwn(strTxtFilter, dwMode);

#ifndef exbase_not_use_m_dwReserved
	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CScriptFunc::Filter_ID(const CString &strTxtFilter, DWORD dwMode)
{
	FilterOwn_ID(strTxtFilter, dwMode);

#ifndef exbase_not_use_m_dwReserved
	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CScriptFunc::Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode)
{
	FilterOwn_ID_Name(strTxtFilter, dwMode);

#ifndef exbase_not_use_m_dwReserved
	return m_dwReserved;
#else
	return 0;
#endif
}
DWORD CScriptFunc::Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode)
{
	FilterOwn_ID_Name_NoCase(strTxtFilter, dwMode);

#ifndef exbase_not_use_m_dwReserved
	return m_dwReserved;
#else
	return 0;
#endif
}