//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndRect.cpp  CUIWndRect


#include "stdafx.h"
#include "UIWndRect.h"

CUIWndRect::CUIWndRect()
{
	//初始化属性
	m_nPenWidth = 0;

	//初始化成员变量
}

CUIWndRect::~CUIWndRect()
{
}

long CUIWndRect::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPenColorKey, oNode, m_crPenColor);
	xml_GetAttibuteValue(pXmlKeys->m_strPenStypeKey, oNode, m_strPenStype);
	xml_GetAttibuteValue(pXmlKeys->m_strPenWidthKey, oNode, m_nPenWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strBrushColorKey, oNode, m_crBrushColor);
	return 0;
}

long CUIWndRect::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPenColorKey, oElement, m_crPenColor);
	xml_SetAttributeValue(pXmlKeys->m_strPenStypeKey, oElement, m_strPenStype);
	xml_SetAttributeValue(pXmlKeys->m_strPenWidthKey, oElement, m_nPenWidth);
	xml_SetAttributeValue(pXmlKeys->m_strBrushColorKey, oElement, m_crBrushColor);
	return 0;
}

long CUIWndRect::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crPenColor);
		BinarySerializeCalLen(oBinaryBuffer, m_strPenStype);
		BinarySerializeCalLen(oBinaryBuffer, m_nPenWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_crBrushColor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crPenColor);
		BinarySerializeRead(oBinaryBuffer, m_strPenStype);
		BinarySerializeRead(oBinaryBuffer, m_nPenWidth);
		BinarySerializeRead(oBinaryBuffer, m_crBrushColor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crPenColor);
		BinarySerializeWrite(oBinaryBuffer, m_strPenStype);
		BinarySerializeWrite(oBinaryBuffer, m_nPenWidth);
		BinarySerializeWrite(oBinaryBuffer, m_crBrushColor);
	}
	return 0;
}

void CUIWndRect::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndRect::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndRect *p = (CUIWndRect*)pObj;

	if(m_crPenColor != p->m_crPenColor)
	{
		return FALSE;
	}

	if(m_strPenStype != p->m_strPenStype)
	{
		return FALSE;
	}

	if(m_nPenWidth != p->m_nPenWidth)
	{
		return FALSE;
	}

	if(m_crBrushColor != p->m_crBrushColor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndRect::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndRect *p = (CUIWndRect*)pDest;

	p->m_crPenColor = m_crPenColor;
	p->m_strPenStype = m_strPenStype;
	p->m_nPenWidth = m_nPenWidth;
	p->m_crBrushColor = m_crBrushColor;
	return TRUE;
}

CBaseObject* CUIWndRect::Clone()
{
	CUIWndRect *p = new CUIWndRect();
	Copy(p);
	return p;
}

BOOL CUIWndRect::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndRect::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndRect::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}



BOOL CUIWndRect::UICreate(CWnd *pParent)
{
	if (m_pWindow != NULL)
	{
		LOG_WriteLawString("recreate Rect");
	}

	CRect rect = GetWndPosition();
	BOOL bState = FALSE;		
	bState = Create(NULL, WS_CHILD|WS_VISIBLE, 
		rect, pParent, GenerateWindowID()
		);

	if (!bState)
	{
		return FALSE;
	}

	ShowWindow(SW_SHOW);
	m_pWindow = this;

	return TRUE;
}

BOOL CUIWndRect::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}