//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSystemConfigGlobal.cpp

#include "stdafx.h"
#include "SttSystemConfigGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttSystemConfigXmlRWKeys

CSttSystemConfigXmlRWKeys* CSttSystemConfigXmlRWKeys::g_pXmlKeys = NULL;
long CSttSystemConfigXmlRWKeys::g_nMngrRef = 0;


CSttSystemConfigXmlRWKeys::CSttSystemConfigXmlRWKeys()
{
	m_strCSttModuleKey = L"module";
	m_strCSttModuleUseKey = L"module-use";
	m_strCSttDevConfigKey = L"dev-config";
	m_strCSttSystemConfigKey = L"system-config";
	m_strOpen_Delay_TimeKey = L"open-delay-time";
	m_strCompany_NameKey = L"company-name";
	m_strCur_Sel_ModelKey = L"cur-sel-model";
	m_strSel_OfflineKey = L"sel-offline";
	m_strSel_SOE_TestKey = L"sel-SOE-test";
	m_strSel_Steady_OutputKey = L"sel-steady-output";
	m_strSet_PasswordKey = L"set-password";
	m_strOverload_DelayKey = L"overload-delay";
	m_strDouble_Click_EditKey = L"double-click-edit";
	m_strAux_IpKey = L"aux-ip";
	m_strLast_Folder_PathKey = L"last-folder-path";
	m_strMulti_Exp_ListKey = L"multi-exp-list";
	m_strUse_Scl_ViewKey = L"use-scl-view";
	m_strLog_PrintKey =  L"log_print";
	m_strFt3_Prim_Code_ValueKey = L"ft3-prim-code-value";
	m_strLock_MapsKey = L"Lock-Maps";
	m_strSel_Sys_Pata = L"sel-sys-pata";
	m_strHasFT3Key = L"Has-Ft3";
}

CSttSystemConfigXmlRWKeys::~CSttSystemConfigXmlRWKeys()
{
}

CSttSystemConfigXmlRWKeys* CSttSystemConfigXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttSystemConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttSystemConfigXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttSystemConfigConstGlobal

long CSttSystemConfigConstGlobal::g_nGlobalRef = 0;
CSttSystemConfigConstGlobal* CSttSystemConfigConstGlobal::g_pGlobal = NULL;


CSttSystemConfigConstGlobal::CSttSystemConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttSystemConfigConstGlobal::~CSttSystemConfigConstGlobal()
{
}

CSttSystemConfigConstGlobal* CSttSystemConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttSystemConfigConstGlobal();
	}

	return g_pGlobal;
}

void CSttSystemConfigConstGlobal::Release()
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
