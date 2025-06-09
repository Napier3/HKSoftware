//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapSerialDevice.cpp  CEpCapSerialDevice


#include "stdafx.h"
#include "EpCapSerialDevice.h"

CEpCapSerialDevice::CEpCapSerialDevice()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CEpCapSerialDevice::~CEpCapSerialDevice()
{
}

long CEpCapSerialDevice::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strComIDKey, oNode, m_strComID);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CEpCapSerialDevice::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strComIDKey, oElement, m_strComID);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CEpCapSerialDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strComID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strComID);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strComID);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
	}
	return 0;
}

BOOL CEpCapSerialDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapSerialDevice *p = (CEpCapSerialDevice*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strComID != p->m_strComID)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapSerialDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapSerialDevice *p = (CEpCapSerialDevice*)pDest;

	p->m_strName = m_strName;
	p->m_strComID = m_strComID;
	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CEpCapSerialDevice::Clone()
{
	CEpCapSerialDevice *p = new CEpCapSerialDevice();
	Copy(p);
	return p;
}

