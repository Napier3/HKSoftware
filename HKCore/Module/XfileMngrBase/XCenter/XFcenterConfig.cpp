#include "stdafx.h"
#include <afxsock.h> 
//#include <winsock2.h>
#include <iphlpapi.h>
//#include <windows.h>
#pragma comment(lib,"iphlpapi.lib")
//#pragma comment(lib,"ws2_32.lib")

#include "XFcenterConfig.h"
#include "..\..\API\FileApi.h"
#include "..\..\Socket\XPing.h"

CXFcenterConfig* CXFcenterConfig::g_pXFcenterConfig = NULL;
long CXFcenterConfig::g_nXFcenterConfigRef = 0;
CString CXFcenterConfig::g_strXFcenterServerConfigFile = _T("FileMngrServerConfig.xml");

CXFcenterConfig* CXFcenterConfig::Create()
{
	g_nXFcenterConfigRef++;

	if (g_nXFcenterConfigRef == 1)
	{
		CXFcenterXMLRWKeys::Create();
		g_pXFcenterConfig = new CXFcenterConfig();
		g_pXFcenterConfig->Open(g_strXFcenterServerConfigFile);
	}

	return g_pXFcenterConfig;
}

void CXFcenterConfig::Release()
{
	g_nXFcenterConfigRef--;

	if (g_nXFcenterConfigRef == 0)
	{
		CXFcenterXMLRWKeys::Release();
		delete g_pXFcenterConfig;
		g_pXFcenterConfig = NULL;
	}
}

CXFcenterConfig::CXFcenterConfig()
{
	m_strServerIP = _T("192.168.0.101");
	m_nServerPort = 8200;
	m_nServerPort = 0;
	m_strServerIP.Empty();
	m_nUseServer = 0;

	m_strReportFileMngrID = _T("report-file-mngr");
	m_strTestTemplateFileMngrID = _T("test-template-file-mngr");
	m_strProtocolFileMngrID = _T("protocol-file-mngr");

	m_strSeverHostName = _T("");
	m_strSeverMac = _T("");
	m_strLocalGateWayMac = _T("");
	m_nAccessType = 0;			//0:以IP访问，1：以主机名访问
}

CXFcenterConfig::~CXFcenterConfig()
{

}

CString CXFcenterConfig::GetXFcenterConfigFile(const CString &strConfigFile)
{
	CString strFile;
	strFile = (CString)_P_GetCommonConfigPath();
	strFile += strConfigFile;

	return strFile;
}


long CXFcenterConfig::Open(const CString &strConfigFile)
{
	ASSERT (CXFcenterXMLRWKeys::g_pXFcenterRWKeys != NULL);

	m_strXFcenterConfigFile = GetXFcenterConfigFile(strConfigFile);

	return OpenXmlFile(m_strXFcenterConfigFile, CXFcenterXMLRWKeys::g_pXFcenterRWKeys->m_strXFcenterKey, CXFcenterXMLRWKeys::g_pXFcenterRWKeys);
}

long CXFcenterConfig::Save()
{
	ASSERT (CXFcenterXMLRWKeys::g_pXFcenterRWKeys != NULL);

	ClearFileReadOnlyAttr(m_strXFcenterConfigFile);
	SaveXmlFile(m_strXFcenterConfigFile, CXFcenterXMLRWKeys::g_pXFcenterRWKeys);

	return 1;
}

long CXFcenterConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXFcenterXMLRWKeys* pXmlKeys = (CXFcenterXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_GetElementText(pXmlKeys->m_strServerPortKey, oElement, m_nServerPort);
	xml_GetElementText(pXmlKeys->m_strServerIPKey, oElement, m_strServerIP);
	xml_GetElementText(pXmlKeys->m_strUserIDKey, oElement, m_strUserID);
	xml_GetElementText(pXmlKeys->m_strUserPswKey, oElement, m_strUserPsw);

	xml_GetAttibuteValue(pXmlKeys->m_strUseServerKey, oElement, m_nUseServer);

	xml_GetElementText(pXmlKeys->m_strFileReportsKey, oElement, m_strReportFileMngrID);
	xml_GetElementText(pXmlKeys->m_strFileTemplateKey, oElement, m_strTestTemplateFileMngrID);
	xml_GetElementText(pXmlKeys->m_strFileProtocolKey, oElement, m_strProtocolFileMngrID);

	xml_GetElementText(pXmlKeys->m_strSeverHostNameKey, oElement, m_strSeverHostName);
	xml_GetElementText(pXmlKeys->m_strSeverMacKey, oElement, m_strSeverMac);
	xml_GetElementText(pXmlKeys->m_strLocalGatewayMacKey, oElement, m_strLocalGateWayMac);
	xml_GetElementText(pXmlKeys->m_strAccessTypeKey, oElement, m_nAccessType);

	if( !InitXFcenterServer())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s文件中IP或主机名设置错误")
			,g_strXFcenterServerConfigFile);
	}

	return 0;
}

long CXFcenterConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXFcenterXMLRWKeys* pXmlKeys = (CXFcenterXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_SetElementText(pXmlKeys->m_strServerPortKey, oXMLDoc, oElement, m_nServerPort);
	xml_SetElementText(pXmlKeys->m_strServerIPKey, oXMLDoc, oElement, m_strServerIP);
	xml_SetElementText(pXmlKeys->m_strUserIDKey, oXMLDoc, oElement, m_strUserID);
	xml_SetElementText(pXmlKeys->m_strUserPswKey, oXMLDoc, oElement, m_strUserPsw);

	xml_SetAttributeValue(pXmlKeys->m_strUseServerKey, oElement, m_nUseServer);

	xml_SetElementText(pXmlKeys->m_strFileReportsKey, oXMLDoc, oElement, m_strReportFileMngrID);
	xml_SetElementText(pXmlKeys->m_strFileTemplateKey, oXMLDoc, oElement, m_strTestTemplateFileMngrID);
	xml_SetElementText(pXmlKeys->m_strFileProtocolKey, oXMLDoc, oElement, m_strProtocolFileMngrID);

	xml_SetElementText(pXmlKeys->m_strSeverHostNameKey, oXMLDoc, oElement, m_strSeverHostName);
	xml_SetElementText(pXmlKeys->m_strSeverMacKey, oXMLDoc, oElement, m_strSeverMac);
	xml_SetElementText(pXmlKeys->m_strLocalGatewayMacKey, oXMLDoc, oElement, m_strLocalGateWayMac);
	xml_SetElementText(pXmlKeys->m_strAccessTypeKey, oXMLDoc, oElement, m_nAccessType);

	return 0;
}

BOOL CXFcenterConfig::IsXFcenterServer()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return (g_pXFcenterConfig->m_nUseServer != 0);
}

CString CXFcenterConfig::GetServerIP()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strServerIP;
}

long CXFcenterConfig::GetServerPort()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_nServerPort;
}

CString CXFcenterConfig::GetUserID()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strUserID;
}

CString CXFcenterConfig::GetUserPsw()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strUserPsw;
}

CString CXFcenterConfig::GetSeverHostName()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strSeverHostName;
}

CString CXFcenterConfig::GetSeverMac()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strSeverMac;
}

CString CXFcenterConfig::GetLocalGatewayMac()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_strLocalGateWayMac;
}

long CXFcenterConfig::GetAccessType()
{
	ASSERT (g_pXFcenterConfig != NULL);

	return g_pXFcenterConfig->m_nAccessType;
}

CString CXFcenterConfig::GetServerIPOrHost()
{
	ASSERT (g_pXFcenterConfig != NULL);

	if (g_pXFcenterConfig->m_nAccessType == 0)
	{
		return g_pXFcenterConfig->GetServerIP();
	}
	else
	{
		return g_pXFcenterConfig->GetSeverHostName();
	}
}


void CXFcenterConfig::SetServerIP(const CString &strIP)
{
	ASSERT (g_pXFcenterConfig != NULL);

	g_pXFcenterConfig->m_strServerIP = strIP;
}

void CXFcenterConfig::SetServerPort(UINT nPort)
{
	ASSERT (g_pXFcenterConfig != NULL);

	g_pXFcenterConfig->m_nServerPort = nPort;
}

void CXFcenterConfig::SetUserID(const CString &strUserID)
{
	ASSERT (g_pXFcenterConfig != NULL);

	g_pXFcenterConfig->m_strUserID = strUserID;
}

void CXFcenterConfig::SetUserPsw(const CString &strUserPsw)
{
	ASSERT (g_pXFcenterConfig != NULL);

	g_pXFcenterConfig->m_strUserPsw = strUserPsw;
}

BOOL CXFcenterConfig::InitXFcenterServer()
{
	if (g_pXFcenterConfig->m_nAccessType == 0 
		&& g_pXFcenterConfig->m_strServerIP.IsEmpty())
	{
		return FALSE;
	}
	if (g_pXFcenterConfig->m_nAccessType != 0 
		&& (g_pXFcenterConfig->m_strSeverHostName.IsEmpty()
		|| g_pXFcenterConfig->m_strSeverMac.IsEmpty())
		|| g_pXFcenterConfig->m_strLocalGateWayMac.IsEmpty())
	{
		return FALSE;
	}

	if (g_pXFcenterConfig->m_nAccessType == 0)
	{
		return TRUE;
	}

	CString strIP = _T("");
	BOOL bRet = GetIPFromHostNameAndMac(g_pXFcenterConfig->m_strSeverHostName,
											g_pXFcenterConfig->m_strSeverMac,
											g_pXFcenterConfig->m_strLocalGateWayMac, strIP);
	if (bRet == TRUE)
	{
		g_pXFcenterConfig->m_strServerIP = strIP;
	}

	return bRet;
}

void CXFcenterConfig::SaveConfigFile()
{
	ASSERT (g_pXFcenterConfig != NULL);

	g_pXFcenterConfig->Save();
}

CString CXFcenterConfig::GetReportFileMngrID()
{
	ASSERT (g_pXFcenterConfig != NULL);
	return g_pXFcenterConfig->m_strReportFileMngrID;
}

CString CXFcenterConfig::GetTestTemplateFileMngrID()
{
	ASSERT (g_pXFcenterConfig != NULL);
	return g_pXFcenterConfig->m_strTestTemplateFileMngrID;
}

CString CXFcenterConfig::GetProtocolFileMngrID()
{
	ASSERT (g_pXFcenterConfig != NULL);
	return g_pXFcenterConfig->m_strProtocolFileMngrID;
}

void CXFcenterConfig::SetReportFileMngrID(const CString &strID)
{
	ASSERT (g_pXFcenterConfig != NULL);
	g_pXFcenterConfig->m_strReportFileMngrID = strID;
}

void CXFcenterConfig::SetTestTemplateFileMngrID(const CString &strID)
{
	ASSERT (g_pXFcenterConfig != NULL);
	g_pXFcenterConfig->m_strTestTemplateFileMngrID = strID;
}

void CXFcenterConfig::SetProtocolFileMngrID(const CString &strID)
{
	ASSERT (g_pXFcenterConfig != NULL);
	g_pXFcenterConfig->m_strProtocolFileMngrID = strID;
}

CExBaseList* CXFcenterConfig::GetBuckets()
{
	ASSERT (g_pXFcenterConfig != NULL);
	return &g_pXFcenterConfig->m_listBucket;
}

