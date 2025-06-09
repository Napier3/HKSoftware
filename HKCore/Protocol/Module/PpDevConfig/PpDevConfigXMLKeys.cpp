#include "stdafx.h"
#include "PpDevConfigXMLKeys.h"

CPpDevConfigXMLKeys* CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys = NULL;
long CPpDevConfigXMLKeys::g_nPpDevConfigXMLKeysRef = 0;

CPpDevConfigXMLKeys* CPpDevConfigXMLKeys::Create()
{
	g_nPpDevConfigXMLKeysRef ++;

	if(g_nPpDevConfigXMLKeysRef == 1)
	{
		g_pPpDevConfigXMLKeys = new CPpDevConfigXMLKeys();
	}

	return g_pPpDevConfigXMLKeys;
}

void CPpDevConfigXMLKeys::Release()
{
	g_nPpDevConfigXMLKeysRef --;

	if(g_nPpDevConfigXMLKeysRef == 0)
	{
		delete g_pPpDevConfigXMLKeys;
		g_pPpDevConfigXMLKeys = NULL;
	}
}

CPpDevConfigXMLKeys::CPpDevConfigXMLKeys()
{
	m_strXSINoNamespaceSchemaLocationKey = L"xsi:noNamespaceSchemaLocation";
	m_strXmlnsKey = L"xmlns:xsi";

	m_strPpDevConfigKey = L"PpDev-Config";
	m_strVersionKey = L"version";
	m_strDeviceModelsKey = L"DeviceModels";
	m_strDevcieModelKey = L"DeviceModel";
	m_strDebugDeviceFileKey = L"device-file";

	m_strFileKey = L"file";
}