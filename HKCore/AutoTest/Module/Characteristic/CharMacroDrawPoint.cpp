//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDrawPoint.cpp  CCharMacroDrawPoint


#include "stdafx.h"
#include "CharMacroDrawPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharMacroDrawPoint::CCharMacroDrawPoint()
{
	//初始化属性

	//初始化成员变量
}

CCharMacroDrawPoint::~CCharMacroDrawPoint()
{
}

long CCharMacroDrawPoint::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_strX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_strY);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strColorKey, oNode, m_strColor);
	return 0;
}

long CCharMacroDrawPoint::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_strX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_strY);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strColorKey, oElement, m_strColor);
	return 0;
}

BOOL CCharMacroDrawPoint::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharMacroDrawPoint *p = (CCharMacroDrawPoint*)pObj;

	if(m_strX != p->m_strX)
	{
		return FALSE;
	}

	if(m_strY != p->m_strY)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strColor != p->m_strColor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharMacroDrawPoint::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharMacroDrawPoint *p = (CCharMacroDrawPoint*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_strType = m_strType;
	p->m_strColor = m_strColor;
	return TRUE;
}

CBaseObject* CCharMacroDrawPoint::Clone()
{
	CCharMacroDrawPoint *p = new CCharMacroDrawPoint();
	Copy(p);
	return p;
}

long CCharMacroDrawPoint::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strX);
		BinarySerializeCalLen(oBinaryBuffer, m_strY);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strColor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strX);
		BinarySerializeRead(oBinaryBuffer, m_strY);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strColor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strX);
		BinarySerializeWrite(oBinaryBuffer, m_strY);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strColor);
	}
	return 0;
}

