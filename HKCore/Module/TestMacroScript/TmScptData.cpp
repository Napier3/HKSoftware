//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptData.cpp  CTmScptData


#include "stdafx.h"
#include "TmScptData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmScptData::CTmScptData()
{
	//初始化属性

	//初始化成员变量
}

CTmScptData::~CTmScptData()
{
}

long CTmScptData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CTmScptData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

CExBaseObject* CTmScptData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTmScptValueKey)
	{
		pNew = new CTmScptValue();
	}

	return pNew;
}

CBaseObject* CTmScptData::Clone()
{
	CTmScptData *p = new CTmScptData();
	Copy(p);
	return p;
}

BOOL CTmScptData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTmScptData *p = (CTmScptData*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CTmScptValue* CTmScptData::FindByValue(const CString &strValue)
{
	POS pos = GetHeadPosition();
	CTmScptValue *p = NULL;
	CTmScptValue *pFind = NULL;

	while (pos != NULL)
	{
		p = (CTmScptValue *)GetNext(pos);

		if (strValue == p->m_strValue)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CTmScptData::RunScript(CTestMacro *pMacro, CShortData *pData)
{
// 	if (m_strOldData == pData->m_strValue)
// 	{
// 		return FALSE;
// 	}

	m_strOldData = pData->m_strValue;
	CTmScptValue *pScptValue = (CTmScptValue*)FindByValue(pData->m_strValue);

	if (pScptValue == NULL)
	{
		return FALSE;
	}
	else
	{
		return pScptValue->RunScript(pMacro);
	}
}

