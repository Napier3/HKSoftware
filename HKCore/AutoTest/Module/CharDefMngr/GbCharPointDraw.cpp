//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharPointDraw.cpp  CGbCharPointDraw


#include "stdafx.h"
#include "GbCharPointDraw.h"

CGbCharPointDraw::CGbCharPointDraw()
{
	//初始化属性

	//初始化成员变量
}

CGbCharPointDraw::~CGbCharPointDraw()
{
}

long CGbCharPointDraw::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXidKey, oNode, m_strXid);
	xml_GetAttibuteValue(pXmlKeys->m_strYidKey, oNode, m_strYid);
	return 0;
}

long CGbCharPointDraw::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXidKey, oElement, m_strXid);
	xml_SetAttributeValue(pXmlKeys->m_strYidKey, oElement, m_strYid);
	return 0;
}

long CGbCharPointDraw::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXid);
		BinarySerializeCalLen(oBinaryBuffer, m_strYid);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXid);
		BinarySerializeRead(oBinaryBuffer, m_strYid);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXid);
		BinarySerializeWrite(oBinaryBuffer, m_strYid);
	}
	return 0;
}

BOOL CGbCharPointDraw::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharPointDraw *p = (CGbCharPointDraw*)pObj;

	if(m_strXid != p->m_strXid)
	{
		return FALSE;
	}

	if(m_strYid != p->m_strYid)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharPointDraw::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharPointDraw *p = (CGbCharPointDraw*)pDest;

	p->m_strXid = m_strXid;
	p->m_strYid = m_strYid;
	return TRUE;
}

CBaseObject* CGbCharPointDraw::Clone()
{
	CGbCharPointDraw *p = new CGbCharPointDraw();
	Copy(p);
	return p;
}

