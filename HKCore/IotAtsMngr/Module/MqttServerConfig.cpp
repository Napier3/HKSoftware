#include "stdafx.h"
#include "MqttServerConfig.h"
#include "..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BSTR CMqttServerConfig::m_strServerConfigKey = L"mqtt-server";

BSTR CMqttServerConfig::m_strDBIPKey = L"DB-IP";
BSTR CMqttServerConfig::m_strDBPortKey = L"DB-Port";
BSTR CMqttServerConfig::m_strDBEncodingKey = L"DB-Encoding";
BSTR CMqttServerConfig::m_strDBPasswordKey = L"DB-Password";
BSTR CMqttServerConfig::m_strDBNameKey = L"DB-Name";
BSTR CMqttServerConfig::m_strTestModeKey = L"Test-Mode";

CMqttServerConfig* CMqttServerConfig::g_pMqttServerConfig = NULL;
long CMqttServerConfig::g_nMqttServerConfigRef = 0;

CMqttServerConfig::CMqttServerConfig()
{
	m_strDBEncoding = XSTR_EncodingID_utf8;
	m_strTestMode = MQTT_SERVER_TEST_MODE_FUNCTION;
}

CMqttServerConfig::~CMqttServerConfig()
{

}

CMqttServerConfig* CMqttServerConfig::Create()
{
	g_nMqttServerConfigRef++;

	if (g_nMqttServerConfigRef == 1)
	{
		g_pMqttServerConfig = new CMqttServerConfig();

		if (!g_pMqttServerConfig->Open())
		{
			g_pMqttServerConfig->Save();
		}
	}

	return g_pMqttServerConfig;
}

void CMqttServerConfig::Release()
{
	g_nMqttServerConfigRef--;

	if (g_nMqttServerConfigRef == 0)
	{
		delete g_pMqttServerConfig;
		g_pMqttServerConfig = NULL;
	}
}

long CMqttServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strDBIPKey, oNode, m_strDBIP);
	xml_GetElementText(m_strDBPortKey, oNode, m_strDBPort);
	xml_GetElementText(m_strDBEncodingKey, oNode, m_strDBEncoding);
	xml_GetElementText(m_strDBPasswordKey, oNode, m_strDBPassword);
	xml_GetElementText(m_strDBNameKey, oNode, m_strDBName);
	xml_GetElementText(m_strTestModeKey, oNode, m_strTestMode);
	
	return 0;
}

long CMqttServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strDBIPKey, oXMLDoc, oElement, m_strDBIP);
	xml_SetElementText(m_strDBPortKey, oXMLDoc, oElement, m_strDBPort);
	xml_SetElementText(m_strDBEncodingKey, oXMLDoc, oElement, m_strDBEncoding);
	xml_SetElementText(m_strDBPasswordKey, oXMLDoc, oElement, m_strDBPassword);
	xml_SetElementText(m_strDBNameKey, oXMLDoc, oElement, m_strDBName);
	xml_SetElementText(m_strTestModeKey, oXMLDoc, oElement, m_strTestMode);

	return 0;
}


long CMqttServerConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("MqttServerConfig.xml");

	return OpenXmlFile(m_strFile, m_strServerConfigKey, NULL);
}

long CMqttServerConfig::Save()
{
	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, NULL);

	return 1;
}