//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DllCallGlobal.cpp

#include "stdafx.h"
#include "DllCallGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CDllCallXmlRWKeys

CDllCallXmlRWKeys* CDllCallXmlRWKeys::g_pXmlKeys = NULL;
long CDllCallXmlRWKeys::g_nDLCLRef = 0;


CDllCallXmlRWKeys::CDllCallXmlRWKeys()
{
	m_strCFuncResultsKey = L"results";
	m_strCFuncParasKey = L"paras";
	m_strCDllCallDefMngrKey = L"dll-calls";
	m_strCDllCallDefKey = L"dll-call";
	m_strCDLLFunctionKey = L"func";
	m_strProgidKey = L"progid";
}

CDllCallXmlRWKeys::~CDllCallXmlRWKeys()
{
}

CDllCallXmlRWKeys* CDllCallXmlRWKeys::Create()
{
	g_nDLCLRef++;

	if (g_nDLCLRef == 1)
	{
		g_pXmlKeys = new CDllCallXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CDllCallXmlRWKeys::Release()
{
	g_nDLCLRef--;

	if (g_nDLCLRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CDllCallConstGlobal

long CDllCallConstGlobal::g_nGlobalRef = 0;
CDllCallConstGlobal* CDllCallConstGlobal::g_pGlobal = NULL;


CDllCallConstGlobal::CDllCallConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CDllCallConstGlobal::~CDllCallConstGlobal()
{
}

CDllCallConstGlobal* CDllCallConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDllCallConstGlobal();
	}

	return g_pGlobal;
}

void CDllCallConstGlobal::Release()
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
