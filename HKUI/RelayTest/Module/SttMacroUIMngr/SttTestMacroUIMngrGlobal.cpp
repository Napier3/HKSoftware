//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestMacroUIMngrGlobal.cpp

#include "stdafx.h"
#include "SttTestMacroUIMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttTestMacroUIMngrXmlRWKeys

CSttTestMacroUIMngrXmlRWKeys* CSttTestMacroUIMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSttTestMacroUIMngrXmlRWKeys::g_nUIMngrRef = 0;


CSttTestMacroUIMngrXmlRWKeys::CSttTestMacroUIMngrXmlRWKeys()
{
	m_strMacroUIKey = L"macro-ui";
	m_strUIGroupKey = L"ui-group";
	m_strSttMacroUIMngrKey = L"stt-macro-ui-mngr";
	m_strTypeKey = L"type";
	m_strUi_TypeKey = L"ui-type";
	m_strFileKey = L"file";
	m_strTemplate_GenKey = L"template-gen";
}

CSttTestMacroUIMngrXmlRWKeys::~CSttTestMacroUIMngrXmlRWKeys()
{
}

CSttTestMacroUIMngrXmlRWKeys* CSttTestMacroUIMngrXmlRWKeys::Create()
{
	g_nUIMngrRef++;

	if (g_nUIMngrRef == 1)
	{
		g_pXmlKeys = new CSttTestMacroUIMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttTestMacroUIMngrXmlRWKeys::Release()
{
	g_nUIMngrRef--;

	if (g_nUIMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttTestMacroUIMngrConstGlobal

long CSttTestMacroUIMngrConstGlobal::g_nGlobalRef = 0;
CSttTestMacroUIMngrConstGlobal* CSttTestMacroUIMngrConstGlobal::g_pGlobal = NULL;


CSttTestMacroUIMngrConstGlobal::CSttTestMacroUIMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttTestMacroUIMngrConstGlobal::~CSttTestMacroUIMngrConstGlobal()
{
}

CSttTestMacroUIMngrConstGlobal* CSttTestMacroUIMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttTestMacroUIMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSttTestMacroUIMngrConstGlobal::Release()
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
