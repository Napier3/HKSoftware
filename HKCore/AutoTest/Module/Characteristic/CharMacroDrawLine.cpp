//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDrawLine.cpp  CCharMacroDrawLine


#include "stdafx.h"
#include "CharMacroDrawLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharMacroDrawLine::CCharMacroDrawLine()
{
	//初始化属性

	//初始化成员变量
}

CCharMacroDrawLine::~CCharMacroDrawLine()
{
}

long CCharMacroDrawLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strXeKey, oNode, m_strXe);
	xml_GetAttibuteValue(pXmlKeys->m_strYeKey, oNode, m_strYe);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strColorKey, oNode, m_strColor);
	return 0;
}

long CCharMacroDrawLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strXeKey, oElement, m_strXe);
	xml_SetAttributeValue(pXmlKeys->m_strYeKey, oElement, m_strYe);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strColorKey, oElement, m_strColor);
	return 0;
}

BOOL CCharMacroDrawLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharMacroDrawLine *p = (CCharMacroDrawLine*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strXe != p->m_strXe)
	{
		return FALSE;
	}

	if(m_strYe != p->m_strYe)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
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

BOOL CCharMacroDrawLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharMacroDrawLine *p = (CCharMacroDrawLine*)pDest;

	p->m_strXb = m_strXb;
	p->m_strXe = m_strXe;
	p->m_strYe = m_strYe;
	p->m_strYb = m_strYb;
	p->m_strType = m_strType;
	p->m_strColor = m_strColor;
	return TRUE;
}

CBaseObject* CCharMacroDrawLine::Clone()
{
	CCharMacroDrawLine *p = new CCharMacroDrawLine();
	Copy(p);
	return p;
}

CExBaseObject* CCharMacroDrawLine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CCharMacroDrawLine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CCharMacroDrawLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strXe);
		BinarySerializeCalLen(oBinaryBuffer, m_strYe);
		BinarySerializeCalLen(oBinaryBuffer, m_strYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strColor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXb);
		BinarySerializeRead(oBinaryBuffer, m_strXe);
		BinarySerializeRead(oBinaryBuffer, m_strYe);
		BinarySerializeRead(oBinaryBuffer, m_strYb);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strColor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXb);
		BinarySerializeWrite(oBinaryBuffer, m_strXe);
		BinarySerializeWrite(oBinaryBuffer, m_strYe);
		BinarySerializeWrite(oBinaryBuffer, m_strYb);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strColor);
	}
	return 0;
}

