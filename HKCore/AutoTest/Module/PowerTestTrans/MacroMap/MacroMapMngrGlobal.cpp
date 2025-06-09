//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroMapMngrGlobal.cpp

#include "stdafx.h"
#include "MacroMapMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CClassDefMngrXmlRWKeys

CMacroMapMngrXmlRWKeys* CMacroMapMngrXmlRWKeys::g_pXmlKeys = NULL;
long CMacroMapMngrXmlRWKeys::g_nMPRef = 0;


CMacroMapMngrXmlRWKeys::CMacroMapMngrXmlRWKeys()
{
	m_strCParaMapCalKey = L"para-map-cal";
	m_strCParaMapExprKey = L"para-map-expr";
	m_strCValueMapKey = L"value-map";
	m_strCParaMapKey = L"para-map";
	m_strCMacroMapKey = L"macro-map";
	m_strCMacroMapsKey = L"macro-maps";
	//m_strMapKey = L"map";
	m_strMapNameKey = L"mapname";
	m_strMapIDKey = L"mapid";
	m_strUseKey = L"use";
	m_strCalScriptKey = L"cal-scpt";
	m_strExprKey = L"expr";
}

CMacroMapMngrXmlRWKeys::~CMacroMapMngrXmlRWKeys()
{
}

CMacroMapMngrXmlRWKeys* CMacroMapMngrXmlRWKeys::Create()
{
	g_nMPRef++;

	if (g_nMPRef == 1)
	{
		g_pXmlKeys = new CMacroMapMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMacroMapMngrXmlRWKeys::Release()
{
	g_nMPRef--;

	if (g_nMPRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CClassDefMngrConstGlobal

long CMacroMapMngrConstGlobal::g_nGlobalRef = 0;
CMacroMapMngrConstGlobal* CMacroMapMngrConstGlobal::g_pGlobal = NULL;


CMacroMapMngrConstGlobal::CMacroMapMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CMacroMapMngrConstGlobal::~CMacroMapMngrConstGlobal()
{
}

CMacroMapMngrConstGlobal* CMacroMapMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMacroMapMngrConstGlobal();
	}

	return g_pGlobal;
}

void CMacroMapMngrConstGlobal::Release()
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
