//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLineDraw.cpp  CGbCharLineDraw


#include "stdafx.h"
#include "GbCharLineDraw.h"

CGbCharLineDraw::CGbCharLineDraw()
{
	//初始化属性

	//初始化成员变量
}

CGbCharLineDraw::~CGbCharLineDraw()
{
}

long CGbCharLineDraw::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbidKey, oNode, m_strXbid);
	xml_GetAttibuteValue(pXmlKeys->m_strYbidKey, oNode, m_strYbid);
	xml_GetAttibuteValue(pXmlKeys->m_strXeidKey, oNode, m_strXeid);
	xml_GetAttibuteValue(pXmlKeys->m_strYeidKey, oNode, m_strYeid);
	return 0;
}

long CGbCharLineDraw::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbidKey, oElement, m_strXbid);
	xml_SetAttributeValue(pXmlKeys->m_strYbidKey, oElement, m_strYbid);
	xml_SetAttributeValue(pXmlKeys->m_strXeidKey, oElement, m_strXeid);
	xml_SetAttributeValue(pXmlKeys->m_strYeidKey, oElement, m_strYeid);
	return 0;
}

long CGbCharLineDraw::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXbid);
		BinarySerializeCalLen(oBinaryBuffer, m_strYbid);
		BinarySerializeCalLen(oBinaryBuffer, m_strXeid);
		BinarySerializeCalLen(oBinaryBuffer, m_strYeid);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXbid);
		BinarySerializeRead(oBinaryBuffer, m_strYbid);
		BinarySerializeRead(oBinaryBuffer, m_strXeid);
		BinarySerializeRead(oBinaryBuffer, m_strYeid);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXbid);
		BinarySerializeWrite(oBinaryBuffer, m_strYbid);
		BinarySerializeWrite(oBinaryBuffer, m_strXeid);
		BinarySerializeWrite(oBinaryBuffer, m_strYeid);
	}
	return 0;
}

BOOL CGbCharLineDraw::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharLineDraw *p = (CGbCharLineDraw*)pObj;

	if(m_strXbid != p->m_strXbid)
	{
		return FALSE;
	}

	if(m_strYbid != p->m_strYbid)
	{
		return FALSE;
	}

	if(m_strXeid != p->m_strXeid)
	{
		return FALSE;
	}

	if(m_strYeid != p->m_strYeid)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharLineDraw::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLineDraw *p = (CGbCharLineDraw*)pDest;

	p->m_strXbid = m_strXbid;
	p->m_strYbid = m_strYbid;
	p->m_strXeid = m_strXeid;
	p->m_strYeid = m_strYeid;
	return TRUE;
}

CBaseObject* CGbCharLineDraw::Clone()
{
	CGbCharLineDraw *p = new CGbCharLineDraw();
	Copy(p);
	return p;
}

