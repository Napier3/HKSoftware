#include "StdAfx.h"
#include "PpPackageText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackageText::CPpPackageText(void)
{

}

CPpPackageText::~CPpPackageText(void)
{
	
}

long CPpPackageText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

// 	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  oNode->GetfirstChild();
// 
// 	if (oCDTA != NULL)
// 	{
// 		m_strText = (char*)oCDTA->Getxml();
// 		long nLen = m_strText.GetLength();
// 		m_strText = m_strText.Mid(9, nLen-12);
// 	}
// 	else
// 	{
// 		m_strText = (char*)oNode->Gettext();
// 		m_strText.Trim();
// 	}
	oNode.xml_GetCDATA(m_strText);

	if (m_strName.GetLength() < 2)
	{
		m_strName = m_strText.Left(40);
	}

	return 0;
}

long CPpPackageText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	try
	{
// 		MSXML2::IXMLDOMNodePtr oNode;
// 
// 		oNode = oXMLDoc->createCDATASection(L"");
// 		ASSERT( oNode != NULL);
// 		oElement->appendChild(oNode);
// 
// 		oNode->put_text((_bstr_t)m_strText);
		oElement.xml_SetCDATA(oXMLDoc, m_strText);
	} 
	catch(...)
	{

	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpPackageText::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpPackageText::Clone()
{
	CPpPackageText* pNew = new CPpPackageText();
	Copy(pNew);
	
	return pNew;
}

BOOL CPpPackageText::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}
	
	((CPpPackageText*)pDest)->m_strText = m_strText;

	return CExBaseObject::CopyOwn(pDest);
}

CPpPackageTexts::CPpPackageTexts()
{

}

CPpPackageTexts::~CPpPackageTexts()
{

}

CExBaseObject* CPpPackageTexts::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextKey)
	{
		return new CPpPackageText();
	}

	return NULL;
}

CExBaseObject* CPpPackageTexts::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

BOOL CPpPackageTexts::IsEqualOwn(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CPpPackageTexts::CopyOwn(CBaseObject* pDest)
{
	return TRUE;
}

CBaseObject* CPpPackageTexts::Clone()
{
	CPpPackageTexts *pNew = new CPpPackageTexts();
	Copy(pNew);
	return pNew;
}
