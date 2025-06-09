#include "stdafx.h"
#include "XFcenterXMLRWKeys.h"

CXFcenterXMLRWKeys* CXFcenterXMLRWKeys::g_pXFcenterRWKeys = NULL;
long CXFcenterXMLRWKeys::g_nXFcenterRWKeysRef = 0;

CXFcenterXMLRWKeys* CXFcenterXMLRWKeys::Create()
{
	g_nXFcenterRWKeysRef ++;

	if(g_pXFcenterRWKeys == NULL)
	{
		g_pXFcenterRWKeys = new CXFcenterXMLRWKeys();
	}

	return g_pXFcenterRWKeys;
}

void CXFcenterXMLRWKeys::Release()
{
	g_nXFcenterRWKeysRef --;

	if(g_nXFcenterRWKeysRef == 0)
	{
		delete g_pXFcenterRWKeys;
		g_pXFcenterRWKeys = NULL;
	}
}

CXFcenterXMLRWKeys::CXFcenterXMLRWKeys()
{
	m_strXFcenterKey = L"file-mngr-server-config";
	m_strServerPortKey = L"server-port";
	m_strServerIPKey = L"server-ip";
	m_strUserIDKey = L"user-id";
	m_strUserPswKey = L"user-psw";
	m_strUseServerKey = L"use-server";

	m_strFileReportsKey = L"report-file-mngr-id";
	m_strFileTemplateKey = L"test-template-file-mngr-id";
	m_strFileProtocolKey = L"protocol-file-mngr-id";

	m_strSeverHostNameKey = L"server-host";
	m_strSeverMacKey = L"server-mac";
	m_strLocalGatewayMacKey = L"local-gateway-mac";
	m_strAccessTypeKey = L"access-type";
}
