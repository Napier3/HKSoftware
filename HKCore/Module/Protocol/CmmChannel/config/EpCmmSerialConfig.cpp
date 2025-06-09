#include "StdAfx.h"
#include "EpCmmSerialConfig.h"
#include <math.h>

CEpCmmSerialConfig::CEpCmmSerialConfig(void)
{
	m_nBaudRate = 9600;
	m_nDataBit = 8;
	m_fStopBit = 1;
	m_nParity = 2;
	m_nPortNum = 1;

	m_strName = m_strID = L"serial";
}

CEpCmmSerialConfig::~CEpCmmSerialConfig(void)
{
}


//´®ÐÐ»¯
long CEpCmmSerialConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpCmmSerialConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strPortNumKey,oNode,m_nPortNum);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strBaudRateKey,oNode,m_nBaudRate);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strByteSizeKey,oNode,m_nDataBit);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strStopBitsKey,oNode,m_fStopBit);
	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strParityKey,oNode,m_nParity);
	
	return 0;
}

long CEpCmmSerialConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strPortNumKey,oElement,m_nPortNum);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strBaudRateKey,oElement,m_nBaudRate);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strByteSizeKey,oElement,m_nDataBit);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strStopBitsKey,oElement,m_fStopBit);
	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strParityKey,oElement,m_nParity);

	return 0;
}

BOOL CEpCmmSerialConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CEpCmmSerialConfig*)pDest)->m_nPortNum = m_nPortNum;
	((CEpCmmSerialConfig*)pDest)->m_nBaudRate = m_nBaudRate;
	((CEpCmmSerialConfig*)pDest)->m_nDataBit = m_nDataBit;
	((CEpCmmSerialConfig*)pDest)->m_fStopBit = m_fStopBit;
	((CEpCmmSerialConfig*)pDest)->m_nParity = m_nParity;

	return CEpCmmConfigBase::CopyOwn(pDest);
}

BYTE CEpCmmSerialConfig::GetStopBits()
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

