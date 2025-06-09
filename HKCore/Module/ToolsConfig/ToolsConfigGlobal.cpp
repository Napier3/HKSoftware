//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ToolsConfigGlobal.cpp

#include "stdafx.h"
#include "ToolsConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CToolsConfigXmlRWKeys

CToolsConfigXmlRWKeys* CToolsConfigXmlRWKeys::g_pXmlKeys = NULL;
long CToolsConfigXmlRWKeys::g_nTCFRef = 0;


CToolsConfigXmlRWKeys::CToolsConfigXmlRWKeys()
{
	m_strCToolsConfigKey = L"tools-config";
	m_strCToolObjectKey = L"tool";
	m_strTypeKey = L"type";
	m_strModeKey = L"mode";
	m_strParaKey = L"para";
	m_strTitleKey = L"title";
	m_strServerNameKey = L"server";

	m_strUserServerKey = L"User-Server";
	m_strUse_TASKTESTKey = L"Use-Task";
	m_strUse_SDVMPPKey = L"Use_SdvMppP";
	m_strUse_MDVMGRPKey = L"Use_MdvMgrp";
	m_strUse_ReportPaneKey = L"Use_Report-Pane";
	m_strUseAppSelConfigKey = L"Use-App-Sel-Config";
	m_strName_TEST_PROJECT_EXKey = L"Name-Test-Project";
}

CToolsConfigXmlRWKeys::~CToolsConfigXmlRWKeys()
{
}

CToolsConfigXmlRWKeys* CToolsConfigXmlRWKeys::Create()
{
	g_nTCFRef++;

	if (g_nTCFRef == 1)
	{
		g_pXmlKeys = new CToolsConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CToolsConfigXmlRWKeys::Release()
{
	g_nTCFRef--;

	if (g_nTCFRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CToolsConfigConstGlobal

long CToolsConfigConstGlobal::g_nGlobalRef = 0;
CToolsConfigConstGlobal* CToolsConfigConstGlobal::g_pGlobal = NULL;


CToolsConfigConstGlobal::CToolsConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CToolsConfigConstGlobal::~CToolsConfigConstGlobal()
{
}

CToolsConfigConstGlobal* CToolsConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CToolsConfigConstGlobal();
	}

	return g_pGlobal;
}

void CToolsConfigConstGlobal::Release()
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
