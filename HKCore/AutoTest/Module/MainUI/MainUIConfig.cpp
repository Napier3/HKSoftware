#include "StdAfx.h"
#include "MainUIConfig.h"

const WCHAR* strMainUIKey = L"PMMainUIKey";

CMainUIConfig::CMainUIConfig(void)
{
	m_pCurrentVersion = NULL;
}

CMainUIConfig::~CMainUIConfig(void)
{
	DeleteAll();
}
long CMainUIConfig::IsEqual(CExBaseObject* pObj)
{
	return 0;
}
long CMainUIConfig::Copy(CExBaseObject* pDesObj)
{
	return 0;
}
CExBaseList* CMainUIConfig::Clone(void)
{
	return NULL;
}
void CMainUIConfig::Init()
{

}
long CMainUIConfig::InitAfterSerialize()
{
	return 0;
}


void CMainUIConfig::OpenXMLFile(CString strFileName)
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
	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(L"//PMMainConfig");
	ATLASSERT(oRoot != NULL);
	if(oRoot == NULL)
	{
		AfxMessageBox(L"打开XML文件失败！");
	}

	XmlRead(oRoot,CPMXmlRWKey::g_pPMXmlRWKeys);
	SetCurrentVersion();
	//XMLRead(oRoot);
}

void CMainUIConfig::SetCurrentVersion()
{
	int nCount = GetCount();
	for (int i=0;i<nCount;i++)
	{
		CExBaseObject* pObject = GetAt(i);
		if (pObject->m_strID == m_strCurrVersion)
		{
			m_pCurrentVersion = (CVersion*)pObject;
			break;
		}
	}
	if (m_pCurrentVersion == NULL)
	{
		AfxMessageBox(L"没设置当前Version！");
	}
}

long CMainUIConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strActiveVersion,oNode,m_strCurrVersion);
	return 0;
}

long CMainUIConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strActiveVersion), _bstr_t(m_strName));
	return 0;
}

long CMainUIConfig::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	
	return 0;
}

CExBaseObject* CMainUIConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strVersion)
	{
		CVersion* pVersion = new CVersion;
		return pVersion;
	}
	else
		return NULL;
}

CExBaseObject* CMainUIConfig::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}

void CMainUIConfig::SaveXMLFile(CString strFileName)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,CPMXmlRWKey::g_pPMXmlRWKeys);
	docPtr->save((_bstr_t)strFileName);
}