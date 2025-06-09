//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineConfigGlobal.cpp

#include "stdafx.h"
#include "MmsEngineConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CMmsEngineConfigXmlRWKeys

CMmsEngineConfigXmlRWKeys* CMmsEngineConfigXmlRWKeys::g_pXmlKeys = NULL;
long CMmsEngineConfigXmlRWKeys::g_nMSCFGRef = 0;


CMmsEngineConfigXmlRWKeys::CMmsEngineConfigXmlRWKeys()
{
	m_strCMmsEngineDsCfgKey = L"ds";

	m_strCMmsDatasetsKey = L"datasets"; //datasets
	m_strCMmslocalipsKey = L"localips"; //localips
	m_strCMmsIPCfgKey = L"ip"; //ip

	m_strCMmsEngineConfigKey = L"mms-engine-config";
	m_strKeyKey = L"key";
	m_strReadKey = L"read";
	m_strMmsKeyConfigKey = L"mms-key-config";

	m_str_TrgOps_Key = L"TrgOps";
	m_str_OptFlds_Key = L"OptFlds";
	m_strCanWriteActiveSGKey = L"can-write-active-sg";
	m_strWriteCtrlCheckModeKey = L"write-ctrl-check-flag";
	m_strWriteDataAfterWaitKey = L"write-data-after-wait";
	m_strWriteDataAfterWaitAfterSelKey = L"write-data-wait-after-sel";
	m_strMmsReadUseReportKey = L"read-use-report";
	m_strMmsResetOnlyClearReportKey = L"reset-only-clear-report";

	m_str_OptFlds_BR_Key = L"OptFlds_BR";
	m_str_OptFlds_RP_Key = L"OptFlds_RP";
	m_str_TrgOps_UI_Key   = L"TrgOps_UI";
	m_strDebugModeKey   = L"debug-mode";
	m_strUseDsDoutKey   = L"use-dsdout";
	m_strAutoGenModelDatasKey   = L"auto-gen-model-datas";
	m_strEnumLDAfterReadXmlKey   = L"enum-ld-after-read-xml";
	m_strMmsEnumLogCtrKey   = L"enum-log-ctrl";
	m_strExitAppForExceptionKey   = L"exit-app-for-exception";
	m_strUseDvmMapFileKey   = L"use-dvm-map-file";
	m_strSwitchSGWaitKey   = L"switch-setting-group-wait";
	m_strMaxReportCountKey   = L"max-report-count";
	m_strMultDevModelKey   = L"mstm-dev-mode";
	m_strExportModelAutoKey   = L"export-model-auto";

	m_strDevNumKey = L"dev-num";//dev-num
	m_strMultiDevModelKey = L"multi-dev-model";//multi-dev-model
	m_strAutoSetIpKey = L"auto-set-ip";//auto-set-ip

	m_strConnNumKey = L"conn-num";//conn-num
	m_strDevCheckKey = L"dev-check";//dev-check
	m_strUseEntryIDUpdateKey = L"use-entryid-update";//use-entryid-update
	m_strIntgPdKey = L"IntgPd";//IntgPd

}

CMmsEngineConfigXmlRWKeys::~CMmsEngineConfigXmlRWKeys()
{
}

CMmsEngineConfigXmlRWKeys* CMmsEngineConfigXmlRWKeys::Create()
{
	g_nMSCFGRef++;

	if (g_nMSCFGRef == 1)
	{
		g_pXmlKeys = new CMmsEngineConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMmsEngineConfigXmlRWKeys::Release()
{
	g_nMSCFGRef--;

	if (g_nMSCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMmsEngineConfigConstGlobal

long CMmsEngineConfigConstGlobal::g_nGlobalRef = 0;
CMmsEngineConfigConstGlobal* CMmsEngineConfigConstGlobal::g_pGlobal = NULL;


CMmsEngineConfigConstGlobal::CMmsEngineConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CMmsEngineConfigConstGlobal::~CMmsEngineConfigConstGlobal()
{
}

CMmsEngineConfigConstGlobal* CMmsEngineConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMmsEngineConfigConstGlobal();
	}

	return g_pGlobal;
}

void CMmsEngineConfigConstGlobal::Release()
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
