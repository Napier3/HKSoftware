//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestGridDefineGlobal.cpp

#include "stdafx.h"
#include "SttTestGridDefineGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttTestGridDefineXmlRWKeys

CSttTestGridDefineXmlRWKeys* CSttTestGridDefineXmlRWKeys::g_pXmlKeys = NULL;
long CSttTestGridDefineXmlRWKeys::g_nMngrRef = 0;


CSttTestGridDefineXmlRWKeys::CSttTestGridDefineXmlRWKeys()
{
	m_strCSttGdColDef_TextCombKey = L"text-comb";
	m_strCSttGdParaConditionKey = L"para-condition";
	m_strCSttGdConditionKey = L"condition";
	m_strCSttGdInst_ColKey = L"col";
	m_strCSttGdInst_ColsKey = L"cols";
	m_strCSttGdGridInstKey = L"grid-inst";
	m_strCSttGdGridInstsKey = L"grid-insts";
	m_strCSttGdColDef_Fuc_AvgKey = L"avg";
	m_strCSttGdColDef_Fuc_MinKey = L"min";
	m_strCSttGdColDef_Fuc_MaxKey = L"max";
	m_strCSttGdColDef_ScriptKey = L"script";
	m_strCSttGdColDef_ParaKey = L"para";
	m_strCSttGdColDefKey = L"col-def";
	m_strCSttGdGridDefineKey = L"grid-define";
	m_strCSttGdDataCalKey = L"data-cal";
	m_strCSttGdDataProcessKey = L"data-process";
	m_strCSttGdTestMacroKey = L"test-macro";
	m_strCSttTestGridDefineKey = L"test-grid-define";
	m_strMacro_IdKey = L"macro-id";
	m_strExprKey = L"expr";
	m_strData_IdKey = L"data-id";
	m_strData_TypeKey = L"data-type";
	m_strUnitKey = L"unit";
	m_strDecimalKey = L"decimal";
	m_strMaxKey = L"max";
	m_strMinKey = L"min";
	m_strEditableKey = L"editable";
	m_strWidthKey = L"width";
	m_strCtrl_TypeKey = L"ctrl-type";
	m_strRateKey = L"rate";
	m_strSetting_AttachKey = L"setting-attach";
	m_strIs_RltKey = L"is-rlt";
	m_strIdKey = L"id";
	m_strLogicKey = L"logic";
	m_strValueKey = L"value";
	m_strPrev_TextKey = L"prev-text";
	m_strAfter_TextKey = L"after-text";
	m_strWith_UnitKey = L"with-unit";
}

CSttTestGridDefineXmlRWKeys::~CSttTestGridDefineXmlRWKeys()
{
}

CSttTestGridDefineXmlRWKeys* CSttTestGridDefineXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttTestGridDefineXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttTestGridDefineXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttTestGridDefineConstGlobal

long CSttTestGridDefineConstGlobal::g_nGlobalRef = 0;
CSttTestGridDefineConstGlobal* CSttTestGridDefineConstGlobal::g_pGlobal = NULL;


CSttTestGridDefineConstGlobal::CSttTestGridDefineConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttTestGridDefineConstGlobal::~CSttTestGridDefineConstGlobal()
{
}

CSttTestGridDefineConstGlobal* CSttTestGridDefineConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttTestGridDefineConstGlobal();
	}

	return g_pGlobal;
}

void CSttTestGridDefineConstGlobal::Release()
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
