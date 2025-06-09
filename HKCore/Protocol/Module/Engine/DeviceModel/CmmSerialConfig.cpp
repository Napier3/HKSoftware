#include "StdAfx.h"
#include "CmmSerialConfig.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmSerialConfig::CCmmSerialConfig(void)
{
	m_nBaudRate = 9600;
	m_nDataBit = 8;
	m_fStopBit = 1;
	m_nParity = 2;
	m_nPortNum = 1;

	m_strName = m_strID = L"serial";
}

CCmmSerialConfig::~CCmmSerialConfig(void)
{
}


//´®ÐÐ»¯
long CCmmSerialConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmSerialConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strPortNumKey,oNode,m_nPortNum);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strBaudRateKey,oNode,m_nBaudRate);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strByteSizeKey,oNode,m_nDataBit);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strStopBitsKey,oNode,m_fStopBit);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strParityKey,oNode,m_nParity);
	
	return 0;
}

long CCmmSerialConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strPortNumKey,oElement,m_nPortNum);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strBaudRateKey,oElement,m_nBaudRate);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strByteSizeKey,oElement,m_nDataBit);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strStopBitsKey,oElement,m_fStopBit);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strParityKey,oElement,m_nParity);

	return 0;
}

BOOL CCmmSerialConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmSerialConfig*)pDest)->m_nPortNum = m_nPortNum;
	((CCmmSerialConfig*)pDest)->m_nBaudRate = m_nBaudRate;
	((CCmmSerialConfig*)pDest)->m_nDataBit = m_nDataBit;
	((CCmmSerialConfig*)pDest)->m_fStopBit = m_fStopBit;
	((CCmmSerialConfig*)pDest)->m_nParity = m_nParity;

	return CCmmConfigBase::CopyOwn(pDest);
}



CBaseObject* CCmmSerialConfig::Clone()
{
	CCmmSerialConfig *pNew = new CCmmSerialConfig();

	Copy(pNew);

	return pNew;
}


BYTE CCmmSerialConfig::GetStopBits()
{ /* 0,1,2 = 1, 1.5, 2               */
	if ( fabs(m_fStopBit - 1) <=0.001 )
	{
		return 0;
	}

	if ( fabs(m_fStopBit - 1.5) <=0.001 )
	{
		return 1;
	}

	if ( fabs(m_fStopBit - 2) <=0.001 )
	{
		return 2;
	}

	return 0;
}

