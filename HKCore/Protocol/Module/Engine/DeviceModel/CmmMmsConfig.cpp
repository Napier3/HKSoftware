#include "StdAfx.h"
#include "CmmMmsConfig.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmMmsConfig::CCmmMmsConfig(void)
{
	m_strRemoteIP = _T("192.168.1.100");
	m_strName = m_strID = _T("mms");
	m_bPingState = FALSE;

	m_strPSW = _T("");//123456789012
	m_strKey = _T("");//1234567890123456

}

CCmmMmsConfig::~CCmmMmsConfig(void)
{
}


//´®ÐÐ»¯
long CCmmMmsConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmMmsConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,oNode, m_strRemoteIP);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,oNode, m_strPSW);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,oNode, m_strKey);
	
	return 0;
}

long CCmmMmsConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,oElement,m_strRemoteIP);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,oElement,m_strPSW);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,oElement,m_strKey);

	return 0;
}

BOOL CCmmMmsConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmMmsConfig*)pDest)->m_strRemoteIP = m_strRemoteIP;
	((CCmmMmsConfig*)pDest)->m_strPSW = m_strPSW;
	((CCmmMmsConfig*)pDest)->m_strKey = m_strKey;

	return CCmmConfigBase::CopyOwn(pDest);
}



CBaseObject* CCmmMmsConfig::Clone()
{
	CCmmMmsConfig *pNew = new CCmmMmsConfig();

	Copy(pNew);

	return pNew;
}
