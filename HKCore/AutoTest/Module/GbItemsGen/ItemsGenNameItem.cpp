//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenNameItem.cpp  CItemsGenNameItem


#include "stdafx.h"
#include "ItemsGenNameItem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenNameItem::CItemsGenNameItem()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenNameItem::~CItemsGenNameItem()
{
}

long CItemsGenNameItem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strName_HeadKey, oNode, m_strNameHead);
	xml_GetAttibuteValue(pXmlKeys->m_strName_TailKey, oNode, m_strNameTail);
	xml_GetAttibuteValue(pXmlKeys->m_strID_HeadKey, oNode, m_strIDHead);
	xml_GetAttibuteValue(pXmlKeys->m_strID_TailKey, oNode, m_strIDTail);
	xml_GetAttibuteValue(pXmlKeys->m_strId_DataKey, oNode, m_strID_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	return 0;
}

long CItemsGenNameItem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strName_HeadKey, oElement, m_strNameHead);
	xml_SetAttributeValue(pXmlKeys->m_strName_TailKey, oElement, m_strNameTail);
	xml_SetAttributeValue(pXmlKeys->m_strID_HeadKey, oElement, m_strIDHead);
	xml_SetAttributeValue(pXmlKeys->m_strID_TailKey, oElement, m_strIDTail);
	xml_SetAttributeValue(pXmlKeys->m_strId_DataKey, oElement, m_strID_Data);
	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	return 0;
}

long CItemsGenNameItem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strNameHead);
		BinarySerializeCalLen(oBinaryBuffer, m_strNameTail);
		BinarySerializeCalLen(oBinaryBuffer, m_strIDHead);
		BinarySerializeCalLen(oBinaryBuffer, m_strIDTail);
		BinarySerializeCalLen(oBinaryBuffer, m_strID_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strNameHead);
		BinarySerializeRead(oBinaryBuffer, m_strNameTail);
		BinarySerializeRead(oBinaryBuffer, m_strIDHead);
		BinarySerializeRead(oBinaryBuffer, m_strIDTail);
		BinarySerializeRead(oBinaryBuffer, m_strID_Data);
		BinarySerializeRead(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strNameHead);
		BinarySerializeWrite(oBinaryBuffer, m_strNameTail);
		BinarySerializeWrite(oBinaryBuffer, m_strIDHead);
		BinarySerializeWrite(oBinaryBuffer, m_strIDTail);
		BinarySerializeWrite(oBinaryBuffer, m_strID_Data);
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
	}
	return 0;
}

void CItemsGenNameItem::InitAfterRead()
{
}

BOOL CItemsGenNameItem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenNameItem *p = (CItemsGenNameItem*)pObj;

	if(m_strNameHead != p->m_strNameHead)
	{
		return FALSE;
	}

	if(m_strNameTail != p->m_strNameTail)
	{
		return FALSE;
	}

	if(m_strIDHead != p->m_strIDHead)
	{
		return FALSE;
	}

	if(m_strIDTail != p->m_strIDTail)
	{
		return FALSE;
	}

	if(m_strID_Data != p->m_strID_Data)
	{
		return FALSE;
	}

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenNameItem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenNameItem *p = (CItemsGenNameItem*)pDest;

	p->m_strNameHead = m_strNameHead;
	p->m_strNameTail = m_strNameTail;
	p->m_strIDHead = m_strIDHead;
	p->m_strIDTail = m_strIDTail;
	p->m_strID_Data = m_strID_Data;
	p->m_strFormat = m_strFormat;
	return TRUE;
}

CBaseObject* CItemsGenNameItem::Clone()
{
	CItemsGenNameItem *p = new CItemsGenNameItem();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenNameItem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenNameItem *p = new CItemsGenNameItem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

