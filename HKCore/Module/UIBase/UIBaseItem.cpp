//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利




#include "stdafx.h"
#include "UIBaseItem.h"

CUIBaseItem::CUIBaseItem()
{
	m_pText = NULL;
	m_pFont = NULL;
	m_pEvents = NULL;
}

CUIBaseItem::~CUIBaseItem()
{
}

long CUIBaseItem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CUIBaseItem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CUIBaseItem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CUIBaseItem::InitAfterRead()
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
			m_pFont = (CUIBaseFont*)p;
		}
		else if (nClassID == UICLASSID_CUIWINDOWTEXT)
		{
			m_pText = (CUIWindowText *)p;
		}
		else if (nClassID == UICLASSID_CUIEVENTS)
		{
			m_pEvents = (CUIEvents *)p;
		}
	}

	if (m_pFont == NULL)
	{
		m_pFont = (CUIBaseFont*)AddNewChild(new CUIBaseFont());
	}

	if (m_pText == NULL)
	{
		m_pText = (CUIWindowText *)AddNewChild(new CUIWindowText());
	}

	if (m_pEvents == NULL)
	{
		m_pEvents = (CUIEvents *)AddNewChild(new CUIEvents());
	}

}

BOOL CUIBaseItem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseItem *p = (CUIBaseItem*)pObj;
	
	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIBaseItem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseItem *p = (CUIBaseItem*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CUIBaseItem::Clone()
{
	CUIBaseItem *p = new CUIBaseItem();
	Copy(p);
	return p;
}

