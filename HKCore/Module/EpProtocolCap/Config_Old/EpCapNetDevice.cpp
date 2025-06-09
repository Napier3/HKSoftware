//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetDevice.cpp  CEpCapNetDevice


#include "stdafx.h"
#include "EpCapNetDevice.h"

CEpCapNetDevice::CEpCapNetDevice()
{
	//初始化属性
	m_nIndex = 0;
	m_nTcp = 0;
	m_nUdp = 0;

	//初始化成员变量
}

CEpCapNetDevice::~CEpCapNetDevice()
{
}

long CEpCapNetDevice::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strIPKey, oNode, m_strIP);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_strProtocol);
	xml_GetAttibuteValue(pXmlKeys->m_strTcpKey, oNode, m_nTcp);
	xml_GetAttibuteValue(pXmlKeys->m_strUdpKey, oNode, m_nUdp);
	return 0;
}

long CEpCapNetDevice::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strIPKey, oElement, m_strIP);
	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_strProtocol);
	xml_SetAttributeValue(pXmlKeys->m_strTcpKey, oElement, m_nTcp);
	xml_SetAttributeValue(pXmlKeys->m_strUdpKey, oElement, m_nUdp);
	return 0;
}

long CEpCapNetDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strIP);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol);
		BinarySerializeCalLen(oBinaryBuffer, m_nTcp);
		BinarySerializeCalLen(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_strIP);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol);
		BinarySerializeRead(oBinaryBuffer, m_nTcp);
		BinarySerializeRead(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strIP);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol);
		BinarySerializeWrite(oBinaryBuffer, m_nTcp);
		BinarySerializeWrite(oBinaryBuffer, m_nUdp);
	}
	return 0;
}

void CEpCapNetDevice::InitAfterRead()
{
}

BOOL CEpCapNetDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetDevice *p = (CEpCapNetDevice*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_strProtocol != p->m_strProtocol)
	{
		return FALSE;
	}

	if(m_nTcp != p->m_nTcp)
	{
		return FALSE;
	}

	if(m_nUdp != p->m_nUdp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetDevice *p = (CEpCapNetDevice*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex = m_nIndex;
	p->m_strIP = m_strIP;
	p->m_strProtocol = m_strProtocol;
	p->m_nTcp = m_nTcp;
	p->m_nUdp = m_nUdp;
	return TRUE;
}

CBaseObject* CEpCapNetDevice::Clone()
{
	CEpCapNetDevice *p = new CEpCapNetDevice();
	Copy(p);
	return p;
}

