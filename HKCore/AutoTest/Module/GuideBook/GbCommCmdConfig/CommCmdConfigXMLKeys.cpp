#include "stdafx.h"
#include "CommCmdConfigXMLKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCommCmdConfigXMLKeys* CCommCmdConfigXMLKeys::g_pConfigXMLKeys = NULL;
long CCommCmdConfigXMLKeys::g_nConfigXMLKeysRef = 0;

CCommCmdConfigXMLKeys* CCommCmdConfigXMLKeys::CreateConfigXMLKeys()
{
	g_nConfigXMLKeysRef ++;

	if(g_nConfigXMLKeysRef == 1)
	{
		g_pConfigXMLKeys = new CCommCmdConfigXMLKeys();
	}

	return g_pConfigXMLKeys;
}

void CCommCmdConfigXMLKeys::Release()
{
	g_nConfigXMLKeysRef --;

	if(g_nConfigXMLKeysRef == 0)
	{
		delete g_pConfigXMLKeys;
		g_pConfigXMLKeys = NULL;
	}
}

CCommCmdConfigXMLKeys::CCommCmdConfigXMLKeys()
{
	m_strCommCmdConfigKey = L"comm-cmd-config";
	m_strCmdKey = L"cmd";
	m_strCmdExKey = L"cmdex";
	m_strCmdParaKey = L"para";
	
	m_strPpProcedureIDKey = L"pp-procedure-id";
	m_strPpDvNodeIDKey = L"pp-dv-node-id";
	m_strGbDataIDKey = L"gb-data-id";
	m_strGbRwOptrKeyKey = L"gb-rw-optr";
	m_strDatasetKey = L"dataset";
	m_strValueKey = L"value";
	m_strDataTypeKey = L"data-type";
	m_strUseConnectKey = L"use-connect";
	m_strWzdEditModeKey = L"wzd-edit-mode";
}

