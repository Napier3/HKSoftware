#include "StdAfx.h"
#include "CmmNetServerConfig.h"
#include "CmmNetClientConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmNetServerConfig::CCmmNetServerConfig(void)
{
	m_nLocalPort = 80;
	m_strLocalIP = L"0.0.0.0";
	m_bPostConnectFinishMsgAfterAccept = FALSE;
}

CCmmNetServerConfig::~CCmmNetServerConfig(void)
{
}


//´®ÐÐ»¯
long CCmmNetServerConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmNetServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oNode, m_nLocalPort);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strClientIPKey, oNode, m_strClientIP);

	return 0;
}

long CCmmNetServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey, oElement, m_nLocalPort);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strClientIPKey, oElement, m_strClientIP);

	return 0;
}

BOOL CCmmNetServerConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmNetServerConfig*)pDest)->m_strLocalIP = m_strLocalIP;
	((CCmmNetServerConfig*)pDest)->m_nLocalPort = m_nLocalPort;
	((CCmmNetServerConfig*)pDest)->m_strClientIP = m_strClientIP;

	return CCmmConfigBase::CopyOwn(pDest);
}