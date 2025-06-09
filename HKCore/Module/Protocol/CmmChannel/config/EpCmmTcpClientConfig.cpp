#include "StdAfx.h"
#include "EpCmmTcpClientConfig.h"

CEpCmmTcpClientConfig::CEpCmmTcpClientConfig(void)
{
}

CEpCmmTcpClientConfig::~CEpCmmTcpClientConfig(void)
{
}


//´®ÐÐ»¯
long CEpCmmTcpClientConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpCmmTcpClientConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CEpCmmConfigBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oNode, m_nLocalPort);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey, oNode, m_strRemoteIP);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strRemotePortKey, oNode, m_nRemotePort);

	return 0;
}

long CEpCmmTcpClientConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCmmConfigBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oElement, m_nLocalPort);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey, oElement, m_strRemoteIP);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strRemotePortKey, oElement, m_nRemotePort);

	return 0;
}
