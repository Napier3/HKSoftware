//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CExprMngrGlobal.cpp

#include "stdafx.h"
#include "ExprMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CCExprMngrXmlRWKeys

CExprMngrXmlRWKeys* CExprMngrXmlRWKeys::g_pXmlKeys = NULL;
long CExprMngrXmlRWKeys::g_nEXPRef = 0;


CExprMngrXmlRWKeys::CExprMngrXmlRWKeys()
{
	m_strCPpExprTypesMngrKey = L"expr-mngr";
	m_strCPpExprSendTypesKey = L"expr-snd";
	m_strCPpExprRcvTypesKey = L"expr-rcv";
	m_strCPpExprTypeKey = L"expr-type";
	m_strCPpExprKey = L"expr";
	m_strValueKey = L"value";
}

CExprMngrXmlRWKeys::~CExprMngrXmlRWKeys()
{
}

CExprMngrXmlRWKeys* CExprMngrXmlRWKeys::Create()
{
	g_nEXPRef++;

	if (g_nEXPRef == 1)
	{
		g_pXmlKeys = new CExprMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CExprMngrXmlRWKeys::Release()
{
	g_nEXPRef--;

	if (g_nEXPRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCExprMngrConstGlobal

long CCExprMngrConstGlobal::g_nGlobalRef = 0;
CCExprMngrConstGlobal* CCExprMngrConstGlobal::g_pGlobal = NULL;


CCExprMngrConstGlobal::CCExprMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CCExprMngrConstGlobal::~CCExprMngrConstGlobal()
{
}

CCExprMngrConstGlobal* CCExprMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCExprMngrConstGlobal();
	}

	return g_pGlobal;
}

void CCExprMngrConstGlobal::Release()
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
