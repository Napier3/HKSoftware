// XrioRioConverter.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioRioConverter.h"

// CXrioRioConverter

CXrioRioConverter::CXrioRioConverter()
{
//	m_strName = _T("RioConverter节点");
}

CXrioRioConverter::~CXrioRioConverter()
{
}

long CXrioRioConverter::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
//    xml_GetElementText(pXmlKeys->m_strScriptKey, oNode, m_strScript);


	return 0;
}

long CXrioRioConverter::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);
//    xml_SetElementText(pXmlKeys->m_strScriptKey, oXMLDoc, oElement, m_strScript);

	return 0;
}

long CXrioRioConverter::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CXrioRioConverter::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioRioConverter *p = (CXrioRioConverter*)pObj;

	return TRUE;
}

BOOL CXrioRioConverter::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioRioConverter *p = (CXrioRioConverter*)pDest;

	return TRUE;
}

CBaseObject* CXrioRioConverter::Clone()
{
	CXrioRioConverter *p = new CXrioRioConverter();
	Copy(p);
	return p;
}

BOOL CXrioRioConverter::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_RioConverter
	)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioRioConverter::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strScriptKey)
	{
        pNew = new CXrioScript();
	}

	return pNew;
}

CExBaseObject* CXrioRioConverter::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_Script)
	{
        pNew = new CXrioScript();
	}

	return pNew;
}




