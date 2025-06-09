//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommExprGlobal.cpp

#include "stdafx.h"
#include "CommExprGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CCommExprXmlRWKeys

CCommExprXmlRWKeys* CCommExprXmlRWKeys::g_pXmlKeys = NULL;
long CCommExprXmlRWKeys::g_nMngrRef = 0;


CCommExprXmlRWKeys::CCommExprXmlRWKeys()
{
	m_strCCommExprKey = L"expr";
	m_strValueKey = L"value";
	m_strOptrKey = L"optr";
}

CCommExprXmlRWKeys::~CCommExprXmlRWKeys()
{
}

CCommExprXmlRWKeys* CCommExprXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CCommExprXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCommExprXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCommExprConstGlobal

long CCommExprConstGlobal::g_nGlobalRef = 0;
CCommExprConstGlobal* CCommExprConstGlobal::g_pGlobal = NULL;


CCommExprConstGlobal::CCommExprConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CCommExprConstGlobal::~CCommExprConstGlobal()
{
}

CCommExprConstGlobal* CCommExprConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCommExprConstGlobal();
	}

	return g_pGlobal;
}

void CCommExprConstGlobal::Release()
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
