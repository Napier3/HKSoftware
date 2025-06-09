//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.cpp  CXLangItem


#include "stdafx.h"
#include "XLangItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXLangItem::CXLangItem()
{
	//初始化属性
	m_pstrResourceRef = NULL;

	//初始化成员变量
}

CXLangItem::~CXLangItem()
{
}

long CXLangItem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTranslationKey, oNode, m_strTranslation);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcTextKey, oNode, m_strSrcText);
	return 0;
}

long CXLangItem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTranslationKey, oElement, m_strTranslation);
	xml_SetAttributeValue(pXmlKeys->m_strSrcTextKey, oElement, m_strSrcText);

	return 0;
}

long CXLangItem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTranslation);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrcText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strTranslation);
		BinarySerializeRead(oBinaryBuffer, m_strSrcText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strTranslation);
		BinarySerializeWrite(oBinaryBuffer, m_strSrcText);
	}
	return 0;
}

void CXLangItem::InitAfterRead()
{
}

BOOL CXLangItem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXLangItem *p = (CXLangItem*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strTranslation != p->m_strTranslation)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXLangItem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXLangItem *p = (CXLangItem*)pDest;

	p->m_strID = m_strID;
	p->m_strTranslation = m_strTranslation;
	p->m_strSrcText = m_strSrcText;

	return TRUE;
}

CBaseObject* CXLangItem::Clone()
{
	CXLangItem *p = new CXLangItem();
	Copy(p);
	return p;
}

