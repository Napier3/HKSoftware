
//XTFKeyBase.cpp  CXTFKeyBase


#include "stdafx.h"
#include "XTFKeyBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFKeyBase::CXTFKeyBase()
{
	//³õÊ¼»¯ÊôÐÔ
	m_nArray = -1;
}

CXTFKeyBase::~CXTFKeyBase()
{
}

long CXTFKeyBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strCXTempFuncsArray, oNode, m_nArray);
	return 0;
}

long CXTFKeyBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strCXTempFuncsArray, oElement, m_nArray);
	return 0;
}

long CXTFKeyBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFKeyBase::InitAfterRead()
{
}

BOOL CXTFKeyBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFKeyBase *p = (CXTFKeyBase*)pObj;
	return TRUE;
}

BOOL CXTFKeyBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFKeyBase *p = (CXTFKeyBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFKeyBase::Clone()
{
	CXTFKeyBase *p = new CXTFKeyBase();
	Copy(p);
	return p;
}
BOOL CXTFKeyBase::CanPaste(UINT nClassID)
{

	if (nClassID == KTFCLASSID_CXKEYBASE)
	{
		return TRUE;
	}

	return FALSE;
}