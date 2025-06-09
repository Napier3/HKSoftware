//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLiner.cpp  CGbCharLiner


#include "stdafx.h"
#include "GbCharLiner.h"

CGbCharLiner::CGbCharLiner()
{
	//初始化属性

	//初始化成员变量
}

CGbCharLiner::~CGbCharLiner()
{
}

long CGbCharLiner::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CGbCharLiner::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

long CGbCharLiner::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXb);
		BinarySerializeRead(oBinaryBuffer, m_strYb);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXb);
		BinarySerializeWrite(oBinaryBuffer, m_strYb);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strDir);
	}
	return 0;
}

BOOL CGbCharLiner::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharLiner *p = (CGbCharLiner*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharLiner::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLiner *p = (CGbCharLiner*)pDest;

	p->m_strXb = m_strXb;
	p->m_strYb = m_strYb;
	p->m_strAngle = m_strAngle;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CGbCharLiner::Clone()
{
	CGbCharLiner *p = new CGbCharLiner();
	Copy(p);
	return p;
}

