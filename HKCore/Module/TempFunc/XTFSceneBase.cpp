
//XTFSceneBase.cpp  CXTFSceneBase


#include "stdafx.h"
#include "XTFSceneBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFSceneBase::CXTFSceneBase()
{
	//³õÊ¼»¯ÊôÐÔ
	
}

CXTFSceneBase::~CXTFSceneBase()
{
}

long CXTFSceneBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFSceneBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFSceneBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFSceneBase::InitAfterRead()
{
	
}

BOOL CXTFSceneBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFSceneBase *p = (CXTFSceneBase*)pObj;
	return TRUE;
}

BOOL CXTFSceneBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFSceneBase *p = (CXTFSceneBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFSceneBase::Clone()
{
	CXTFSceneBase *p = new CXTFSceneBase();
	Copy(p);
	return p;
}
BOOL CXTFSceneBase::CanPaste(UINT nClassID)
{
    if (nClassID == KTFCLASSID_CXSCENEBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXTFSceneBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXTempFuncsFolder)
	{
		pNew = new CXTFFolderBase();
	}
	
	else if (strClassID == pXmlKeys->m_strCXTempFuncsFunc)
	{
		pNew = new CXTFFuncBase();
	}
	return pNew;
}
