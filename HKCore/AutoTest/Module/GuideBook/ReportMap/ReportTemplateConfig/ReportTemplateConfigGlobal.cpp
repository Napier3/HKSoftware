//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ReportTemplateConfigGlobal.cpp

#include "stdafx.h"
#include "ReportTemplateConfigGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CReportTemplateConfigXmlRWKeys

CReportTemplateConfigXmlRWKeys* CReportTemplateConfigXmlRWKeys::g_pXmlKeys = NULL;
long CReportTemplateConfigXmlRWKeys::g_nRPTCFGRef = 0;


CReportTemplateConfigXmlRWKeys::CReportTemplateConfigXmlRWKeys()
{
	m_strCMgrpCmbnDataMngrKey = L"mgrp-cmbn";
	m_strCSysRptDataMngrKey = L"sys-rpt-data-mngr";
	m_strCSysRptDataKey = L"data";
	m_strCBkmkDataProcessMngrKey = L"bkmk-data-process-mngr";
	m_strCBkmkDataProcessKey = L"process";
	m_strCCommCmdStrcutAttrsKey = L"comm-cmd-struct-attrs";
	m_strCCommCmdStrcutAttrKey = L"attr";
	m_strCReportTemplateConfigKey = L"report-template-config";
	m_strOptrKey = L"optr";
	m_strValueKey = L"value";
	m_strTextTrueKey = L"txt-true";
	m_strTextFalseKey = L"txt-false";
	m_strTextAppendKey = L"append-text";
}

CReportTemplateConfigXmlRWKeys::~CReportTemplateConfigXmlRWKeys()
{
}

CReportTemplateConfigXmlRWKeys* CReportTemplateConfigXmlRWKeys::Create()
{
	g_nRPTCFGRef++;

	if (g_nRPTCFGRef == 1)
	{
		g_pXmlKeys = new CReportTemplateConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CReportTemplateConfigXmlRWKeys::Release()
{
	g_nRPTCFGRef--;

	if (g_nRPTCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CReportTemplateConfigConstGlobal

long CReportTemplateConfigConstGlobal::g_nGlobalRef = 0;
CReportTemplateConfigConstGlobal* CReportTemplateConfigConstGlobal::g_pGlobal = NULL;


CReportTemplateConfigConstGlobal::CReportTemplateConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CReportTemplateConfigConstGlobal::~CReportTemplateConfigConstGlobal()
{
}

CReportTemplateConfigConstGlobal* CReportTemplateConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CReportTemplateConfigConstGlobal();
	}

	return g_pGlobal;
}

void CReportTemplateConfigConstGlobal::Release()
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
