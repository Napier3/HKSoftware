//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharArc.cpp  CGbCharArc


#include "stdafx.h"
#include "GbCharArc.h"

CGbCharArc::CGbCharArc()
{
	//初始化属性

	//初始化成员变量
}

CGbCharArc::~CGbCharArc()
{
}

long CGbCharArc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXcKey, oNode, m_strXc);
	xml_GetAttibuteValue(pXmlKeys->m_strYcKey, oNode, m_strYc);
	xml_GetAttibuteValue(pXmlKeys->m_strRKey, oNode, m_strR);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleBKey, oNode, m_strAngleB);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleEKey, oNode, m_strAngleE);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CGbCharArc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXcKey, oElement, m_strXc);
	xml_SetAttributeValue(pXmlKeys->m_strYcKey, oElement, m_strYc);
	xml_SetAttributeValue(pXmlKeys->m_strRKey, oElement, m_strR);
	xml_SetAttributeValue(pXmlKeys->m_strAngleBKey, oElement, m_strAngleB);
	xml_SetAttributeValue(pXmlKeys->m_strAngleEKey, oElement, m_strAngleE);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

long CGbCharArc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXc);
		BinarySerializeCalLen(oBinaryBuffer, m_strYc);
		BinarySerializeCalLen(oBinaryBuffer, m_strR);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngleB);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngleE);
		BinarySerializeCalLen(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXc);
		BinarySerializeRead(oBinaryBuffer, m_strYc);
		BinarySerializeRead(oBinaryBuffer, m_strR);
		BinarySerializeRead(oBinaryBuffer, m_strAngleB);
		BinarySerializeRead(oBinaryBuffer, m_strAngleE);
		BinarySerializeRead(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXc);
		BinarySerializeWrite(oBinaryBuffer, m_strYc);
		BinarySerializeWrite(oBinaryBuffer, m_strR);
		BinarySerializeWrite(oBinaryBuffer, m_strAngleB);
		BinarySerializeWrite(oBinaryBuffer, m_strAngleE);
		BinarySerializeWrite(oBinaryBuffer, m_strDir);
	}
	return 0;
}

BOOL CGbCharArc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharArc *p = (CGbCharArc*)pObj;

	if(m_strXc != p->m_strXc)
	{
		return FALSE;
	}

	if(m_strYc != p->m_strYc)
	{
		return FALSE;
	}

	if(m_strR != p->m_strR)
	{
		return FALSE;
	}

	if(m_strAngleB != p->m_strAngleB)
	{
		return FALSE;
	}

	if(m_strAngleE != p->m_strAngleE)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharArc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharArc *p = (CGbCharArc*)pDest;

	p->m_strXc = m_strXc;
	p->m_strYc = m_strYc;
	p->m_strR = m_strR;
	p->m_strAngleB = m_strAngleB;
	p->m_strAngleE = m_strAngleE;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CGbCharArc::Clone()
{
	CGbCharArc *p = new CGbCharArc();
	Copy(p);
	return p;
}

