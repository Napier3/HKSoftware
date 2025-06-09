//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseFont.cpp  CUIBaseFont


#include "stdafx.h"
#include "UIBaseFont.h"
#include "..\API\GloblaDrawFunctions.h"

CUIBaseFont CUIBaseFont::g_oUIBaseFont;

CUIBaseFont::CUIBaseFont()
{
	//初始化属性
	m_nSize = 12;
	m_nItalic = 0;
	m_nBold = 0;
	m_nEscapement = 0;

	//初始化成员变量
	m_strID = _T("Tahoma");
	m_pFont = NULL;
}

CUIBaseFont::~CUIBaseFont()
{
	if (m_pFont != NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}

long CUIBaseFont::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	xml_GetAttibuteValue(pXmlKeys->m_strItalicKey, oNode, m_nItalic);
	xml_GetAttibuteValue(pXmlKeys->m_strBoldKey, oNode, m_nBold);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strColorKey, oNode, m_crColor);
	xml_GetAttibuteValue(pXmlKeys->m_strEscapementKey, oNode, m_nEscapement);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkColorKey, oNode, m_crBkColor);

	return 0;
}

long CUIBaseFont::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	xml_SetAttributeValue(pXmlKeys->m_strItalicKey, oElement, m_nItalic);
	xml_SetAttributeValue(pXmlKeys->m_strBoldKey, oElement, m_nBold);
	xml_SetAttributeValue_Color(pXmlKeys->m_strColorKey, oElement, m_crColor);
	xml_SetAttributeValue(pXmlKeys->m_strEscapementKey, oElement, m_nEscapement);
	xml_SetAttributeValue_Color(pXmlKeys->m_strBkColorKey, oElement, m_crBkColor);

	return 0;
}

long CUIBaseFont::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nItalic);
		BinarySerializeCalLen(oBinaryBuffer, m_nBold);
		BinarySerializeCalLen(oBinaryBuffer, m_crColor);
		BinarySerializeCalLen(oBinaryBuffer, m_nEscapement);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSize);
		BinarySerializeRead(oBinaryBuffer, m_nItalic);
		BinarySerializeRead(oBinaryBuffer, m_nBold);
		BinarySerializeRead(oBinaryBuffer, m_crColor);
		BinarySerializeRead(oBinaryBuffer, m_nEscapement);
		BinarySerializeRead(oBinaryBuffer, m_crBkColor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
		BinarySerializeWrite(oBinaryBuffer, m_nItalic);
		BinarySerializeWrite(oBinaryBuffer, m_nBold);
		BinarySerializeWrite(oBinaryBuffer, m_crColor);
		BinarySerializeWrite(oBinaryBuffer, m_nEscapement);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColor);
	}
	return 0;
}

BOOL CUIBaseFont::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseFont *p = (CUIBaseFont*)pObj;

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	if(m_nItalic != p->m_nItalic)
	{
		return FALSE;
	}

	if(m_nBold != p->m_nBold)
	{
		return FALSE;
	}

	if(m_crColor != p->m_crColor)
	{
		return FALSE;
	}

	if(m_nEscapement != p->m_nEscapement)
	{
		return FALSE;
	}

	if(m_crBkColor != p->m_crBkColor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIBaseFont::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseFont *p = (CUIBaseFont*)pDest;

	p->m_nSize = m_nSize;
	p->m_nItalic = m_nItalic;
	p->m_nBold = m_nBold;
	p->m_crColor = m_crColor;
	p->m_nEscapement = m_nEscapement;
	p->m_crBkColor = m_crBkColor;
	return TRUE;
}

CBaseObject* CUIBaseFont::Clone()
{
	CUIBaseFont *p = new CUIBaseFont();
	Copy(p);
	return p;
}

CFont* CUIBaseFont::GetFont()
{
	if (m_pFont != NULL)
	{
		return m_pFont;
	}

	if (m_strID.GetLength() == 0)
	{
		m_strID = _T("Tahoma");
	}

	m_pFont = new CFont();
	LOGFONT lf = InitLogFont();

#ifdef _UNICODE
	wcscpy(lf.lfFaceName, m_strID);
#else
	strcpy(lf.lfFaceName, m_strID);
#endif

	lf.lfHeight = m_nSize;
	lf.lfItalic = (BYTE)m_nItalic;
	lf.lfWeight = (m_nBold == 0 ? 400 : 600);

	if(m_nEscapement > 0)
	{
		lf.lfEscapement = m_nEscapement;
	}

	m_pFont->CreateFontIndirect(&lf);

	return m_pFont;
}

LOGFONT CUIBaseFont::GetLogFont()
{
	LOGFONT lf = InitLogFont();	

#ifdef _UNICODE
	wcscpy(lf.lfFaceName, m_strName);
#else
	strcpy(lf.lfFaceName, m_strName);
#endif

	lf.lfHeight = m_nSize;
	lf.lfItalic = (BYTE)m_nItalic;
	lf.lfWeight = (m_nBold == 0 ? 400 : 600);

	return lf;
}
