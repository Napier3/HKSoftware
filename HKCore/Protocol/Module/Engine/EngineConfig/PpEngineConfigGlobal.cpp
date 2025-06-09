//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpEngineConfigGlobal.cpp

#include "stdafx.h"
#include "PpEngineConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CPpEngineConfigXmlRWKeys

CPpEngineConfigXmlRWKeys* CPpEngineConfigXmlRWKeys::g_pPpEngineCfgXmlKeys = NULL;
long CPpEngineConfigXmlRWKeys::g_nPpEngineCfgRef = 0;


CPpEngineConfigXmlRWKeys::CPpEngineConfigXmlRWKeys()
{
	m_strCPpEngineConfigKey = L"Pp-engine-config";

	m_strDebugModeKey   = L"debug-mode";
	m_strLogDataBindKey   = L"log-data-bind";
	m_strPkgDataInforKey   = L"log-pkg-data-infor";
	m_strLogPkgKey   = L"log-pkg";
	m_strLogDebugInforKey   = L"log-debug-infor";
	m_strNoChangeWhenSameKey   = L"no-change-when-same";
	m_strOnlyWriteLogFileKey   = L"only-write-log-file";
}

CPpEngineConfigXmlRWKeys::~CPpEngineConfigXmlRWKeys()
{
}

CPpEngineConfigXmlRWKeys* CPpEngineConfigXmlRWKeys::Create()
{
	g_nPpEngineCfgRef++;

	if (g_nPpEngineCfgRef == 1)
	{
		g_pPpEngineCfgXmlKeys = new CPpEngineConfigXmlRWKeys();
	}

	return g_pPpEngineCfgXmlKeys;
}

void CPpEngineConfigXmlRWKeys::Release()
{
	g_nPpEngineCfgRef--;

	if (g_nPpEngineCfgRef == 0)
	{
		delete g_pPpEngineCfgXmlKeys;
		g_pPpEngineCfgXmlKeys = NULL;
	}
}

