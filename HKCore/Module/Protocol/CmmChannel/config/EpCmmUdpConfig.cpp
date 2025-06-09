#include "StdAfx.h"
#include "EpCmmUdpConfig.h"

CEpCmmUdpConfig::CEpCmmUdpConfig(void)
{
	m_nMulticastPort = 0;
}

CEpCmmUdpConfig::~CEpCmmUdpConfig(void)
{
}


//串行化
 long CEpCmmUdpConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
 {
	 return 0;
 }

 long CEpCmmUdpConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
 {
	 CEpCmmConfigBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oNode, m_nLocalPort);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oNode, m_nUseBroadcast);

	 //组播地址
	 xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oNode, m_strMulticastIP);
	 xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oNode, m_nMulticastPort);

	 return 0;
 }

 long CEpCmmUdpConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
 {
	 CEpCmmConfigBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oElement, m_nLocalPort);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUseBroadcastKey, oElement, m_nUseBroadcast);

	 //组播地址
	 xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey, oElement, m_strMulticastIP);
	 xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strMulticastPortKey, oElement, m_nMulticastPort);

	 return 0;
 }

 BOOL CEpCmmUdpConfig::CopyOwn(CBaseObject* pDest)
 {
	 if (this == pDest)
	 {
		 return TRUE;
	 }


	((CEpCmmUdpConfig*)pDest)->m_strLocalIP = m_strLocalIP;
	((CEpCmmUdpConfig*)pDest)->m_nLocalPort = m_nLocalPort;
	 ((CEpCmmUdpConfig*)pDest)->m_strMulticastIP = m_strMulticastIP;
	 ((CEpCmmUdpConfig*)pDest)->m_nMulticastPort = m_nMulticastPort;

	 return CEpCmmConfigBase::CopyOwn(pDest);
 }