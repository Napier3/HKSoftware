//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceData.cpp  CEpDeviceData


#include "stdafx.h"
#include "EpDeviceData.h"

CEpDeviceData::CEpDeviceData()
{
	//初始化属性
	m_nUsed = 0;

	//初始化成员变量
}

CEpDeviceData::~CEpDeviceData()
{
}

long CEpDeviceData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strUsedKey, oNode, m_nUsed);

	return 0;
}

long CEpDeviceData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strUsedKey, oElement, m_nUsed);

	return 0;
}

long CEpDeviceData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nUsed);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nUsed);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nUsed);
	}

	return 0;
}

void CEpDeviceData::InitAfterRead()
{
}

BOOL CEpDeviceData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceData *p = (CEpDeviceData*)pObj;

	if(m_nUsed != p->m_nUsed)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpDeviceData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEpDeviceData *p = (CEpDeviceData*)pDest;

	p->m_nUsed = m_nUsed;

	return TRUE;
}

CBaseObject* CEpDeviceData::Clone()
{
	CEpDeviceData *p = new CEpDeviceData();
	Copy(p);
	return p;
}

