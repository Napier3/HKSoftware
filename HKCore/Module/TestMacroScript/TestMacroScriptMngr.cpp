//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroScriptMngr.cpp  CTestMacroScriptMngr


#include "stdafx.h"
#include "TestMacroScriptMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacroScriptMngr::CTestMacroScriptMngr()
{
	//初始化属性

	//初始化成员变量
	
}

CTestMacroScriptMngr::~CTestMacroScriptMngr()
{
}

long CTestMacroScriptMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTestMacroScriptMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CTestMacroScriptMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacroScriptKey)
	{
		pNew = new CTestMacroScript();
	}

	return pNew;
}
