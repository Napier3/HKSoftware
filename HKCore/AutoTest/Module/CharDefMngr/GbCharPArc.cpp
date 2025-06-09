//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharPArc.cpp  CGbCharPArc


#include "stdafx.h"
#include "GbCharPArc.h"

CGbCharPArc::CGbCharPArc()
{
	//初始化属性

	//初始化成员变量
}

CGbCharPArc::~CGbCharPArc()
{
}

long CGbCharPArc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharArc::XmlReadOwn(oNode, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPArc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharArc::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPArc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbCharArc::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

BOOL CGbCharPArc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbCharArc::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbCharPArc *p = (CGbCharPArc*)pObj;

	return TRUE;
}

BOOL CGbCharPArc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharArc::CopyOwn(pDest);

	CGbCharPArc *p = (CGbCharPArc*)pDest;

	return TRUE;
}

CBaseObject* CGbCharPArc::Clone()
{
	CGbCharPArc *p = new CGbCharPArc();
	Copy(p);
	return p;
}

