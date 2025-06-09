//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//LicenseGlobal.cpp

#include "stdafx.h"
#include "SttLicenseGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CLicenseXmlRWKeys

CLicenseXmlRWKeys* CLicenseXmlRWKeys::g_pXmlKeys = NULL;
long CLicenseXmlRWKeys::g_nSTTLCSRef = 0;


CLicenseXmlRWKeys::CLicenseXmlRWKeys()
{
	m_strCSttLicenseMngrKey = L"license-mngr";
	m_strCSttLicenseKey = L"license";
	m_strCSttLicenseModuleKey = L"module";
	m_strKeyKey = L"key";
	m_strYearKey = L"year";
	m_strMonthKey = L"month";
	m_strDayKey = L"day";
	m_strDaysKey = L"days";
	m_strTimesKey = L"times";
	m_strTypeKey = L"type";
}

CLicenseXmlRWKeys::~CLicenseXmlRWKeys()
{
}

CLicenseXmlRWKeys* CLicenseXmlRWKeys::Create()
{
	g_nSTTLCSRef++;

	if (g_nSTTLCSRef == 1)
	{
		g_pXmlKeys = new CLicenseXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CLicenseXmlRWKeys::Release()
{
	g_nSTTLCSRef--;

	if (g_nSTTLCSRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CLicenseConstGlobal

long CLicenseConstGlobal::g_nGlobalRef = 0;
CLicenseConstGlobal* CLicenseConstGlobal::g_pGlobal = NULL;


CLicenseConstGlobal::CLicenseConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CLicenseConstGlobal::~CLicenseConstGlobal()
{
}

CLicenseConstGlobal* CLicenseConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CLicenseConstGlobal();
	}

	return g_pGlobal;
}

void CLicenseConstGlobal::Release()
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
