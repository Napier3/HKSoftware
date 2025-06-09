//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ClassDefMngrGlobal.cpp

#include "stdafx.h"
#include "ClassDefMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CClassDefMngrXmlRWKeys

CClassDefMngrXmlRWKeys* CClassDefMngrXmlRWKeys::g_pXmlKeys = NULL;
long CClassDefMngrXmlRWKeys::g_nMngrRef = 0;


CClassDefMngrXmlRWKeys::CClassDefMngrXmlRWKeys()
{
	m_strCCommcmdRefKey = L"CommcmdRef";
	m_strCTestMacroRefKey = L"TestMacroRef";
	m_strCTestMacroGroupKey = L"TestMacroGroup";
	m_strCTestMacroToolBarKey = L"TestMacroToolBar";
	m_strPicKey = L"pic";
	m_strFormatKey = L"format";
	m_strValueKey = L"value";
}

CClassDefMngrXmlRWKeys::~CClassDefMngrXmlRWKeys()
{
}

CClassDefMngrXmlRWKeys* CClassDefMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CClassDefMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CClassDefMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CClassDefMngrConstGlobal

long CClassDefMngrConstGlobal::g_nGlobalRef = 0;
CClassDefMngrConstGlobal* CClassDefMngrConstGlobal::g_pGlobal = NULL;


CClassDefMngrConstGlobal::CClassDefMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CClassDefMngrConstGlobal::~CClassDefMngrConstGlobal()
{
}

CClassDefMngrConstGlobal* CClassDefMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CClassDefMngrConstGlobal();
	}

	return g_pGlobal;
}

void CClassDefMngrConstGlobal::Release()
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
