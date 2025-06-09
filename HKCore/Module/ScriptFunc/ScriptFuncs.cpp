//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFuncs.cpp  CScriptFuncs


#include "stdafx.h"
#include "ScriptFuncs.h"

//////////////////////////////////////////////////////////////////////////
//CScriptFuncs
CScriptFuncs::CScriptFuncs()
{
	//初始化属性

	//初始化成员变量
}

CScriptFuncs::~CScriptFuncs()
{
}

BOOL CScriptFuncs::OpenConfigFile(const CString &strFile)
{
	CString strTemp;
	strTemp = _P_GetConfigPath();
	strTemp += strFile;

	BOOL b = OpenXmlFile(strTemp, CScriptFuncXmlRWKeys::CScriptFuncsKey(), CScriptFuncXmlRWKeys::g_pXmlKeys);

	//xlang_TranslateByResourceFile(this, strFile);
	//20161212  lijq
	xlang_TranslateByResourceFileEx(this, strFile);

	SortByID();

	return b;
}

long CScriptFuncs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CScriptFuncs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CScriptFuncs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CScriptFuncXmlRWKeys *pXmlKeys = (CScriptFuncXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCScriptFuncKey)
	{
		pNew = new CScriptFunc();
	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
//CScriptFuncsList
CScriptFuncsList* CScriptFuncsList::g_pScriptFuncsList = NULL;
long CScriptFuncsList::g_nScriptFuncsList = 0;

CScriptFuncsList::CScriptFuncsList()
{

}

CScriptFuncsList::~CScriptFuncsList()
{

}

void CScriptFuncsList::Create()
{
	g_nScriptFuncsList++;

	if (g_nScriptFuncsList == 1)
	{
		g_pScriptFuncsList = new CScriptFuncsList();
	}
}

void CScriptFuncsList::Release()
{
	g_nScriptFuncsList--;

	if (g_nScriptFuncsList == 0)
	{
		delete g_pScriptFuncsList;
		g_pScriptFuncsList = NULL;
	}
}

CScriptFuncs* CScriptFuncsList::OpenFile(const CString &strFile)
{
	CString strID = strFile;
	strID.MakeLower();

	CScriptFuncs *pFuncs = (CScriptFuncs*)g_pScriptFuncsList->FindByID(strID);

	if (pFuncs != NULL)
	{
		return pFuncs;
	}

	pFuncs = new CScriptFuncs();
	pFuncs->OpenConfigFile(strFile);
	pFuncs->m_strID = strID;
	pFuncs->m_strName = strID;
	g_pScriptFuncsList->AddTail(pFuncs);

	return pFuncs;
}

