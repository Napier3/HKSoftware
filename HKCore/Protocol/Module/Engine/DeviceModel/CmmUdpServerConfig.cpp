#include "StdAfx.h"
#include "CmmUdpServerConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmUdpServerConfig::CCmmUdpServerConfig(void)
{
	m_nUseBroadcast = 0;
	m_nMulticastPort = 0;
	m_strMulticastIP = _T("0.0.0.0");
	m_strName = _T("udp-server");
	m_strID = m_strName;
}

CCmmUdpServerConfig::~CCmmUdpServerConfig(void)
{
}


//串行化
 long CCmmUdpServerConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
 {
	 return 0;
 }

 long CCmmUdpServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
 {
	 CCmmNetServerConfig::XmlReadOwn(oNode, pXmlRWKeys);

	 xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oNode, m_nUseBroadcast);
	 //组播地址
	 xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oNode, m_strMulticastIP);
	 xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oNode, m_nMulticastPort);

	 return 0;
 }

 long CCmmUdpServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
 {
	 CCmmNetServerConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	 xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oElement, m_nUseBroadcast);
	 xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oElement, m_strMulticastIP);
	 xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oElement, m_nMulticastPort);

	 return 0;
 }

 BOOL CCmmUdpServerConfig::CopyOwn(CBaseObject* pDest)
 {
	 if (this == pDest)
	 {
		 return TRUE;
	 }

	 ((CCmmUdpServerConfig*)pDest)->m_strMulticastIP = m_strMulticastIP;
	 ((CCmmUdpServerConfig*)pDest)->m_nMulticastPort = m_nMulticastPort;
	 ((CCmmUdpServerConfig*)pDest)->m_nUseBroadcast = m_nUseBroadcast;

	 return CCmmNetServerConfig::CopyOwn(pDest);
 }


 CBaseObject* CCmmUdpServerConfig::Clone()
 {
	 CCmmUdpServerConfig *pNew = new CCmmUdpServerConfig();

	 Copy(pNew);

	 return pNew;
 }

