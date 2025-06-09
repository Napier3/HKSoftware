#include "stdafx.h"
#include "SafenetXMLRWKeys.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSafenetXMLRWKeys* CSafenetXMLRWKeys::g_pSafenetRWKeys = NULL;
long CSafenetXMLRWKeys::g_nSafenetRWKeysRef = 0;

CSafenetXMLRWKeys* CSafenetXMLRWKeys::Create()
{
	g_nSafenetRWKeysRef ++;

	if(g_pSafenetRWKeys == NULL)
	{
		g_pSafenetRWKeys = new CSafenetXMLRWKeys();
	}

	return g_pSafenetRWKeys;
}

void CSafenetXMLRWKeys::Release()
{
	g_nSafenetRWKeysRef --;

	if(g_nSafenetRWKeysRef == 0)
	{
		delete g_pSafenetRWKeys;
		g_pSafenetRWKeys = NULL;
	}
}

CSafenetXMLRWKeys::CSafenetXMLRWKeys()
{
	m_strSafenetKey = L"safenet-config";
	m_strServerPortKey = L"server-port";
	m_strServerIPKey = L"server-ip";
	m_strUserIDKey = L"user-id";
	m_strUserPswKey = L"user-psw";
	m_strUseServerKey = L"use-server";

	m_strSeverHostNameKey = L"server-host";
	m_strSeverMacKey = L"server-mac";
	m_strLocalGatewayMacKey = L"local-gateway-mac";
	m_strAccessTypeKey = L"access-type";
}
