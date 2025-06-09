
//XTFFuncBase.cpp  CXTFFuncBase


#include "stdafx.h"
#include "XTFFuncBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFFuncBase::CXTFFuncBase()
{
	//³õÊ¼»¯ÊôÐÔ
	m_pKeys = NULL;
	m_pTemplate = NULL;
}

CXTFFuncBase::~CXTFFuncBase()
{
}

long CXTFFuncBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFFuncBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFFuncBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFFuncBase::InitAfterRead()
{

}

BOOL CXTFFuncBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFFuncBase *p = (CXTFFuncBase*)pObj;
	return TRUE;
}

BOOL CXTFFuncBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFFuncBase *p = (CXTFFuncBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFFuncBase::Clone()
{
	CXTFFuncBase *p = new CXTFFuncBase();
	Copy(p);
	return p;
}
BOOL CXTFFuncBase::CanPaste(UINT nClassID)
{
	if (nClassID == KTFCLASSID_CXTEMPBASE)
	{
		return TRUE;
	}

	else if (nClassID == KTFCLASSID_CXKEYBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXTFFuncBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXTempFuncsKeys)
	{
		m_pKeys = new CXTFKeysBase();
		pNew = m_pKeys;
	}

	else if (strClassID == pXmlKeys->m_strCXTempFuncsTemp)
	{
		m_pTemplate = new CXTFTempBase();
		pNew = m_pTemplate;
	}

	return pNew;
}

BOOL CXTFFuncBase::XMatch(CXKeyMatchRefList *pXkeyMatchRefList)
{
	ASSERT (m_pKeys != NULL);

	if (m_pKeys == NULL)
	{
		return FALSE;
	}

	long nRatio = 0;
	return m_pKeys->m_oXkeyMatchRefList.Match(pXkeyMatchRefList, nRatio);
}


long CXTFFuncBase::QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate)
{
	if (XMatch(pKeysList))
	{
		listTemplate.AddTail(this);
		return 1;
	}
	else
	{
		return 0;
	}
}

