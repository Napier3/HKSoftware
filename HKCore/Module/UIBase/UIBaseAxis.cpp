//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseAxis.cpp  CUIBaseAxis


#include "stdafx.h"
#include "UIBaseAxis.h"

CUIBaseAxis::CUIBaseAxis()
{
	//初始化属性
	m_nRangeMin = 0;
	m_nRangeMax = 0;
	m_nScaleType = 0;
	m_nScaleMinPixel = 0;
	m_nUseHalfScale = 0;
	m_nUseTenthScale = 0;

	//初始化成员变量
	m_pTitleFont = NULL;
	m_pScaleFont = NULL;
}

CUIBaseAxis::~CUIBaseAxis()
{
}

long CUIBaseAxis::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRangeMinKey, oNode, m_nRangeMin);
	xml_GetAttibuteValue(pXmlKeys->m_strRangeMaxKey, oNode, m_nRangeMax);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleTypeKey, oNode, m_nScaleType);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleMinPixelKey, oNode, m_nScaleMinPixel);
	xml_GetAttibuteValue(pXmlKeys->m_strUseHalfScaleKey, oNode, m_nUseHalfScale);
	xml_GetAttibuteValue(pXmlKeys->m_strUseTenthScaleKey, oNode, m_nUseTenthScale);
	xml_GetAttibuteValue(pXmlKeys->m_strBkColorFromKey, oNode, m_crBkColorFrom);
	xml_GetAttibuteValue(pXmlKeys->m_strBkColorToKey, oNode, m_crBkColorTo);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleColorKey, oNode, m_crScaleColor);
	xml_GetAttibuteValue(pXmlKeys->m_strScaleShadowColorKey, oNode, m_crScaleShadowColor);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CUIBaseAxis::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRangeMinKey, oElement, m_nRangeMin);
	xml_SetAttributeValue(pXmlKeys->m_strRangeMaxKey, oElement, m_nRangeMax);
	xml_SetAttributeValue(pXmlKeys->m_strScaleTypeKey, oElement, m_nScaleType);
	xml_SetAttributeValue(pXmlKeys->m_strScaleMinPixelKey, oElement, m_nScaleMinPixel);
	xml_SetAttributeValue(pXmlKeys->m_strUseHalfScaleKey, oElement, m_nUseHalfScale);
	xml_SetAttributeValue(pXmlKeys->m_strUseTenthScaleKey, oElement, m_nUseTenthScale);
	xml_SetAttributeValue(pXmlKeys->m_strBkColorFromKey, oElement, m_crBkColorFrom);
	xml_SetAttributeValue(pXmlKeys->m_strBkColorToKey, oElement, m_crBkColorTo);
	xml_SetAttributeValue(pXmlKeys->m_strScaleColorKey, oElement, m_crScaleColor);
	xml_SetAttributeValue(pXmlKeys->m_strScaleShadowColorKey, oElement, m_crScaleShadowColor);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CUIBaseAxis::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nRangeMin);
		BinarySerializeCalLen(oBinaryBuffer, m_nRangeMax);
		BinarySerializeCalLen(oBinaryBuffer, m_nScaleType);
		BinarySerializeCalLen(oBinaryBuffer, m_nScaleMinPixel);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseHalfScale);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseTenthScale);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeCalLen(oBinaryBuffer, m_crScaleColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nRangeMin);
		BinarySerializeRead(oBinaryBuffer, m_nRangeMax);
		BinarySerializeRead(oBinaryBuffer, m_nScaleType);
		BinarySerializeRead(oBinaryBuffer, m_nScaleMinPixel);
		BinarySerializeRead(oBinaryBuffer, m_nUseHalfScale);
		BinarySerializeRead(oBinaryBuffer, m_nUseTenthScale);
		BinarySerializeRead(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeRead(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeRead(oBinaryBuffer, m_crScaleColor);
		BinarySerializeRead(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nRangeMin);
		BinarySerializeWrite(oBinaryBuffer, m_nRangeMax);
		BinarySerializeWrite(oBinaryBuffer, m_nScaleType);
		BinarySerializeWrite(oBinaryBuffer, m_nScaleMinPixel);
		BinarySerializeWrite(oBinaryBuffer, m_nUseHalfScale);
		BinarySerializeWrite(oBinaryBuffer, m_nUseTenthScale);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeWrite(oBinaryBuffer, m_crScaleColor);
		BinarySerializeWrite(oBinaryBuffer, m_crScaleShadowColor);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CUIBaseAxis::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == UICLASSID_CUIBASEFONT)
		{
			m_pTitleFont = (CUIBaseFont*)p;
		}
		else if (nClassID == UICLASSID_CUIBASEFONT)
		{
			m_pScaleFont = (CUIBaseFont*)p;
		}
	}

	if (m_pTitleFont == NULL)
	{
		m_pTitleFont = (CUIBaseFont*)AddNewChild(new CUIBaseFont());
	}

	if (m_pScaleFont == NULL)
	{
		m_pScaleFont = (CUIBaseFont*)AddNewChild(new CUIBaseFont());
	}

}

BOOL CUIBaseAxis::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseAxis *p = (CUIBaseAxis*)pObj;

	if(m_nRangeMin != p->m_nRangeMin)
	{
		return FALSE;
	}

	if(m_nRangeMax != p->m_nRangeMax)
	{
		return FALSE;
	}

	if(m_nScaleType != p->m_nScaleType)
	{
		return FALSE;
	}

	if(m_nScaleMinPixel != p->m_nScaleMinPixel)
	{
		return FALSE;
	}

	if(m_nUseHalfScale != p->m_nUseHalfScale)
	{
		return FALSE;
	}

	if(m_nUseTenthScale != p->m_nUseTenthScale)
	{
		return FALSE;
	}

	if(m_crBkColorFrom != p->m_crBkColorFrom)
	{
		return FALSE;
	}

	if(m_crBkColorTo != p->m_crBkColorTo)
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

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIBaseAxis::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseAxis *p = (CUIBaseAxis*)pDest;

	p->m_nRangeMin = m_nRangeMin;
	p->m_nRangeMax = m_nRangeMax;
	p->m_nScaleType = m_nScaleType;
	p->m_nScaleMinPixel = m_nScaleMinPixel;
	p->m_nUseHalfScale = m_nUseHalfScale;
	p->m_nUseTenthScale = m_nUseTenthScale;
	p->m_crBkColorFrom = m_crBkColorFrom;
	p->m_crBkColorTo = m_crBkColorTo;
	p->m_crScaleColor = m_crScaleColor;
	p->m_crScaleShadowColor = m_crScaleShadowColor;
	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CUIBaseAxis::Clone()
{
	CUIBaseAxis *p = new CUIBaseAxis();
	Copy(p);
	return p;
}

