//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgToolGlobal.cpp

#include "stdafx.h"
#include "IecCfgToolGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgToolXmlRWKeys

CIecCfgToolXmlRWKeys* CIecCfgToolXmlRWKeys::g_pXmlKeys = NULL;
long CIecCfgToolXmlRWKeys::g_nIFTRef = 0;


CIecCfgToolXmlRWKeys::CIecCfgToolXmlRWKeys()
{
	m_strCIecCfgToolKey = L"iecfg-tool";
	m_strCSclFilesKey = L"scl-files";
	m_strCSclFileKey = L"scl-file";
	m_strCIecCfgFilesKey = L"iecfg-files";
	m_strCIecCfgFileKey = L"iecfg-file";
	m_strCIecCfgFileDeviceKey = L"iecfg-file-device";

	m_strUseDebugKey = L"debug-state";
	m_strAutoSetUIChIndexKey = L"auto-set-ui-ch-index";

	m_strIecCfgDownDllFileKey = L"iec-down-dll";
	m_strViewOnlyUsedInChsKey = L"view-only-used-inch";
	m_strViewChsPathKey = L"view-chs-path";

	m_strTscdNameKey = L"tscd-name"; //tscd-name

	m_strAT02D_UseHarmKey = L"use-harm";//周宏军 20200616  增加AT02配置
	m_strAT02D_VerifyVolCurChannelKey = L"verify-volc";
	m_strLinkGoutKey = L"link-gout";//周宏军 20200616  增加link-gout
	m_strAutoOpenLastKey = L"auto-open-last";
}

CIecCfgToolXmlRWKeys::~CIecCfgToolXmlRWKeys()
{
}

CIecCfgToolXmlRWKeys* CIecCfgToolXmlRWKeys::Create()
{
	g_nIFTRef++;

	if (g_nIFTRef == 1)
	{
		g_pXmlKeys = new CIecCfgToolXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CIecCfgToolXmlRWKeys::Release()
{
	g_nIFTRef--;

	if (g_nIFTRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CIecCfgToolConstGlobal

long CIecCfgToolConstGlobal::g_nGlobalRef = 0;
CIecCfgToolConstGlobal* CIecCfgToolConstGlobal::g_pGlobal = NULL;


CIecCfgToolConstGlobal::CIecCfgToolConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CIecCfgToolConstGlobal::~CIecCfgToolConstGlobal()
{
}

CIecCfgToolConstGlobal* CIecCfgToolConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIecCfgToolConstGlobal();
	}

	return g_pGlobal;
}

void CIecCfgToolConstGlobal::Release()
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
