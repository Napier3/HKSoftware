//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenBinary.cpp  CUibGenBinary


#include "stdafx.h"
#include "UibGenBinary.h"

CUibGenBinary::CUibGenBinary()
{
	//初始化属性
	m_nValue = 0;
	m_fTurnTime = 0;
	m_fHoldTime = 0;

	//初始化成员变量
}

CUibGenBinary::~CUibGenBinary()
{
}

long CUibGenBinary::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_nValue);
	xml_GetAttibuteValue(pXmlKeys->m_strTurnTimeKey, oNode, m_fTurnTime);
	xml_GetAttibuteValue(pXmlKeys->m_strHoldTimeKey, oNode, m_fHoldTime);
	return 0;
}

long CUibGenBinary::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_nValue);
	xml_SetAttributeValue(pXmlKeys->m_strTurnTimeKey, oElement, m_fTurnTime);
	xml_SetAttributeValue(pXmlKeys->m_strHoldTimeKey, oElement, m_fHoldTime);
	return 0;
}

long CUibGenBinary::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fTurnTime);
		BinarySerializeCalLen(oBinaryBuffer, m_fHoldTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nValue);
		BinarySerializeRead(oBinaryBuffer, m_fTurnTime);
		BinarySerializeRead(oBinaryBuffer, m_fHoldTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nValue);
		BinarySerializeWrite(oBinaryBuffer, m_fTurnTime);
		BinarySerializeWrite(oBinaryBuffer, m_fHoldTime);
	}
	return 0;
}

void CUibGenBinary::InitAfterRead()
{
}

BOOL CUibGenBinary::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUibGenBinary *p = (CUibGenBinary*)pObj;

	if(m_nValue != p->m_nValue)
	{
		return FALSE;
	}

	if(m_fTurnTime != p->m_fTurnTime)
	{
		return FALSE;
	}

	if(m_fHoldTime != p->m_fHoldTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUibGenBinary::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUibGenBinary *p = (CUibGenBinary*)pDest;

	p->m_nValue = m_nValue;
	p->m_fTurnTime = m_fTurnTime;
	p->m_fHoldTime = m_fHoldTime;
	return TRUE;
}

CBaseObject* CUibGenBinary::Clone()
{
	CUibGenBinary *p = new CUibGenBinary();
	Copy(p);
	return p;
}

