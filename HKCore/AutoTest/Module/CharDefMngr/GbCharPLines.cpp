//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharPLines.cpp  CGbCharPLines


#include "stdafx.h"
#include "GbCharPLines.h"

CGbCharPLines::CGbCharPLines()
{
	//初始化属性

	//初始化成员变量
}

CGbCharPLines::~CGbCharPLines()
{
}

long CGbCharPLines::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLines::XmlReadOwn(oNode, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLines::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLines::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLines::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbCharLines::SerializeOwn(oBinaryBuffer);
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

BOOL CGbCharPLines::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbCharLines::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbCharPLines *p = (CGbCharPLines*)pObj;

	return TRUE;
}

BOOL CGbCharPLines::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLines::CopyOwn(pDest);

	CGbCharPLines *p = (CGbCharPLines*)pDest;

	return TRUE;
}

CBaseObject* CGbCharPLines::Clone()
{
	CGbCharPLines *p = new CGbCharPLines();
	Copy(p);
	return p;
}

