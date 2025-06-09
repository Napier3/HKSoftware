//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenSerial.cpp  CEpCapGenSerial


#include "stdafx.h"
#include "EpCapGenSerial.h"

CEpCapGenSerial::CEpCapGenSerial()
{
	//初始化属性
	m_nBaudRate = 0;
	m_nDataBit = 0;
	m_nStopBit = 0;
	m_fParity = 0;
	m_nPort = 0;

	//初始化成员变量
}

CEpCapGenSerial::~CEpCapGenSerial()
{
}

long CEpCapGenSerial::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapGenBase::XmlReadOwn(oNode, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBaudRateKey, oNode, m_nBaudRate);
	xml_GetAttibuteValue(pXmlKeys->m_strDataBitKey, oNode, m_nDataBit);
	xml_GetAttibuteValue(pXmlKeys->m_strStopBitKey, oNode, m_nStopBit);
	xml_GetAttibuteValue(pXmlKeys->m_strParityKey, oNode, m_fParity);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	return 0;
}

long CEpCapGenSerial::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapGenBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBaudRateKey, oElement, m_nBaudRate);
	xml_SetAttributeValue(pXmlKeys->m_strDataBitKey, oElement, m_nDataBit);
	xml_SetAttributeValue(pXmlKeys->m_strStopBitKey, oElement, m_nStopBit);
	xml_SetAttributeValue(pXmlKeys->m_strParityKey, oElement, m_fParity);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	return 0;
}

BOOL CEpCapGenSerial::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapGenBase::CopyOwn(pDest);

	CEpCapGenSerial *p = (CEpCapGenSerial*)pDest;

	p->m_nBaudRate = m_nBaudRate;
	p->m_nDataBit = m_nDataBit;
	p->m_nStopBit = m_nStopBit;
	p->m_fParity = m_fParity;
	p->m_nPort = m_nPort;
	return TRUE;
}

CBaseObject* CEpCapGenSerial::Clone()
{
	CEpCapGenSerial *p = new CEpCapGenSerial();
	Copy(p);
	return p;
}

