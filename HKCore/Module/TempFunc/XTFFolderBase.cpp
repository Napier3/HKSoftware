
//XTFFolderBase.cpp  CXTFFolderBase


#include "stdafx.h"
#include "XTFFolderBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFFolderBase::CXTFFolderBase()
{
	//初始化属性
	
}

CXTFFolderBase::~CXTFFolderBase()
{
}

long CXTFFolderBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFFolderBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFFolderBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFFolderBase::InitAfterRead()
{
	
}

BOOL CXTFFolderBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFFolderBase *p = (CXTFFolderBase*)pObj;
	return TRUE;
}

BOOL CXTFFolderBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFFolderBase *p = (CXTFFolderBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFFolderBase::Clone()
{
	CXTFFolderBase *p = new CXTFFolderBase();
	Copy(p);
	return p;
}
BOOL CXTFFolderBase::CanPaste(UINT nClassID)
{
    if (nClassID == KTFCLASSID_CXFOLDERBASE)
	{
		return TRUE;
	}

	else if (nClassID == KTFCLASSID_CXFUNCBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXTFFolderBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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


long CXTFFolderBase::QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate)
{
	POS pos = GetHeadPosition();    //第一级，Templates-Functions
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == KTFCLASSID_CXFOLDERBASE)
		{
			nCount += ((CXTFFolderBase*)p)->QueryByKeys(pKeysList, listTemplate);
		}
		else if (nClassID == KTFCLASSID_CXFUNCBASE)
		{
			nCount += ((CXTFFuncBase*)p)->QueryByKeys(pKeysList, listTemplate);
		}
	}

	return nCount;
}

