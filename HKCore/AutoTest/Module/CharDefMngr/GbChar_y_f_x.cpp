//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbChar_y_f_x.cpp  CGbChar_y_f_x


#include "stdafx.h"
#include "GbChar_y_f_x.h"

CGbChar_y_f_x::CGbChar_y_f_x()
{
	//初始化属性

	//初始化成员变量
}

CGbChar_y_f_x::~CGbChar_y_f_x()
{
}

long CGbChar_y_f_x::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_strMin);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_strMax);
	xml_GetAttibuteValue(pXmlKeys->m_strExpressionKey, oNode, m_strExpression);
	return 0;
}

long CGbChar_y_f_x::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_strMin);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_strMax);
	xml_SetAttributeValue(pXmlKeys->m_strExpressionKey, oElement, m_strExpression);
	return 0;
}

long CGbChar_y_f_x::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strExpression);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMin);
		BinarySerializeRead(oBinaryBuffer, m_strMax);
		BinarySerializeRead(oBinaryBuffer, m_strExpression);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMin);
		BinarySerializeWrite(oBinaryBuffer, m_strMax);
		BinarySerializeWrite(oBinaryBuffer, m_strExpression);
	}
	return 0;
}

BOOL CGbChar_y_f_x::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbChar_y_f_x *p = (CGbChar_y_f_x*)pObj;

	if(m_strMin != p->m_strMin)
	{
		return FALSE;
	}

	if(m_strMax != p->m_strMax)
	{
		return FALSE;
	}

	if(m_strExpression != p->m_strExpression)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbChar_y_f_x::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbChar_y_f_x *p = (CGbChar_y_f_x*)pDest;

	p->m_strMin = m_strMin;
	p->m_strMax = m_strMax;
	p->m_strExpression = m_strExpression;
	return TRUE;
}

CBaseObject* CGbChar_y_f_x::Clone()
{
	CGbChar_y_f_x *p = new CGbChar_y_f_x();
	Copy(p);
	return p;
}

