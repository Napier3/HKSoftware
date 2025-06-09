#include "StdAfx.h"
#include "CmmUdpClientConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmUdpClientConfig::CCmmUdpClientConfig(void)
{
	m_nUseBroadcast = 0;
	m_nMulticastPort = 0;
	m_strMulticastIP = _T("0.0.0.0");
	m_strName = _T("udp-client");
	m_strID = m_strName;
}

CCmmUdpClientConfig::~CCmmUdpClientConfig(void)
{
}


//´®ÐÐ»¯
long CCmmUdpClientConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmUdpClientConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetClientConfig::XmlReadOwn(oNode, pXmlRWKeys);
	
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oNode, m_nUseBroadcast);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oNode, m_strMulticastIP);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oNode, m_nMulticastPort);

	return 0;
}

long CCmmUdpClientConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetClientConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oElement, m_nUseBroadcast);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oElement, m_strMulticastIP);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oElement, m_nMulticastPort);

	return 0;
}

BOOL CCmmUdpClientConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmUdpClientConfig*)pDest)->m_strMulticastIP = m_strMulticastIP;
	((CCmmUdpClientConfig*)pDest)->m_nMulticastPort = m_nMulticastPort;
	((CCmmUdpClientConfig*)pDest)->m_nUseBroadcast = m_nUseBroadcast;

	return CCmmNetClientConfig::CopyOwn(pDest);
}



CBaseObject* CCmmUdpClientConfig::Clone()
{
	CCmmUdpClientConfig *pNew = new CCmmUdpClientConfig();

	Copy(pNew);

	return pNew;
}

