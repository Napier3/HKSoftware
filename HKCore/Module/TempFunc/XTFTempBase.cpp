
//XTFTempBase.cpp  CXTFTempBase


#include "stdafx.h"
#include "XTFTempBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CXTFTempBase::CXTFTempBase()
{
	//≥ı ºªØ Ù–‘
}

CXTFTempBase::~CXTFTempBase()
{
}

long CXTFTempBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFTempBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;
	return 0;
}

long CXTFTempBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXTFTempBase::InitAfterRead()
{
}

BOOL CXTFTempBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTFTempBase *p = (CXTFTempBase*)pObj;
	return TRUE;
}

BOOL CXTFTempBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	CXTFTempBase *p = (CXTFTempBase*)pDest;

	return TRUE;
}

CBaseObject* CXTFTempBase::Clone()
{
	CXTFTempBase *p = new CXTFTempBase();
	Copy(p);
	return p;
}
BOOL CXTFTempBase::CanPaste(UINT nClassID)
{

	if (nClassID == KTFCLASSID_CXTEMPBASE)
	{
		return TRUE;
	}

	return FALSE;
}