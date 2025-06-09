//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceData101Yk.cpp  CEpDeviceData101Yk


#include "stdafx.h"
#include "EpDeviceData101Yk.h"

CEpDeviceData101Yk::CEpDeviceData101Yk()
{
	//初始化属性
	m_nValue = 0;

	//初始化成员变量
}

CEpDeviceData101Yk::~CEpDeviceData101Yk()
{
}

long CEpDeviceData101Yk::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_nValue);
	return 0;
}

long CEpDeviceData101Yk::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_nValue);
	return 0;
}

long CEpDeviceData101Yk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDeviceData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nValue);
	}
	return 0;
}

void CEpDeviceData101Yk::InitAfterRead()
{
}

BOOL CEpDeviceData101Yk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceData101Yk *p = (CEpDeviceData101Yk*)pObj;

	if(m_nValue != p->m_nValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpDeviceData101Yk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceData::CopyOwn(pDest);

	CEpDeviceData101Yk *p = (CEpDeviceData101Yk*)pDest;

	p->m_nValue = m_nValue;
	return TRUE;
}

CBaseObject* CEpDeviceData101Yk::Clone()
{
	CEpDeviceData101Yk *p = new CEpDeviceData101Yk();
	Copy(p);
	return p;
}

BOOL CEpDeviceData101Yk::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEpDeviceData101Yk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEpDeviceData101Yk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
