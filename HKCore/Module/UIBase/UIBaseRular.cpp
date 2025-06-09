//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseRular.cpp  CUIBaseRular


#include "stdafx.h"
#include "UIBaseRular.h"

CUIBaseRular::CUIBaseRular()
{
	//初始化属性
	m_nDrawBorder = 0;
	m_nDrawHalfScale = 0;
	m_nDrawTenthScale = 0;

	//初始化成员变量
}

CUIBaseRular::~CUIBaseRular()
{
}

long CUIBaseRular::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBkColorKey, oNode, m_crBkColor);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleColorKey, oNode, m_crScaleColor);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleShadowColorKey, oNode, m_crScaleShadowColor);
	xml_GetAttibuteValue(pXmlKeys->m_strTenthScaleColorKey, oNode, m_crTenthScaleColor);
	xml_GetAttibuteValue(pXmlKeys->m_strBorderColorKey, oNode, m_crBorderColor);
	xml_GetAttibuteValue(pXmlKeys->m_strTextColorKey, oNode, m_crTextColor);
	xml_GetAttibuteValue(pXmlKeys->m_strDrawBorderKey, oNode, m_nDrawBorder);
	xml_GetAttibuteValue(pXmlKeys->m_strDrawHalfScaleKey, oNode, m_nDrawHalfScale);
	xml_GetAttibuteValue(pXmlKeys->m_strDrawTenthScaleKey, oNode, m_nDrawTenthScale);
	return 0;
}

long CUIBaseRular::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBkColorKey, oElement, m_crBkColor);
	xml_SetAttributeValue(pXmlKeys->m_strScaleColorKey, oElement, m_crScaleColor);
	xml_SetAttributeValue(pXmlKeys->m_strScaleShadowColorKey, oElement, m_crScaleShadowColor);
	xml_SetAttributeValue(pXmlKeys->m_strTenthScaleColorKey, oElement, m_crTenthScaleColor);
	xml_SetAttributeValue(pXmlKeys->m_strBorderColorKey, oElement, m_crBorderColor);
	xml_SetAttributeValue(pXmlKeys->m_strTextColorKey, oElement, m_crTextColor);
	xml_SetAttributeValue(pXmlKeys->m_strDrawBorderKey, oElement, m_nDrawBorder);
	xml_SetAttributeValue(pXmlKeys->m_strDrawHalfScaleKey, oElement, m_nDrawHalfScale);
	xml_SetAttributeValue(pXmlKeys->m_strDrawTenthScaleKey, oElement, m_nDrawTenthScale);
	return 0;
}

long CUIBaseRular::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crScaleColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crTenthScaleColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crBorderColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crTextColor);
		BinarySerializeCalLen(oBinaryBuffer, m_nDrawBorder);
		BinarySerializeCalLen(oBinaryBuffer, m_nDrawHalfScale);
		BinarySerializeCalLen(oBinaryBuffer, m_nDrawTenthScale);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crBkColor);
		BinarySerializeRead(oBinaryBuffer, m_crScaleColor);
		BinarySerializeRead(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeRead(oBinaryBuffer, m_crTenthScaleColor);
		BinarySerializeRead(oBinaryBuffer, m_crBorderColor);
		BinarySerializeRead(oBinaryBuffer, m_crTextColor);
		BinarySerializeRead(oBinaryBuffer, m_nDrawBorder);
		BinarySerializeRead(oBinaryBuffer, m_nDrawHalfScale);
		BinarySerializeRead(oBinaryBuffer, m_nDrawTenthScale);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crBkColor);
		BinarySerializeWrite(oBinaryBuffer, m_crScaleColor);
		BinarySerializeWrite(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeWrite(oBinaryBuffer, m_crTenthScaleColor);
		BinarySerializeWrite(oBinaryBuffer, m_crBorderColor);
		BinarySerializeWrite(oBinaryBuffer, m_crTextColor);
		BinarySerializeWrite(oBinaryBuffer, m_nDrawBorder);
		BinarySerializeWrite(oBinaryBuffer, m_nDrawHalfScale);
		BinarySerializeWrite(oBinaryBuffer, m_nDrawTenthScale);
	}
	return 0;
}

BOOL CUIBaseRular::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseRular *p = (CUIBaseRular*)pObj;

	if(m_crBkColor != p->m_crBkColor)
	{
		return FALSE;
	}

	if(m_crScaleColor != p->m_crScaleColor)
	{
		return FALSE;
	}

	if(m_crScaleShadowColor != p->m_crScaleShadowColor)
	{
		return FALSE;
	}

	if(m_crTenthScaleColor != p->m_crTenthScaleColor)
	{
		return FALSE;
	}

	if(m_crBorderColor != p->m_crBorderColor)
	{
		return FALSE;
	}

	if(m_crTextColor != p->m_crTextColor)
	{
		return FALSE;
	}

	if(m_nDrawBorder != p->m_nDrawBorder)
	{
		return FALSE;
	}

	if(m_nDrawHalfScale != p->m_nDrawHalfScale)
	{
		return FALSE;
	}

	if(m_nDrawTenthScale != p->m_nDrawTenthScale)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIBaseRular::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseRular *p = (CUIBaseRular*)pDest;

	p->m_crBkColor = m_crBkColor;
	p->m_crScaleColor = m_crScaleColor;
	p->m_crScaleShadowColor = m_crScaleShadowColor;
	p->m_crTenthScaleColor = m_crTenthScaleColor;
	p->m_crBorderColor = m_crBorderColor;
	p->m_crTextColor = m_crTextColor;
	p->m_nDrawBorder = m_nDrawBorder;
	p->m_nDrawHalfScale = m_nDrawHalfScale;
	p->m_nDrawTenthScale = m_nDrawTenthScale;
	return TRUE;
}

CBaseObject* CUIBaseRular::Clone()
{
	CUIBaseRular *p = new CUIBaseRular();
	Copy(p);
	return p;
}

