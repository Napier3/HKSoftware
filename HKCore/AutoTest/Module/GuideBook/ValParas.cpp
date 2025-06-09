#include "stdafx.h"
#include "ValParas.h"

CValParas::CValParas()
{
	m_pValues = new CValues();
	ASSERT(m_pValues != NULL);
}

CValParas::~CValParas()
{
	delete m_pValues;
	m_pValues = NULL;
}

long CValParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		m_pValues->Serialize(oBinaryBuffer);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		m_pValues->DeleteAll();
		m_pValues->Serialize(oBinaryBuffer);
	}
	else
	{
		m_pValues->Serialize(oBinaryBuffer);
	}

	return 0;
}

long CValParas::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	MSXML2::IXMLDOMNodeListPtr oNodes = oNode->GetchildNodes();
	long nCount = oNodes->Getlength();

	if(nCount != 0)
	{
// 		SystemTool::IValueXMLRWKeysPtr valueKeys;
// 		valueKeys.CreateInstance(__uuidof(SystemTool::ValueXMLRWKeys));
		m_pValues->DeleteAll();
		m_pValues->XmlRead(oNode,CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);
	}

	return 0;
}

long CValParas::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

// 	SystemTool::IValueXMLRWKeysPtr valueKeys;
// 	valueKeys.CreateInstance(__uuidof(SystemTool::ValueXMLRWKeys));
//	valueKeys->put_DocPtr(oXMLDoc);
	m_pValues->XmlWrite(oXMLDoc, oElement,CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);

	return 0;
}

BSTR CValParas::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strParasKey;
}

BOOL CValParas::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CValParas::CopyOwn(CBaseObject *pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDesObj);

	CValParas* pValParas = (CValParas*)pDesObj;

	if(pValParas->m_pValues != NULL)
	{
		delete pValParas->m_pValues;
		pValParas->m_pValues = NULL;
	}

	pValParas->m_pValues = (CValues*)m_pValues->Clone();

	return TRUE;
}

CBaseObject* CValParas::Clone()
{
	CValParas* pValParas = new CValParas();
	Copy(pValParas);

	return pValParas;
}

CValues* CValParas::GetValues()
{	
	return m_pValues;		
}