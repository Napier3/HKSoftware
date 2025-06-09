#include "stdafx.h"
#include "AtsRpcServerConfig.h"
#include "..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BSTR CAtsRpcServerConfig::m_strServerConfigKey = L"mstm-sln-test-server";
BSTR CAtsRpcServerConfig::m_strRemoteIPKey = L"remote-ip";
BSTR CAtsRpcServerConfig::m_strLocalIPKey = L"local-ip";
BSTR CAtsRpcServerConfig::m_strServerRpcPortKey = L"port-rpc";
BSTR CAtsRpcServerConfig::m_strServerFtpUserKey = L"user-ftp";
BSTR CAtsRpcServerConfig::m_strServerFtpPswKey = L"psw-ftp";

	
CAtsRpcServerConfig* CAtsRpcServerConfig::g_pAtsRpcServerConfig = NULL;
long CAtsRpcServerConfig::g_nAtsRpcServerConfigRef = 0;

CAtsRpcServerConfig* CAtsRpcServerConfig::Create()
{
	g_nAtsRpcServerConfigRef++;

	if (g_nAtsRpcServerConfigRef == 1)
	{
		g_pAtsRpcServerConfig = new CAtsRpcServerConfig();

		if (!g_pAtsRpcServerConfig->Open())
		{
			g_pAtsRpcServerConfig->Save();
		}
	}

	return g_pAtsRpcServerConfig;
}

void CAtsRpcServerConfig::Release()
{
	g_nAtsRpcServerConfigRef--;

	if (g_nAtsRpcServerConfigRef == 0)
	{
		delete g_pAtsRpcServerConfig;
		g_pAtsRpcServerConfig = NULL;
	}
}

CAtsRpcServerConfig::CAtsRpcServerConfig()
{
	m_strRemoteIP = _T("192.168.1.200");
	m_strLocalIP = _T("192.168.1.200");
	m_nRpcServerPort = 9998;
	m_strFtpUser = _T("power-sky");
	m_strFtpPSW = _T("power-sky");
}

CAtsRpcServerConfig::~CAtsRpcServerConfig()
{
	
}

long CAtsRpcServerConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("AtsRpcServerConfig.xml");

	return OpenXmlFile(m_strFile, m_strServerConfigKey, NULL);
}

long CAtsRpcServerConfig::Save()
{
	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, NULL);
		
	return 1;
}

long CAtsRpcServerConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strRemoteIPKey, oElement, m_strRemoteIP);
	xml_GetElementText(m_strServerRpcPortKey, oElement, m_nRpcServerPort);
	xml_GetElementText(m_strServerFtpUserKey, oElement, m_strFtpUser);
	xml_GetElementText(m_strServerFtpPswKey, oElement, m_strFtpPSW);
	xml_GetElementText(m_strLocalIPKey, oElement, m_strLocalIP);

	return 0;
}

long CAtsRpcServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strRemoteIPKey, oXMLDoc, oElement, m_strRemoteIP);
	xml_SetElementText(m_strServerRpcPortKey, oXMLDoc, oElement, m_nRpcServerPort);
	xml_SetElementText(m_strServerFtpUserKey, oXMLDoc, oElement, m_strFtpUser);
	xml_SetElementText(m_strServerFtpPswKey, oXMLDoc, oElement, m_strFtpPSW);
	xml_SetElementText(m_strLocalIPKey, oXMLDoc, oElement, m_strLocalIP);

	return 0;
}

