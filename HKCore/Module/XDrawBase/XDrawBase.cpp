//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawBase.cpp  CXDrawBase


#include "stdafx.h"
#include "XDrawBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawBase::CXDrawBase()
{
	//初始化属性


	//初始化成员变量
	m_nStyle = 0;
	m_nWidth = 1;
}

CXDrawBase::~CXDrawBase()
{
}

long CXDrawBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForeColorKey, oNode, m_crForeColor);
	xml_GetAttibuteValue(pXmlKeys->m_strBackColorKey, oNode, m_crBkColor);
#ifdef _XDRAW_USE_EXTERN_ATTR_
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strShowKey, oNode, m_nShow);
#endif

	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_dwState);
	xml_GetAttibuteValue(pXmlKeys->m_strStyleKey, oNode, m_nStyle);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);

	return 0;
}

long CXDrawBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForeColorKey, oElement, m_crForeColor);
	xml_SetAttributeValue(pXmlKeys->m_strBackColorKey, oElement, m_crBkColor);
#ifdef _XDRAW_USE_EXTERN_ATTR_
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);
	xml_SetAttributeValue(pXmlKeys->m_strShowKey, oElement, m_nShow);
#endif

	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_dwState);

	xml_SetAttributeValue(pXmlKeys->m_strStyleKey, oElement, m_nStyle);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);

	return 0;
}

long CXDrawBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crForeColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColor);
#ifdef _XDRAW_USE_EXTERN_ATTR_
		BinarySerializeCalLen(oBinaryBuffer, m_nEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_nShow);
#endif
		BinarySerializeCalLen(oBinaryBuffer, m_dwState);
		BinarySerializeCalLen(oBinaryBuffer, m_nStyle);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crForeColor);
		BinarySerializeRead(oBinaryBuffer, m_crBkColor);
#ifdef _XDRAW_USE_EXTERN_ATTR_
		BinarySerializeRead(oBinaryBuffer, m_nEnable);
		BinarySerializeRead(oBinaryBuffer, m_nShow);
#endif
		BinarySerializeRead(oBinaryBuffer, m_dwState);
		BinarySerializeRead(oBinaryBuffer, m_nStyle);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crForeColor);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColor);
#ifdef _XDRAW_USE_EXTERN_ATTR_
		BinarySerializeWrite(oBinaryBuffer, m_nEnable);
		BinarySerializeWrite(oBinaryBuffer, m_nShow);
#endif
		BinarySerializeWrite(oBinaryBuffer, m_dwState);
		BinarySerializeWrite(oBinaryBuffer, m_nStyle);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
	}
	return 0;
}

BOOL CXDrawBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXDrawBase *p = (CXDrawBase*)pObj;

	if(m_crForeColor != p->m_crForeColor)
	{
		return FALSE;
	}

	if(m_dwState != p->m_dwState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase *p = (CXDrawBase*)pDest;

	p->m_crForeColor = m_crForeColor;
	p->m_crBkColor = m_crBkColor;
#ifdef _XDRAW_USE_EXTERN_ATTR_
	p->m_nEnable = m_nEnable;
	p->m_nShow = m_nShow;
#endif
	p->m_dwState = m_dwState;
	p->m_nStyle = m_nStyle;
	p->m_nWidth = m_nWidth;

	return TRUE;
}

void CXDrawBase::SetBeginPoint(double x, double y)		{	ASSERT (FALSE);	};
void CXDrawBase::SetEndPoint(double x, double y)		{	ASSERT (FALSE);	};

// 
// void CXDrawBase::SetPickState(BOOL bPick)
// {
// 	if (bPick)
// 	{
// 		m_dwState = XDRAW_STATE_PICKED;
// 	}
// 	else
// 	{
// 		m_dwState = XDRAW_STATE_NORMAL;
// 	}
// }
// 
