
//XTFKeysBase.cpp  CXTFKeysBase


#include "stdafx.h"
#include "XTFKeysBase.h"
#include "..\KeyDb\XKeyDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFKeysBase::CXTFKeysBase()
{
	//初始化属性
	
}

CXTFKeysBase::~CXTFKeysBase()
{
}

long CXTFKeysBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFKeysBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFKeysBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFKeysBase::InitAfterRead()
{
	//根据key，初始化m_oXkeyMatchRefList
	//遍历每一个CXTFKeyBase，调用
	CXKeyDB* pXKeyDB = CTempFuncXmlRWFuncs::GetXKeyDB();
	POS pos = GetHeadPosition();
	CXTFKeyBase *pXKey = NULL;

	while (pos != NULL)
	{
		pXKey = (CXTFKeyBase *)GetNext(pos);
		CXKeyMatchRef* pKey = pXKeyDB->CreateXKeyMatchRef(pXKey->m_strName, pXKey->m_nArray);

		if (pKey != NULL)
		{
			m_oXkeyMatchRefList.AddTail(pKey);
		}
	}
}

BOOL CXTFKeysBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFKeysBase *p = (CXTFKeysBase*)pObj;
	return TRUE;
}

BOOL CXTFKeysBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFKeysBase *p = (CXTFKeysBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFKeysBase::Clone()
{
	CXTFKeysBase *p = new CXTFKeysBase();
	Copy(p);
	return p;
}
BOOL CXTFKeysBase::CanPaste(UINT nClassID)
{
    if (nClassID == KTFCLASSID_CXKEYBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXTFKeysBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXTempFuncsKey)
	{
		pNew = new CXTFKeyBase();
	}
	return pNew;
}