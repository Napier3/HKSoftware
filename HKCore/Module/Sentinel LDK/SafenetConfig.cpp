#include "stdafx.h"

#include "SafenetConfig.h"
#include "..\API\FileApi.h"
#include "..\Socket\XPing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSafenetConfig* CSafenetConfig::g_pSafenetConfig = NULL;
long CSafenetConfig::g_nSafenetConfigRef = 0;
CString CSafenetConfig::g_strSafenetConfigFile = _T("SafenetConfig.xml");
CString CSafenetConfig::g_strSafenetServerConfigFile = _T("SafenetServerConfig.xml");

CSafenetConfig* CSafenetConfig::Create(BOOL bCreateServer)
{
	g_nSafenetConfigRef++;

	if (g_nSafenetConfigRef == 1)
	{
		CSafenetXMLRWKeys::Create();
		g_pSafenetConfig = new CSafenetConfig();

		if (bCreateServer)
		{
			g_pSafenetConfig->Open(g_strSafenetServerConfigFile);
		}
		else
		{
			g_pSafenetConfig->Open(g_strSafenetConfigFile);
		}
	}

	return g_pSafenetConfig;
}

void CSafenetConfig::Release()
{
	g_nSafenetConfigRef--;

	if (g_nSafenetConfigRef == 0)
	{
		CSafenetXMLRWKeys::Release();
		delete g_pSafenetConfig;
		g_pSafenetConfig = NULL;
	}
}

CSafenetConfig::CSafenetConfig()
{
	m_strServerIP = _T("192.168.0.101");
	m_nServerPort = 8137;
	m_nServerPort = 0;
	m_strServerIP.Empty();
	m_nUseServer = 0;
}

CSafenetConfig::~CSafenetConfig()
{

}

CString CSafenetConfig::GetSafenetConfigFile(const CString &strConfigFile)
{
	CString strFile;
	strFile = (CString)_P_GetCommonConfigPath();
	strFile += strConfigFile;

	return strFile;
}


long CSafenetConfig::Open(const CString &strConfigFile)
{
	ASSERT (CSafenetXMLRWKeys::g_pSafenetRWKeys != NULL);

	m_strSafenetConfigFile = GetSafenetConfigFile(strConfigFile);

	return OpenXmlFile(m_strSafenetConfigFile, CSafenetXMLRWKeys::g_pSafenetRWKeys->m_strSafenetKey, CSafenetXMLRWKeys::g_pSafenetRWKeys);
}

long CSafenetConfig::Save()
{
	ASSERT (CSafenetXMLRWKeys::g_pSafenetRWKeys != NULL);

	ClearFileReadOnlyAttr(m_strSafenetConfigFile);
	SaveXmlFile(m_strSafenetConfigFile, CSafenetXMLRWKeys::g_pSafenetRWKeys);

	return 1;
}

long CSafenetConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSafenetXMLRWKeys* pXmlKeys = (CSafenetXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_GetElementText(pXmlKeys->m_strServerPortKey, oElement, m_nServerPort);
	xml_GetElementText(pXmlKeys->m_strServerIPKey, oElement, m_strServerIP);
	xml_GetElementText(pXmlKeys->m_strUserIDKey, oElement, m_strUserID);
	xml_GetElementText(pXmlKeys->m_strUserPswKey, oElement, m_strUserPsw);

	xml_GetAttibuteValue(pXmlKeys->m_strUseServerKey, oElement, m_nUseServer);

	xml_GetElementText(pXmlKeys->m_strSeverHostNameKey, oElement, m_strSeverHostName);
	xml_GetElementText(pXmlKeys->m_strSeverMacKey, oElement, m_strSeverMac);
	xml_GetElementText(pXmlKeys->m_strLocalGatewayMacKey, oElement, m_strLocalGatewayMac);
	xml_GetElementText(pXmlKeys->m_strAccessTypeKey, oElement, m_nAccessType);

	if (!InitSafenetServer())
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("服务器远程授权，配置文件【%s】中IP或主机名设置错误")
// 			,g_strSafenetConfigFile);
	}

	return 0;
}

long CSafenetConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSafenetXMLRWKeys* pXmlKeys = (CSafenetXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_SetElementText(pXmlKeys->m_strServerPortKey, oXMLDoc, oElement, m_nServerPort);
	xml_SetElementText(pXmlKeys->m_strServerIPKey, oXMLDoc, oElement, m_strServerIP);
	xml_SetElementText(pXmlKeys->m_strUserIDKey, oXMLDoc, oElement, m_strUserID);
	xml_SetElementText(pXmlKeys->m_strUserPswKey, oXMLDoc, oElement, m_strUserPsw);

	xml_SetAttributeValue(pXmlKeys->m_strUseServerKey, oElement, m_nUseServer);

	xml_SetElementText(pXmlKeys->m_strSeverHostNameKey, oXMLDoc, oElement, m_strSeverHostName);
	xml_SetElementText(pXmlKeys->m_strSeverMacKey, oXMLDoc, oElement, m_strSeverMac);
	xml_SetElementText(pXmlKeys->m_strLocalGatewayMacKey, oXMLDoc, oElement, m_strLocalGatewayMac);
	xml_SetElementText(pXmlKeys->m_strAccessTypeKey, oXMLDoc, oElement, m_nAccessType);

	return 0;
}

BOOL CSafenetConfig::IsSafenetServer()
{
	ASSERT (g_pSafenetConfig != NULL);

	return (g_pSafenetConfig->m_nUseServer != 0);
}

CString CSafenetConfig::GetServerIP()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strServerIP;
}

long CSafenetConfig::GetServerPort()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_nServerPort;
}

CString CSafenetConfig::GetUserID()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strUserID;
}

CString CSafenetConfig::GetUserPsw()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strUserPsw;
}

CString CSafenetConfig::GetSeverHostName()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strSeverHostName;
}

CString CSafenetConfig::GetSeverMac()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strSeverMac;
}

CString CSafenetConfig::GetLocalGatewayMac()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_strLocalGatewayMac;
}

long CSafenetConfig::GetAccessType()
{
	ASSERT (g_pSafenetConfig != NULL);

	return g_pSafenetConfig->m_nAccessType;
}

CString CSafenetConfig::GetServerIPOrHost()
{
	ASSERT (g_pSafenetConfig != NULL);

	if (g_pSafenetConfig->m_nAccessType == 0)
	{
		return g_pSafenetConfig->GetServerIP();
	}
	else
	{
		return g_pSafenetConfig->GetSeverHostName();
	}
}

void CSafenetConfig::SetServerIP(const CString &strIP)
{
	ASSERT (g_pSafenetConfig != NULL);

	g_pSafenetConfig->m_strServerIP = strIP;
}

void CSafenetConfig::SetServerPort(UINT nPort)
{
	ASSERT (g_pSafenetConfig != NULL);

	g_pSafenetConfig->m_nServerPort = nPort;
}

void CSafenetConfig::SetUserID(const CString &strUserID)
{
	ASSERT (g_pSafenetConfig != NULL);

	g_pSafenetConfig->m_strUserID = strUserID;
}

void CSafenetConfig::SetUserPsw(const CString &strUserPsw)
{
	ASSERT (g_pSafenetConfig != NULL);

	g_pSafenetConfig->m_strUserPsw = strUserPsw;
}

BOOL CSafenetConfig::InitSafenetServer()
{
	if (g_pSafenetConfig->m_nAccessType == 0 
		&& g_pSafenetConfig->m_strServerIP.IsEmpty())
	{
		return FALSE;
	}
	if (g_pSafenetConfig->m_nAccessType != 0 
		&& (g_pSafenetConfig->m_strSeverHostName.IsEmpty()
		|| g_pSafenetConfig->m_strSeverMac.IsEmpty())
		|| g_pSafenetConfig->m_strLocalGatewayMac.IsEmpty())
	{
		return FALSE;
	}

	if (g_pSafenetConfig->m_nAccessType == 0)
	{
		return TRUE;
	}

	CString strIP = _T("");
	BOOL bRet = GetIPFromHostNameAndMac(g_pSafenetConfig->m_strSeverHostName,
		g_pSafenetConfig->m_strSeverMac, g_pSafenetConfig->m_strLocalGatewayMac, strIP);
	if (bRet == TRUE)
	{
		g_pSafenetConfig->m_strServerIP = strIP;
	}

	return bRet;
}

