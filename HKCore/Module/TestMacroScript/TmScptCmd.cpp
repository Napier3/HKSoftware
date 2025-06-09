//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptCmd.cpp  CTmScptCmd


#include "stdafx.h"
#include "TmScptCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmScptCmd::CTmScptCmd()
{
	//初始化属性

	//初始化成员变量
}

CTmScptCmd::~CTmScptCmd()
{
}

long CTmScptCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataIDKey, oNode, m_strDataID);
	xml_GetAttibuteValue(pXmlKeys->m_strAttrIDKey, oNode, m_strAttrID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CTmScptCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataIDKey, oElement, m_strDataID);
	xml_SetAttributeValue(pXmlKeys->m_strAttrIDKey, oElement, m_strAttrID);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

CBaseObject* CTmScptCmd::Clone()
{
	CTmScptCmd *p = new CTmScptCmd();
	Copy(p);
	return p;
}

BOOL CTmScptCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTmScptCmd *p = (CTmScptCmd*)pDest;

	p->m_strDataID = m_strDataID;
	p->m_strAttrID = m_strAttrID;
	p->m_strValue = m_strValue;
	return TRUE;
}

BOOL CTmScptCmd::RunScript(CTestMacro *pMacro)
{
	BOOL bTrue = FALSE;
	bTrue = TMS_SetDataAttrByGroupID(pMacro, m_strDataID, m_strAttrID, m_strValue);
	return bTrue;
}

