//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MessageImps.cpp  CMessageImps


#include "stdafx.h"
#include "MessageImps.h"

CMessageImps::CMessageImps()
{
	//初始化属性

	//初始化成员变量
}

CMessageImps::~CMessageImps()
{
}

long CMessageImps::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMessageImps::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMessageImps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMessageImps::InitAfterRead()
{
}

BOOL CMessageImps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMessageImps *p = (CMessageImps*)pObj;

	return TRUE;
}

BOOL CMessageImps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMessageImps *p = (CMessageImps*)pDest;

	return TRUE;
}

CBaseObject* CMessageImps::Clone()
{
	CMessageImps *p = new CMessageImps();
	Copy(p);
	return p;
}

BOOL CMessageImps::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CMESSAGEIMP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMessageImps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMessageImpKey)
	{
		pNew = new CMessageImp();
	}

	return pNew;
}

CExBaseObject* CMessageImps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CMESSAGEIMP)
	{
		pNew = new CMessageImp();
	}

	return pNew;
}
