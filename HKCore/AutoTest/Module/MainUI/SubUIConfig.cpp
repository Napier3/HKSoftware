#include "StdAfx.h"
#include "SubUIConfig.h"
#include "UIPage.h"


CSubUIConfig::CSubUIConfig(void)
{
}

CSubUIConfig::~CSubUIConfig(void)
{
	DeleteAll();
}

void CSubUIConfig::OpenXMLFile(CString strFileName)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	if (FAILED(docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument))))
	{
		HRESULT hr = GetLastError();
	}

	_variant_t varXml(strFileName);
	_variant_t varOut((bool)TRUE);
	varOut = docPtr->load(varXml);
	ATLASSERT((BOOL)varOut != FALSE);
	if((BOOL)varOut == FALSE)
	{
		AfxMessageBox(L"打开XML文件失败！");
	}

	MSXML2::IXMLDOMNodePtr oDocRoot = docPtr->GetdocumentElement();
	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode("//SubUIConfig");
	ATLASSERT(oRoot != NULL);
	if(oRoot == NULL)
	{
		AfxMessageBox(L"打开XML文件失败！");
	}

	XmlRead(oRoot,CPMXmlRWKey::g_pPMXmlRWKeys);
}

long CSubUIConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CSubUIConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CSubUIConfig::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CSubUIConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strPage)
	{
		CUIPage* pUIPage = new CUIPage;
		return pUIPage;
	}
	else
		return 0;
}

CExBaseObject* CSubUIConfig::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}
BOOL CSubUIConfig::WriteToFile(CString strFileName)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,CPMXmlRWKey::g_pPMXmlRWKeys);
	docPtr->save((_bstr_t)strFileName);

	return TRUE;
}