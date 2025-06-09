//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EcdmProtocolAddrs.cpp  CEcdmProtocolAddrs


#include "stdafx.h"
#include "EcdmProtocolAddrs.h"

CEcdmProtocolAddrs::CEcdmProtocolAddrs()
{
	//初始化属性

	//初始化成员变量
}

CEcdmProtocolAddrs::~CEcdmProtocolAddrs()
{
}

long CEcdmProtocolAddrs::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEcdmProtocolAddrs::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CEcdmProtocolAddrs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEcdmProtocolAddrs *p = (CEcdmProtocolAddrs*)pObj;

	return TRUE;
}

BOOL CEcdmProtocolAddrs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEcdmProtocolAddrs *p = (CEcdmProtocolAddrs*)pDest;

	return TRUE;
}

CBaseObject* CEcdmProtocolAddrs::Clone()
{
	CEcdmProtocolAddrs *p = new CEcdmProtocolAddrs();
	Copy(p);
	return p;
}

BOOL CEcdmProtocolAddrs::CanPaste(UINT nClassID)
{
	if (nClassID == ECDMCLASSID_CECDMPROTOCOLADDR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEcdmProtocolAddrs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEcdmProtocolAddrKey)
	{
		pNew = new CEcdmProtocolAddr();
	}

	return pNew;
}

CExBaseObject* CEcdmProtocolAddrs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECDMCLASSID_CECDMPROTOCOLADDR)
	{
		pNew = new CEcdmProtocolAddr();
	}

	return pNew;
}
