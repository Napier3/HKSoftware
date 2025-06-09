//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceData101Yc.cpp  CEpDeviceData101Yc


#include "stdafx.h"
#include "EpDeviceData101Yc.h"

CEpDeviceData101Yc::CEpDeviceData101Yc()
{
	//初始化属性
	m_fValue = 0;
	m_fMax = 0;
	m_fMin = 0;

	//初始化成员变量
}

CEpDeviceData101Yc::~CEpDeviceData101Yc()
{
}

long CEpDeviceData101Yc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_fValue);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_fMax);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_fMin);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CEpDeviceData101Yc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_fValue);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_fMax);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_fMin);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CEpDeviceData101Yc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDeviceData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fMax);
		BinarySerializeCalLen(oBinaryBuffer, m_fMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fValue);
		BinarySerializeRead(oBinaryBuffer, m_fMax);
		BinarySerializeRead(oBinaryBuffer, m_fMin);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fValue);
		BinarySerializeWrite(oBinaryBuffer, m_fMax);
		BinarySerializeWrite(oBinaryBuffer, m_fMin);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CEpDeviceData101Yc::InitAfterRead()
{
}

BOOL CEpDeviceData101Yc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceData101Yc *p = (CEpDeviceData101Yc*)pObj;

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

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpDeviceData101Yc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceData::CopyOwn(pDest);

	CEpDeviceData101Yc *p = (CEpDeviceData101Yc*)pDest;

	p->m_fValue = m_fValue;
	p->m_fMax = m_fMax;
	p->m_fMin = m_fMin;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CEpDeviceData101Yc::Clone()
{
	CEpDeviceData101Yc *p = new CEpDeviceData101Yc();
	Copy(p);
	return p;
}

BOOL CEpDeviceData101Yc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEpDeviceData101Yc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEpDeviceData101Yc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
