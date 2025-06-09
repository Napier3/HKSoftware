//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceData101Yt.cpp  CEpDeviceData101Yt


#include "stdafx.h"
#include "EpDeviceData101Yt.h"

CEpDeviceData101Yt::CEpDeviceData101Yt()
{
	//初始化属性
	m_fValue = 0;
	m_fMax = 0;
	m_fMin = 0;

	//初始化成员变量
}

CEpDeviceData101Yt::~CEpDeviceData101Yt()
{
}

long CEpDeviceData101Yt::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_fValue);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_fMax);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_fMin);

	return 0;
}

long CEpDeviceData101Yt::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_fValue);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_fMax);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_fMin);

	return 0;
}

long CEpDeviceData101Yt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDeviceData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fMax);
		BinarySerializeCalLen(oBinaryBuffer, m_fMin);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fValue);
		BinarySerializeRead(oBinaryBuffer, m_fMax);
		BinarySerializeRead(oBinaryBuffer, m_fMin);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fValue);
		BinarySerializeWrite(oBinaryBuffer, m_fMax);
		BinarySerializeWrite(oBinaryBuffer, m_fMin);
	}
	return 0;
}

void CEpDeviceData101Yt::InitAfterRead()
{
}

BOOL CEpDeviceData101Yt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceData101Yt *p = (CEpDeviceData101Yt*)pObj;

	if(m_fValue != p->m_fValue)
	{
		return FALSE;
	}

	if(m_fMax != p->m_fMax)
	{
		return FALSE;
	}

	if(m_fMin != p->m_fMin)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CEpDeviceData101Yt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceData::CopyOwn(pDest);

	CEpDeviceData101Yt *p = (CEpDeviceData101Yt*)pDest;

	p->m_fValue = m_fValue;
	p->m_fMax = m_fMax;
	p->m_fMin = m_fMin;

	return TRUE;
}

CBaseObject* CEpDeviceData101Yt::Clone()
{
	CEpDeviceData101Yt *p = new CEpDeviceData101Yt();
	Copy(p);
	return p;
}

BOOL CEpDeviceData101Yt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEpDeviceData101Yt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEpDeviceData101Yt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
