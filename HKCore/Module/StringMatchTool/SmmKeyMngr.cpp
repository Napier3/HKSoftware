//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmKeyMngr.cpp  CSmmKeyMngr


#include "stdafx.h"
#include "SmmKeyMngr.h"

CSmmKeyMngr::CSmmKeyMngr()
{
	//初始化属性

	//初始化成员变量
}

CSmmKeyMngr::~CSmmKeyMngr()
{
}

long CSmmKeyMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmmKeyMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmmKeyMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmmKeyMngr::InitAfterRead()
{
}

BOOL CSmmKeyMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmKeyMngr *p = (CSmmKeyMngr*)pObj;

	return TRUE;
}

BOOL CSmmKeyMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmKeyMngr *p = (CSmmKeyMngr*)pDest;

	return TRUE;
}

CBaseObject* CSmmKeyMngr::Clone()
{
	CSmmKeyMngr *p = new CSmmKeyMngr();
	Copy(p);
	return p;
}

BOOL CSmmKeyMngr::CanPaste(UINT nClassID)
{
	if (nClassID == SMMCLASSID_CSMMGROUPKEY)
	{
		return TRUE;
	}

	if (nClassID == SMMCLASSID_CSMMMULTIKEY)
	{
		return TRUE;
	}

	if (nClassID == SMMCLASSID_CSMMKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmmKeyMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmmGroupKeyKey)
	{
		pNew = new CSmmGroupKey();
	}
	else if (strClassID == pXmlKeys->m_strCSmmMultiKeyKey)
	{
		pNew = new CSmmMultiKey();
	}
	else if (strClassID == pXmlKeys->m_strCSmmKeyKey)
	{
		pNew = new CSmmKey();
	}
	else if (strClassID == pXmlKeys->m_strCSmmGroupKeysKey)
	{
		pNew = new CSmmGroupKeys();
	}

	return pNew;
}

CExBaseObject* CSmmKeyMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SMMCLASSID_CSMMGROUPKEY)
	{
		pNew = new CSmmGroupKey();
	}
	else if (nClassID == SMMCLASSID_CSMMMULTIKEY)
	{
		pNew = new CSmmMultiKey();
	}
	else if (nClassID == SMMCLASSID_CSMMKEY)
	{
		pNew = new CSmmKey();
	}
	else if (nClassID == SMMCLASSID_CSMMGROUPKEYS)
	{
		pNew = new CSmmGroupKeys();
	}

	return pNew;
}
