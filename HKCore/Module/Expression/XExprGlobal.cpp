//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprGlobal.cpp

#include "stdafx.h"
#include "XExprGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CXExprXmlRWKeys

CXExprXmlRWKeys* CXExprXmlRWKeys::g_pXmlKeys = NULL;
long CXExprXmlRWKeys::g_nEXPRRef = 0;


CXExprXmlRWKeys::CXExprXmlRWKeys()
{
	m_strCXExprNodeKey = L"node";
	m_strCXExprRangeKey = L"range";
	m_strCXExprRangeExKey = L"range-ex";
	m_strCXExprErrorKey = L"error";
	m_strCXExprErrorExKey = L"error-ex";
	m_strCXExprErrorCombinedKey = L"error-combined";
	m_strCXExprValueCalKey = L"valuecal";
	m_strCXExprValueCalExKey = L"valuecal-ex";
	m_strCXExprCmpKey = L"cmp";
	m_strCXExprValueKey = L"value";
	m_strTypeKey = L"type";
	m_strValueKey = L"value";
	m_strOptrKey = L"optr";
	m_strUseKey = L"use";
	m_strCntRsltKey = L"cntrslt";
	m_strCalOptrKey = L"cal-optr";
	m_strModeKey = L"mode";
	m_strLogicKey = L"logic";

	m_strValue1Key = L"value1"; //value1
	m_strValue2Key = L"value2"; //value2
	m_strValueStdKey = L"value-std"; //value-std
	m_strErrorKey = L"error"; //error
	m_strErrorRelKey = L"error-rel";	//error-rel
	m_strErrorAbsKey = L"error-abs"; //error-abs
	m_strValueMaxKey = L"value-max"; //value-max
	m_strValueMinKey = L"value-min"; //value-min
	m_strValueRsltKey = L"value-rslt"; //value-rslt
	m_strValueErrorRsltKey = L"value-error";  //value-error
	m_strValueErrorRelRsltKey = L"value-error-rel";  //value-error-rel 
	m_strValueErrorAbsRsltKey = L"value-error-abs";  //value-error-abs 
	m_strValueCalRsltKey = L"value-cal-rslt";
	m_strMinOptrKey = L"min-optr";  //min-optr
	m_strMaxOptrKey = L"max-optr";  //max-optr
	m_strValueIDKey = L"value-id";  //value-id
	m_strValueNameKey = L"value-name";  //value-name
	m_strValueUnitKey = L"value-unit";  //value-unit
	m_strValueTypeKey = L"value-type";  //value-type
	m_strItemPathKey = L"item-path";  //item-path

	//2023-6-30新增
	m_strValueDstIDKey = L"value-dst-id";   //value-dst-id
	m_strValueSrcIDKey = L"value-src-id";   //value-src-id
	m_strCXExprCalKey = L"expr-cal";      //expr-cal
	m_strCXQueryMaxKey = L"query-max";     //query-max
	m_strCXQueryMinKey = L"query-min";     //query-min

	m_strCXExprCalSRptKey = L"expr-cal-srpt";
	m_strValueSrcIDHasKey = L"value-src-id-has";
	m_strCalModeKey = L"cal-mode";
}

CXExprXmlRWKeys::~CXExprXmlRWKeys()
{
}

CXExprXmlRWKeys* CXExprXmlRWKeys::Create()
{
	g_nEXPRRef++;

	if (g_nEXPRRef == 1)
	{
		g_pXmlKeys = new CXExprXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXExprXmlRWKeys::Release()
{
	g_nEXPRRef--;

	if (g_nEXPRRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CXExprConstGlobal

long CXExprConstGlobal::g_nGlobalRef = 0;
CXExprConstGlobal* CXExprConstGlobal::g_pGlobal = NULL;


CXExprConstGlobal::CXExprConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CXExprConstGlobal::~CXExprConstGlobal()
{
}

CXExprConstGlobal* CXExprConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXExprConstGlobal();
	}

	return g_pGlobal;
}

void CXExprConstGlobal::Release()
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
