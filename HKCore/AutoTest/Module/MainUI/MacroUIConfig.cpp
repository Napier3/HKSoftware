#include "StdAfx.h"
#include "MacroUIConfig.h"
#include "UIPage.h"


CMacroUIConfig::CMacroUIConfig(void)
{
}

CMacroUIConfig::~CMacroUIConfig(void)
{
	DeleteAll();
}

void CMacroUIConfig::OpenXMLFile(CString strFileName)
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
	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(m_PMXmlRWKey.m_strMacroUIConfig);
	ATLASSERT(oRoot != NULL);
	if(oRoot == NULL)
	{
		AfxMessageBox(L"打开XML文件失败！");
	}

	//XMLRead(oRoot);
	XmlRead(oRoot,&m_PMXmlRWKey);
}

long CMacroUIConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	//xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strConfigFile,oNode,m_strConfigFile);
	return 0;
}

long CMacroUIConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	//oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strConfigFile), _bstr_t(m_strConfigFile));
	return 0;
}

long CMacroUIConfig::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CMacroUIConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == m_PMXmlRWKey.m_strPage)
	{
		CUIPage* pUIPage = new CUIPage;
		return pUIPage;
	}
	else
		return 0;
}

CExBaseObject* CMacroUIConfig::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}
BOOL CMacroUIConfig::WriteToFile(CString strFileName)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,&m_PMXmlRWKey);
	docPtr->save((_bstr_t)strFileName);

	return TRUE;
}