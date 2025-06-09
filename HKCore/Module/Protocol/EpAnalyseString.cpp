//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpAnalyseString.cpp  CEpAnalyseString


#include "stdafx.h"
#include "EpAnalyseString.h"

CEpAnalyseString::CEpAnalyseString()
{
	//初始化属性

	//初始化成员变量
}

CEpAnalyseString::~CEpAnalyseString()
{
}

long CEpAnalyseString::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strStringKey, oNode, m_strString);
	return 0;
}

long CEpAnalyseString::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strStringKey, oElement, m_strString);
	return 0;
}

CExBaseObject* CEpAnalyseString::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpAnalyseStringValKey)
	{
		pNew = new CEpAnalyseStringVal();
	}

	return pNew;
}

CExBaseObject* CEpAnalyseString::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPASCLASSID_CEPANALYSESTRINGVAL)
	{
		pNew = new CEpAnalyseStringVal();
	}

	return pNew;
}

CEpAnalyseStringVal* CEpAnalyseString::FindByValue(const CString &strValue)
{
	CEpAnalyseStringVal *p = NULL;
	CEpAnalyseStringVal *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpAnalyseStringVal*)GetNext(pos);

		if (p->IsValueIn(strValue))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

