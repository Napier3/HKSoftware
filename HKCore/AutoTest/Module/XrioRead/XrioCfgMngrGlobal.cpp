//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioCfgMngrGlobal.cpp

#include "stdafx.h"
#include "XrioCfgMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CXrioCfgMngrXmlRWKeys

CXrioCfgMngrXmlRWKeys* CXrioCfgMngrXmlRWKeys::g_pXmlKeys = NULL;
long CXrioCfgMngrXmlRWKeys::g_nXrioRef = 0;


CXrioCfgMngrXmlRWKeys::CXrioCfgMngrXmlRWKeys()
{
	m_strCustomKey = L"CUSTOM";
	m_strXRioKey = L"XRio";
	m_strCustomBlockKey = L"Block";	
	m_strCustomParameterKey = L"Parameter";
	m_strNameKey = L"Name";
	m_strDescriptionKey = L"Description";
	m_strForeignIdKey = L"ForeignId";
	m_strDataTypeKey = L"DataType";
	m_strEnumListKey = L"EnumList";
	m_strEnumValueKey = L"EnumValue";
	m_strEnabledFormulaKey = L"EnabledFormula";
	m_strEnabledRefListKey = L"EnabledRefList";
	m_strValueFormulaKey = L"ValueFormula";
	m_strValueRefListKey = L"ValueRefList";
	m_strRefParamKey = L"RefParam";
	m_strRefEnumKey = L"RefEnum";
	m_strValueKey = L"Value";
	m_strMinValueKey = L"MinValue";
	m_strMaxValueKey = L"MaxValue";
	m_strUnitKey = L"Unit";

	m_strIdKey = L"Id";
	m_strRefIdKey = L"RefId";
	m_strEnumIdKey = L"EnumId";
	m_strEnabledKey = L"Enabled";
	m_strUnitDecimalPlacesKey = L"DecimalPlaces";	
}

CXrioCfgMngrXmlRWKeys::~CXrioCfgMngrXmlRWKeys()
{
}

CXrioCfgMngrXmlRWKeys* CXrioCfgMngrXmlRWKeys::Create()
{
	g_nXrioRef++;

	if (g_nXrioRef == 1)
	{
		g_pXmlKeys = new CXrioCfgMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXrioCfgMngrXmlRWKeys::Release()
{
	g_nXrioRef--;

	if (g_nXrioRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//CXrioCfgMngrConstGlobal

long CXrioCfgMngrConstGlobal::g_nGlobalRef = 0;
CXrioCfgMngrConstGlobal* CXrioCfgMngrConstGlobal::g_pGlobal = NULL;

CXrioCfgMngrConstGlobal::CXrioCfgMngrConstGlobal()
{

}

CXrioCfgMngrConstGlobal::~CXrioCfgMngrConstGlobal()
{
}

CXrioCfgMngrConstGlobal* CXrioCfgMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXrioCfgMngrConstGlobal();
	}

	return g_pGlobal;
}

void CXrioCfgMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

