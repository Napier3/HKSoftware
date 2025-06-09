//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseAxises.cpp  CUIBaseAxises


#include "stdafx.h"
#include "UIBaseAxises.h"

CUIBaseAxises::CUIBaseAxises()
{
	//初始化属性
	m_nLockHorVerScale = 0;

	//初始化成员变量
}

CUIBaseAxises::~CUIBaseAxises()
{
}

long CUIBaseAxises::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBkColorKey, oNode, m_crBkColor);
	xml_GetAttibuteValue(pXmlKeys->m_strGridColorKey, oNode, m_crGridColor);
	xml_GetAttibuteValue(pXmlKeys->m_strCenterColorKey, oNode, m_crCenterColor);
	xml_GetAttibuteValue(pXmlKeys->m_strAxisColorKey, oNode, m_crAxisColor);
	xml_GetAttibuteValue(pXmlKeys->m_strFrameColorKey, oNode, m_crFrameColor);
	xml_GetAttibuteValue(pXmlKeys->m_strLockHorVerScaleKey, oNode, m_nLockHorVerScale);
	return 0;
}

long CUIBaseAxises::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBkColorKey, oElement, m_crBkColor);
	xml_SetAttributeValue(pXmlKeys->m_strGridColorKey, oElement, m_crGridColor);
	xml_SetAttributeValue(pXmlKeys->m_strCenterColorKey, oElement, m_crCenterColor);
	xml_SetAttributeValue(pXmlKeys->m_strAxisColorKey, oElement, m_crAxisColor);
	xml_SetAttributeValue(pXmlKeys->m_strFrameColorKey, oElement, m_crFrameColor);
	xml_SetAttributeValue(pXmlKeys->m_strLockHorVerScaleKey, oElement, m_nLockHorVerScale);
	return 0;
}

long CUIBaseAxises::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crGridColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crCenterColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crAxisColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crFrameColor);
		BinarySerializeCalLen(oBinaryBuffer, m_nLockHorVerScale);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crBkColor);
		BinarySerializeRead(oBinaryBuffer, m_crGridColor);
		BinarySerializeRead(oBinaryBuffer, m_crCenterColor);
		BinarySerializeRead(oBinaryBuffer, m_crAxisColor);
		BinarySerializeRead(oBinaryBuffer, m_crFrameColor);
		BinarySerializeRead(oBinaryBuffer, m_nLockHorVerScale);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crBkColor);
		BinarySerializeWrite(oBinaryBuffer, m_crGridColor);
		BinarySerializeWrite(oBinaryBuffer, m_crCenterColor);
		BinarySerializeWrite(oBinaryBuffer, m_crAxisColor);
		BinarySerializeWrite(oBinaryBuffer, m_crFrameColor);
		BinarySerializeWrite(oBinaryBuffer, m_nLockHorVerScale);
	}
	return 0;
}

void CUIBaseAxises::InitAfterRead()
{
	
}

BOOL CUIBaseAxises::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseAxises *p = (CUIBaseAxises*)pObj;

	if(m_crBkColor != p->m_crBkColor)
	{
		return FALSE;
	}

	if(m_crGridColor != p->m_crGridColor)
	{
		return FALSE;
	}

	if(m_crCenterColor != p->m_crCenterColor)
	{
		return FALSE;
	}

	if(m_crAxisColor != p->m_crAxisColor)
	{
		return FALSE;
	}

	if(m_crFrameColor != p->m_crFrameColor)
	{
		return FALSE;
	}

	if(m_nLockHorVerScale != p->m_nLockHorVerScale)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIBaseAxises::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseAxises *p = (CUIBaseAxises*)pDest;

	p->m_crBkColor = m_crBkColor;
	p->m_crGridColor = m_crGridColor;
	p->m_crCenterColor = m_crCenterColor;
	p->m_crAxisColor = m_crAxisColor;
	p->m_crFrameColor = m_crFrameColor;
	p->m_nLockHorVerScale = m_nLockHorVerScale;
	return TRUE;
}

CBaseObject* CUIBaseAxises::Clone()
{
	CUIBaseAxises *p = new CUIBaseAxises();
	Copy(p);
	return p;
}

BOOL CUIBaseAxises::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIBASEAXIS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIBaseAxises::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIBaseAxisKey)
	{
		pNew = new CUIBaseAxis();
	}

	return pNew;
}

CExBaseObject* CUIBaseAxises::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIBASEAXIS)
	{
		pNew = new CUIBaseAxis();
	}

	return pNew;
}
