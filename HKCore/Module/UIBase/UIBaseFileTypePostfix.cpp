//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseFileTypePostfix.cpp  CUIBaseFileTypePostfix


#include "stdafx.h"
#include "UIBaseFileTypePostfix.h"

CUIBaseFileTypePostfix::CUIBaseFileTypePostfix()
{
	//初始化属性

	//初始化成员变量
}

CUIBaseFileTypePostfix::~CUIBaseFileTypePostfix()
{
}

long CUIBaseFileTypePostfix::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIBaseFileTypePostfix::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIBaseFileTypePostfix::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CUIBaseFileTypePostfix::InitAfterRead()
{
}

BOOL CUIBaseFileTypePostfix::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIBaseFileTypePostfix *p = (CUIBaseFileTypePostfix*)pObj;

	return TRUE;
}

BOOL CUIBaseFileTypePostfix::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUIBaseFileTypePostfix *p = (CUIBaseFileTypePostfix*)pDest;

	return TRUE;
}

CBaseObject* CUIBaseFileTypePostfix::Clone()
{
	CUIBaseFileTypePostfix *p = new CUIBaseFileTypePostfix();
	Copy(p);
	return p;
}

