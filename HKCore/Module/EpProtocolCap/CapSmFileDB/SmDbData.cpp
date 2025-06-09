//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbData.cpp  CSmDbData


#include "stdafx.h"
#include "SmDbData.h"

CSmDbData::CSmDbData()
{
	//初始化属性

	//初始化成员变量
}

CSmDbData::~CSmDbData()
{
}

long CSmDbData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CSmDbData::InitAfterRead()
{
}

BOOL CSmDbData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbData *p = (CSmDbData*)pObj;

	return TRUE;
}

BOOL CSmDbData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbData *p = (CSmDbData*)pDest;

	return TRUE;
}

CBaseObject* CSmDbData::Clone()
{
	CSmDbData *p = new CSmDbData();
	Copy(p);
	return p;
}

