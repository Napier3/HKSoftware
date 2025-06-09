//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroScript.cpp  CTestMacroScript


#include "stdafx.h"
#include "TestMacroScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacroScript::CTestMacroScript()
{
	//初始化属性

	//初始化成员变量
}

CTestMacroScript::~CTestMacroScript()
{
}

long CTestMacroScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacroIDKey, oNode, m_strMacroID);
	m_strID = m_strMacroID;
	xml_GetAttibuteValue(pXmlKeys->m_strDLLKey, oNode, m_strUIDLL);

	return 0;
}

long CTestMacroScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacroIDKey, oElement, m_strMacroID);
	xml_SetAttributeValue(pXmlKeys->m_strDLLKey, oElement, m_strUIDLL);

	return 0;
}

CExBaseObject* CTestMacroScript::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTmScptDataKey)
	{
		pNew = new CTmScptData();
	}

	return pNew;
}

CBaseObject* CTestMacroScript::Clone()
{
	CTestMacroScript *p = new CTestMacroScript();
	Copy(p);
	return p;
}

BOOL CTestMacroScript::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTestMacroScript *p = (CTestMacroScript*)pDest;

	p->m_strMacroID = m_strMacroID;
	return TRUE;
}


void CTestMacroScript::InitScript(CTestMacro *pMacro)
{
// 	if (m_bHasInit)
// 	{
// 		return;
// 	}

	CExBaseList oList;
	oList.Append(pMacro->GetFaultParas());
	oList.Append(pMacro->GetSysParas());

	POS pos = oList.GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)oList.GetNext(pos);
		RunScript(pMacro, pData);
	}

	oList.RemoveAll();
//	m_bHasInit = TRUE;
}

BOOL CTestMacroScript::RunScript(CTestMacro *pMacro, CShortData *pData)
{
	CTmScptData *pScptData = (CTmScptData*)FindByID(pData->m_strID);

	if (pScptData == NULL)
	{
		return FALSE;
	}
	else
	{
		return pScptData->RunScript(pMacro, pData);
	}
}

