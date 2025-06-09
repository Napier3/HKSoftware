#include "stdafx.h"
#include "SFtpServerConfig.h"
#include "..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BSTR CSFtpServerConfig::m_strServerConfigKey = L"sftp-server-config";
BSTR CSFtpServerConfig::m_strServerIPKey = L"server-ip";
BSTR CSFtpServerConfig::m_strServerSFtpUserKey = L"user-sftp";
BSTR CSFtpServerConfig::m_strServerSFtpPswKey = L"psw-sftp";
BSTR CSFtpServerConfig::m_strSftpPortKey = L"port-sftp";
BSTR CSFtpServerConfig::m_strServerDirKey = L"server-dir";

	
CSFtpServerConfig* CSFtpServerConfig::g_pSFtpServerConfig = NULL;
long CSFtpServerConfig::g_nFtpServerConfigRef = 0;

CSFtpServerConfig* CSFtpServerConfig::Create()
{
	g_nFtpServerConfigRef++;

	if (g_nFtpServerConfigRef == 1)
	{
		g_pSFtpServerConfig = new CSFtpServerConfig();

		if (!g_pSFtpServerConfig->Open())
		{
			g_pSFtpServerConfig->Save();
		}
	}

	return g_pSFtpServerConfig;
}

void CSFtpServerConfig::Release()
{
	g_nFtpServerConfigRef--;

	if (g_nFtpServerConfigRef == 0)
	{
		delete g_pSFtpServerConfig;
		g_pSFtpServerConfig = NULL;
	}
}

CSFtpServerConfig::CSFtpServerConfig()
{
	m_strServerIP = _T("192.168.1.70");
	m_strSftpUser = _T("root");
	m_strSFtpPSW = _T("rootroot");
	m_strServerDir = _T("cd/root/");
	m_nSftpPort = 22;
}

CSFtpServerConfig::~CSFtpServerConfig()
{
	
}

long CSFtpServerConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("SFtpServerConfig.xml");

	return OpenXmlFile(m_strFile, m_strServerConfigKey, NULL);
}

long CSFtpServerConfig::Save()
{
	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, NULL);
		
	return 1;
}

long CSFtpServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strServerIPKey, oNode, m_strServerIP);
	xml_GetElementText(m_strServerSFtpUserKey, oNode, m_strSftpUser);
	xml_GetElementText(m_strServerSFtpPswKey, oNode, m_strSFtpPSW);
	xml_GetElementText(m_strServerDirKey, oNode, m_strServerDir);
	xml_GetElementText(m_strSftpPortKey, oNode, m_nSftpPort);

	return 0;
}

long CSFtpServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strServerIPKey, oXMLDoc, oElement, m_strServerIP);
	xml_SetElementText(m_strServerSFtpUserKey, oXMLDoc, oElement, m_strSftpUser);
	xml_SetElementText(m_strServerSFtpPswKey, oXMLDoc, oElement, m_strSFtpPSW);
	xml_SetElementText(m_strServerDirKey, oXMLDoc, oElement, m_strServerDir);
	xml_SetElementText(m_strSftpPortKey, oXMLDoc, oElement, m_nSftpPort);

	return 0;
}

