//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseText.cpp  CUIWindowText


#include "stdafx.h"
#include "UIBaseText.h"

CUIWindowText::CUIWindowText()
{
	//初始化属性

	//初始化成员变量
}

CUIWindowText::~CUIWindowText()
{
}

long CUIWindowText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForeColorKey, oNode, m_crForeColor);
	xml_GetAttibuteValue(pXmlKeys->m_strBackColorKey, oNode, m_crBackColor);
	xml_GetAttibuteValue(pXmlKeys->m_strDisableColorKey, oNode, m_crDisableColor);
	xml_GetAttibuteValue(pXmlKeys->m_strHighLightColorKey, oNode, m_crHighLightColor);
	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	return 0;
}

long CUIWindowText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForeColorKey, oElement, m_crForeColor);
	xml_SetAttributeValue(pXmlKeys->m_strBackColorKey, oElement, m_crBackColor);
	xml_SetAttributeValue(pXmlKeys->m_strDisableColorKey, oElement, m_crDisableColor);
	xml_SetAttributeValue(pXmlKeys->m_strHighLightColorKey, oElement, m_crHighLightColor);
	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	return 0;
}

long CUIWindowText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crForeColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crBackColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crDisableColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crHighLightColor);
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crForeColor);
		BinarySerializeRead(oBinaryBuffer, m_crBackColor);
		BinarySerializeRead(oBinaryBuffer, m_crDisableColor);
		BinarySerializeRead(oBinaryBuffer, m_crHighLightColor);
		BinarySerializeRead(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crForeColor);
		BinarySerializeWrite(oBinaryBuffer, m_crBackColor);
		BinarySerializeWrite(oBinaryBuffer, m_crDisableColor);
		BinarySerializeWrite(oBinaryBuffer, m_crHighLightColor);
		BinarySerializeWrite(oBinaryBuffer, m_strText);
	}
	return 0;
}

void CUIWindowText::InitAfterRead()
{
	
}

BOOL CUIWindowText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIWindowText *p = (CUIWindowText*)pObj;

	if(m_crForeColor != p->m_crForeColor)
	{
		return FALSE;
	}

	if(m_crBackColor != p->m_crBackColor)
	{
		return FALSE;
	}

	if(m_crDisableColor != p->m_crDisableColor)
	{
		return FALSE;
	}

	if(m_crHighLightColor != p->m_crHighLightColor)
	{
		return FALSE;
	}

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWindowText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowText *p = (CUIWindowText*)pDest;

	p->m_crForeColor = m_crForeColor;
	p->m_crBackColor = m_crBackColor;
	p->m_crDisableColor = m_crDisableColor;
	p->m_crHighLightColor = m_crHighLightColor;
	p->m_strText = m_strText;
	return TRUE;
}

CBaseObject* CUIWindowText::Clone()
{
	CUIWindowText *p = new CUIWindowText();
	Copy(p);
	return p;
}

