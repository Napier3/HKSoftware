//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageGlobal.cpp

#include "stdafx.h"
#include "XLanguageGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXLanguageXmlRWKeys

CXLanguageXmlRWKeys* CXLanguageXmlRWKeys::g_pXmlKeys = NULL;
long CXLanguageXmlRWKeys::g_nLGUGRef = 0;


CXLanguageXmlRWKeys::CXLanguageXmlRWKeys()
{
	m_strCXLanguageMngrKey = L"languages";
	m_strCXLanguageKey = L"language";
	m_strCXLangItemKey = L"item";
	m_strTranslationKey = L"translation";
	m_strCurrLanguageKey = L"curr-language";
	m_strSrcTextKey = L"src";
	m_strDebugStateKey = L"debug";
}

CXLanguageXmlRWKeys::~CXLanguageXmlRWKeys()
{
}

CXLanguageXmlRWKeys* CXLanguageXmlRWKeys::Create()
{
	g_nLGUGRef++;

	if (g_nLGUGRef == 1)
	{
		g_pXmlKeys = new CXLanguageXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXLanguageXmlRWKeys::Release()
{
	g_nLGUGRef--;

	if (g_nLGUGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CXLanguageConstGlobal

long CXLanguageConstGlobal::g_nGlobalRef = 0;
CXLanguageConstGlobal* CXLanguageConstGlobal::g_pGlobal = NULL;


CXLanguageConstGlobal::CXLanguageConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CXLanguageConstGlobal::~CXLanguageConstGlobal()
{
}

CXLanguageConstGlobal* CXLanguageConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXLanguageConstGlobal();
	}

	return g_pGlobal;
}

void CXLanguageConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
