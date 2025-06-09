#include "StdAfx.h"
#include "CmmNetClientConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmNetClientConfig::CCmmNetClientConfig(void)
{
	m_nRemotePort = 80;
	m_strRemoteIP = _T("0.0.0.0");
	m_nLocalPort = 80;
	m_strLocalIP = _T("0.0.0.0");
}

CCmmNetClientConfig::~CCmmNetClientConfig(void)
{
}



//´®ÐÐ»¯
long CCmmNetClientConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmNetClientConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetServerConfig::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey, oNode, m_strRemoteIP);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey, oNode, m_nRemotePort);
// 	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oNode, m_strLocalIP);
// 	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oNode, m_nLocalPort);

	return 0;
}

long CCmmNetClientConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetServerConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey, oElement, m_strRemoteIP);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey, oElement, m_nRemotePort);
// 	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oElement, m_strLocalIP);
// 	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oElement, m_nLocalPort);

	return 0;
}

BOOL CCmmNetClientConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmNetClientConfig*)pDest)->m_strRemoteIP = m_strRemoteIP;
	((CCmmNetClientConfig*)pDest)->m_nRemotePort = m_nRemotePort;
// 	((CCmmNetClientConfig*)pDest)->m_strLocalIP = m_strLocalIP;
// 	((CCmmNetClientConfig*)pDest)->m_nLocalPort = m_nLocalPort;

	return CCmmNetServerConfig::CopyOwn(pDest);
}

// CBaseObject* CCmmNetClientConfig::Clone()
// {
// 	CCmmNetClientConfig *pNew = new CCmmNetClientConfig();
// 
// 	Copy(pNew);
// 
// 	return pNew;
// }
// 
