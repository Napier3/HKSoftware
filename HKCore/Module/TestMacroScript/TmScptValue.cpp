//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptValue.cpp  CTmScptValue


#include "stdafx.h"
#include "TmScptValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmScptValue::CTmScptValue()
{
	//初始化属性

	//初始化成员变量
}

CTmScptValue::~CTmScptValue()
{
}

long CTmScptValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CTmScptValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

CExBaseObject* CTmScptValue::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTmScptCmdKey)
	{
		pNew = new CTmScptCmd();
	}
	else if (strClassID == pXmlKeys->m_strCTmScptGroupCmdKey)
	{
		pNew = new CTmScptGroupCmd();
	}

	return pNew;
}

CBaseObject* CTmScptValue::Clone()
{
	CTmScptValue *p = new CTmScptValue();
	Copy(p);
	return p;
}

BOOL CTmScptValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTmScptValue *p = (CTmScptValue*)pDest;

	p->m_strValue = m_strValue;
	return TRUE;
}

BOOL CTmScptValue::RunScript(CTestMacro *pMacro)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCmd = NULL;
	UINT nClassID = 0;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pCmd = GetNext(pos);
		nClassID = pCmd->GetClassID();
		bTrue |= ((CTmScptCmd*)pCmd)->RunScript(pMacro);

// 		if (nClassID == MCSCLASSID_CTMSCPTCMD)
// 		{
// 			bTrue |= ((CTmScptCmd*)pCmd)->RunScript(pMacro);
// 		}
// 		else if (nClassID == TMSCLASSID_CTMSCPTGROUPCMD)
// 		{
// 			bTrue|= ((CTmScptGroupCmd*)pCmd)->RunScript(pMacro);
// 		}
	}

	return TRUE;
}

