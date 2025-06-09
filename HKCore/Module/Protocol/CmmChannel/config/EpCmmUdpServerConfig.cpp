#include "StdAfx.h"
#include "EpCmmUdpServerConfig.h"

CEpCmmUdpServerConfig::CEpCmmUdpServerConfig(void)
{
	m_nMulticastPort = 0;
}

CEpCmmUdpServerConfig::~CEpCmmUdpServerConfig(void)
{
}


//´®ÐÐ»¯
 long CEpCmmUdpServerConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
 {
	 return 0;
 }

 long CEpCmmUdpServerConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
 {
	 CEpCmmUdpConfig::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strClientIPKey, oNode, m_strClientIP);

	 return 0;
 }

 long CEpCmmUdpServerConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
 {
	 CEpCmmUdpConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strClientIPKey, oElement, m_strClientIP);

	 return 0;
 }

 BOOL CEpCmmUdpServerConfig::CopyOwn(CBaseObject* pDest)
 {
	 if (this == pDest)
	 {
		 return TRUE;
	 }


	((CEpCmmUdpServerConfig*)pDest)->m_strLocalIP = m_strLocalIP;
	((CEpCmmUdpServerConfig*)pDest)->m_nLocalPort = m_nLocalPort;
	 ((CEpCmmUdpServerConfig*)pDest)->m_strMulticastIP = m_strMulticastIP;
	 ((CEpCmmUdpServerConfig*)pDest)->m_nMulticastPort = m_nMulticastPort;

	 return CEpCmmConfigBase::CopyOwn(pDest);
 }