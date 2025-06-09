//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpAnalyseStringVal.cpp  CEpAnalyseStringVal


#include "stdafx.h"
#include "EpAnalyseStringVal.h"

CEpAnalyseStringVal::CEpAnalyseStringVal()
{
	//初始化属性

	//初始化成员变量
}

CEpAnalyseStringVal::~CEpAnalyseStringVal()
{
}

long CEpAnalyseStringVal::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strValue2Key, oNode, m_strValue2);
	return 0;
}

long CEpAnalyseStringVal::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strValue2Key, oElement, m_strValue2);
	return 0;
}

BOOL CEpAnalyseStringVal::IsValueIn(const CString &strValue)
{
	if (m_strValue2.GetLength() > 0)
	{
		long nVal1 = CString_To_long(m_strValue);;
		long nVal2 = CString_To_long(m_strValue2);;
		long nVal = CString_To_long(strValue);;

		if (nVal1 < nVal2)
		{
			return ((nVal1 <= nVal) && (nVal <= nVal2));
		}
		else
		{return ((nVal2 <= nVal) && (nVal <= nVal1));
		}
	}
	else
	{
		return (m_strValue == strValue);
	}
}

