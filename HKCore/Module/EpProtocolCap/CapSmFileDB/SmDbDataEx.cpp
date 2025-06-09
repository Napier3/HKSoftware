//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbDataEx.cpp  CSmDbDataEx


#include "stdafx.h"
#include "SmDbDataEx.h"

CSmDbDataEx::CSmDbDataEx()
{
	//初始化属性

	//初始化成员变量
}

CSmDbDataEx::~CSmDbDataEx()
{
}

long CSmDbDataEx::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSmDbData::XmlReadOwn(oNode, pXmlRWKeys);
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbDataEx::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSmDbData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbDataEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSmDbData::SerializeOwn(oBinaryBuffer);
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

void CSmDbDataEx::InitAfterRead()
{
}

BOOL CSmDbDataEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSmDbData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSmDbDataEx *p = (CSmDbDataEx*)pObj;

	return TRUE;
}

BOOL CSmDbDataEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbData::CopyOwn(pDest);

	CSmDbDataEx *p = (CSmDbDataEx*)pDest;

	return TRUE;
}

CBaseObject* CSmDbDataEx::Clone()
{
	CSmDbDataEx *p = new CSmDbDataEx();
	Copy(p);
	return p;
}

