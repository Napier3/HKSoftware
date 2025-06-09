//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLines.cpp  CGbCharLines


#include "stdafx.h"
#include "GbCharLines.h"

CGbCharLines::CGbCharLines()
{
	//初始化属性

	//初始化成员变量
}

CGbCharLines::~CGbCharLines()
{
}

long CGbCharLines::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strXeKey, oNode, m_strXe);
	xml_GetAttibuteValue(pXmlKeys->m_strYeKey, oNode, m_strYe);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CGbCharLines::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strXeKey, oElement, m_strXe);
	xml_SetAttributeValue(pXmlKeys->m_strYeKey, oElement, m_strYe);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

long CGbCharLines::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strXe);
		BinarySerializeCalLen(oBinaryBuffer, m_strYe);
		BinarySerializeCalLen(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXb);
		BinarySerializeRead(oBinaryBuffer, m_strYb);
		BinarySerializeRead(oBinaryBuffer, m_strXe);
		BinarySerializeRead(oBinaryBuffer, m_strYe);
		BinarySerializeRead(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXb);
		BinarySerializeWrite(oBinaryBuffer, m_strYb);
		BinarySerializeWrite(oBinaryBuffer, m_strXe);
		BinarySerializeWrite(oBinaryBuffer, m_strYe);
		BinarySerializeWrite(oBinaryBuffer, m_strDir);
	}
	return 0;
}

BOOL CGbCharLines::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharLines *p = (CGbCharLines*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
	{
		return FALSE;
	}

	if(m_strXe != p->m_strXe)
	{
		return FALSE;
	}

	if(m_strYe != p->m_strYe)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharLines::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLines *p = (CGbCharLines*)pDest;

	p->m_strXb = m_strXb;
	p->m_strYb = m_strYb;
	p->m_strXe = m_strXe;
	p->m_strYe = m_strYe;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CGbCharLines::Clone()
{
	CGbCharLines *p = new CGbCharLines();
	Copy(p);
	return p;
}

