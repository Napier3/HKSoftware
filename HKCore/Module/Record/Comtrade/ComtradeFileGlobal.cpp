//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ComtradeFileGlobal.cpp

#include "stdafx.h"
#include "ComtradeFileGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CComtradeFileXmlRWKeys

CComtradeFileXmlRWKeys* CComtradeFileXmlRWKeys::g_pXmlKeys = NULL;
long CComtradeFileXmlRWKeys::g_nGlobalRef = 0;


CComtradeFileXmlRWKeys::CComtradeFileXmlRWKeys()
{
	m_strCComtradeRateDataKey = L"rateinfor";
	m_strCComtradeBinaryDataKey = L"sttInfo";
	m_strCComtradeAnalogDataKey = L"ChInfo";
	m_strCComtradeDataBaseKey = L"";
	m_strCRcdComtradeFileKey = L"Cfg";
	m_strVersionKey = L"version";
	m_strAllchsKey = L"allchs";
	m_strUIchsKey = L"uichs";
	m_strStatechKey = L"statech";
	m_strFreqKey = L"freq";
	m_strRatesKey = L"rates";
	m_strFirstpttmKey = L"firstpttm";
	m_strTriptmKey = L"triptm";
	m_strDatafiletypeKey = L"datafiletype";
	m_strTmmultKey = L"tmmult";
	m_strIndexKey = L"index";
	m_strCcbmKey = L"ccbm";
	m_strUnitKey = L"unit";
	m_strCoefaKey = L"coefa";
	m_strCoefbKey = L"coefb";
	m_strSkewtimeKey = L"skewtime";
	m_strMinKey = L"min";
	m_strMaxKey = L"max";
	m_strPrimaryKey = L"primary";
	m_strSecondaryKey = L"secondary";
	m_strPsKey = L"ps";
	m_strYKey = L"y";
	m_strSamprateKey = L"samprate";
	m_strEndsampKey = L"endsamp";
}

CComtradeFileXmlRWKeys::~CComtradeFileXmlRWKeys()
{
}

CComtradeFileXmlRWKeys* CComtradeFileXmlRWKeys::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pXmlKeys = new CComtradeFileXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CComtradeFileXmlRWKeys::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CComtradeFileConstGlobal

long CComtradeFileConstGlobal::g_nGlobalRef = 0;
CComtradeFileConstGlobal* CComtradeFileConstGlobal::g_pGlobal = NULL;


CComtradeFileConstGlobal::CComtradeFileConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CComtradeFileConstGlobal::~CComtradeFileConstGlobal()
{
}

CComtradeFileConstGlobal* CComtradeFileConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CComtradeFileConstGlobal();
	}

	return g_pGlobal;
}

void CComtradeFileConstGlobal::Release()
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
