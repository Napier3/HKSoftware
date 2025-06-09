//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBGeneratorGlobal.cpp

#include "stdafx.h"
#include "UIBGeneratorGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CUIBGeneratorXmlRWKeys

CUIBGeneratorXmlRWKeys* CUIBGeneratorXmlRWKeys::g_pXmlKeys = NULL;
long CUIBGeneratorXmlRWKeys::g_nUIBGRef = 0;


CUIBGeneratorXmlRWKeys::CUIBGeneratorXmlRWKeys()
{
	m_strCUibGenBinaryKey = L"binary";
	m_strCUibGeneratorKey = L"UIB_Gen";
	m_strCUibGenStateKey = L"state";
	m_strCUibGenAnalogKey = L"analog";
	m_strCUibGenHarmKey = L"hm";
	m_strUseKey = L"use";
	m_strIndexKey = L"index";
	m_strValueKey = L"value";
	m_strAngleKey = L"angle";
	m_strZeroKey = L"zero";
	m_strCoefKey = L"coef";
	m_strChIDKey = L"ch-id";
	m_strRandKey = L"rand";
	m_strUnitKey = L"unit";
	m_strPrimaryKey = L"primary";
	m_strSecondaryKey = L"secondary";
	m_strTimeLongKey = L"time-long";
	m_strModeKey = L"mode";
	m_strFreqKey = L"freq";
	m_strSampRateKey = L"samp-rate";
	m_strUchCountKey = L"u-chs";
	m_strIchCountKey = L"i-chs";
	m_strBchCountKey = L"b-chs";
	m_strTurnTimeKey = L"turn-time";
	m_strHoldTimeKey = L"hold-time";
}

CUIBGeneratorXmlRWKeys::~CUIBGeneratorXmlRWKeys()
{
}

CUIBGeneratorXmlRWKeys* CUIBGeneratorXmlRWKeys::Create()
{
	g_nUIBGRef++;

	if (g_nUIBGRef == 1)
	{
		g_pXmlKeys = new CUIBGeneratorXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CUIBGeneratorXmlRWKeys::Release()
{
	g_nUIBGRef--;

	if (g_nUIBGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CUIBGeneratorConstGlobal

long CUIBGeneratorConstGlobal::g_nGlobalRef = 0;
CUIBGeneratorConstGlobal* CUIBGeneratorConstGlobal::g_pGlobal = NULL;


CUIBGeneratorConstGlobal::CUIBGeneratorConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CUIBGeneratorConstGlobal::~CUIBGeneratorConstGlobal()
{
}

CUIBGeneratorConstGlobal* CUIBGeneratorConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CUIBGeneratorConstGlobal();
	}

	return g_pGlobal;
}

void CUIBGeneratorConstGlobal::Release()
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
