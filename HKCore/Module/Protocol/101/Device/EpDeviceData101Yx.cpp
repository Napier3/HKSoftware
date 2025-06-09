//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceData101Yx.cpp  CEpDeviceData101Yx


#include "stdafx.h"
#include "EpDeviceData101Yx.h"

CEpDeviceData101Yx::CEpDeviceData101Yx()
{
	//初始化属性

	//初始化成员变量
}

CEpDeviceData101Yx::~CEpDeviceData101Yx()
{
}

long CEpDeviceData101Yx::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CEpDeviceData101Yx::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CEpDeviceData101Yx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDeviceData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CEpDeviceData101Yx::InitAfterRead()
{
}

BOOL CEpDeviceData101Yx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceData101Yx *p = (CEpDeviceData101Yx*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpDeviceData101Yx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceData::CopyOwn(pDest);

	CEpDeviceData101Yx *p = (CEpDeviceData101Yx*)pDest;

	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CEpDeviceData101Yx::Clone()
{
	CEpDeviceData101Yx *p = new CEpDeviceData101Yx();
	Copy(p);
	return p;
}

BOOL CEpDeviceData101Yx::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEpDeviceData101Yx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEpDeviceData101Yx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
