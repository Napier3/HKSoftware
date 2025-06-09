#include "StdAfx.h"
#include "EpCmmTcpServerConfig.h"

CEpCmmTcpServerConfig::CEpCmmTcpServerConfig(void)
{
}

CEpCmmTcpServerConfig::~CEpCmmTcpServerConfig(void)
{
}


//´®ÐÐ»¯
long CEpCmmTcpServerConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpCmmTcpServerConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CEpCmmConfigBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oNode, m_nLocalPort);

	return 0;
}

long CEpCmmTcpServerConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCmmConfigBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oElement, m_nLocalPort);

	return 0;
}


BOOL CEpCmmTcpServerConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CEpCmmTcpServerConfig*)pDest)->m_strLocalIP = m_strLocalIP;
	((CEpCmmTcpServerConfig*)pDest)->m_nLocalPort = m_nLocalPort;

	return CEpCmmConfigBase::CopyOwn(pDest);
}

