//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VoiceWord3Global.cpp

#include "stdafx.h"
#include "VoiceWordGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CVoiceWordXmlRWKeys

CVoiceWordXmlRWKeys* CVoiceWordXmlRWKeys::g_pXmlKeys = NULL;
long CVoiceWordXmlRWKeys::g_nVWRef = 0;


CVoiceWordXmlRWKeys::CVoiceWordXmlRWKeys()
{
	m_strCAudioDataKey = L"data";
	m_strCAudioTestWordsKey = L"test-words";
	m_strCAudioKeyWordsKey = L"key-words";
	m_strCAudioKeyWordKey = L"key-word";
	m_strCAudioFlowWordsKey = L"flow-words";
	m_strCAudioFlowWordKey = L"flow-word";
	m_strCAudioWordKey = L"word";
	m_strCAudioOrderWordsKey = L"order-words";
	m_strCAudioOrderWordKey = L"order-word";
	m_strCAudioTipWordsKey = L"tip-words";
	m_strCAudioTipWordKey = L"tip-word";
	m_strCAudioReplyKeyWordKey = L"reply-key-word";
	m_strValueKey = L"value";
	m_strTip_Word_IdKey = L"tip-word-id";
	m_strOrder_Word_IdKey = L"order-word-id";
	m_strLevelKey = L"level";
	m_strFlagKey = L"flag";
	m_strTipWordKey = L"tip-word";
	m_strData_TypeKey = L"data-type";
}

CVoiceWordXmlRWKeys::~CVoiceWordXmlRWKeys()
{
}

CVoiceWordXmlRWKeys* CVoiceWordXmlRWKeys::Create()
{
	g_nVWRef++;

	if (g_nVWRef == 1)
	{
		g_pXmlKeys = new CVoiceWordXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CVoiceWordXmlRWKeys::Release()
{
	g_nVWRef--;

	if (g_nVWRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CVoiceWord3ConstGlobal

long CVoiceWord3ConstGlobal::g_nGlobalRef = 0;
CVoiceWord3ConstGlobal* CVoiceWord3ConstGlobal::g_pGlobal = NULL;


CVoiceWord3ConstGlobal::CVoiceWord3ConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CVoiceWord3ConstGlobal::~CVoiceWord3ConstGlobal()
{
}

CVoiceWord3ConstGlobal* CVoiceWord3ConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CVoiceWord3ConstGlobal();
	}

	return g_pGlobal;
}

void CVoiceWord3ConstGlobal::Release()
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
