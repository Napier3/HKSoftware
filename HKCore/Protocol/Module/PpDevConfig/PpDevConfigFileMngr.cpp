#include "stdafx.h"
#include "PpDevConfigFileMngr.h"
// #include "..\..\Module\FileMngr\FileMngrXMLKeys.h"

long CPpDevConfigFileMngr::g_nPpRefs = 0;
CPpDevConfigFileMngr* CPpDevConfigFileMngr::g_pPpDevConfigFileMngr = NULL;

CString GetPpDevConfigFile()
{
	CString strFileName;
	strFileName.Format(_T("%s%s"),(CString)_P_GetConfigPath(),g_strPpDevFileName);

	return strFileName;
}

CPpDevConfigFileMngr::CPpDevConfigFileMngr()
{
	m_strXmlns = _T("http://www.w3.org/2001/XMLSchema-instance");

	m_pDeviceModelFiles = NULL;
}

CPpDevConfigFileMngr* CPpDevConfigFileMngr::Create()
{
	g_nPpRefs ++;

	if(g_nPpRefs == 1)
	{
		g_pPpDevConfigFileMngr = new CPpDevConfigFileMngr();
	}

	return g_pPpDevConfigFileMngr;
}

void CPpDevConfigFileMngr::Release()
{
	g_nPpRefs --;

	if(g_nPpRefs == 0)
	{
		delete g_pPpDevConfigFileMngr;
		g_pPpDevConfigFileMngr = NULL;
	}
}

long CPpDevConfigFileMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CPpDevConfigFileMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CExBaseObject* CPpDevConfigFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	ASSERT(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys != NULL);

	if(strClassID == CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDeviceModelsKey)
	{
		m_pDeviceModelFiles = new CPpDevConfigDeviceModels();

		return m_pDeviceModelFiles;
	}

	return NULL;
}

BOOL CPpDevConfigFileMngr::SaveXmlFile(const CString& strFileName)
{
	return FALSE;
}

BOOL CPpDevConfigFileMngr::OpenXmlFile(const CString& strFileName)
{
	ASSERT(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys != NULL);
	
// 	MSXML2::IXMLDOMDocumentPtr oDoc;
// 
// 	if(::xml_OpenFile(oDoc,strFileName))
// 	{
// 		MSXML2::IXMLDOMNodePtr oDocRoot = oDoc->GetdocumentElement();
// 		MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(L"//"+(_bstr_t)CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strPpDevConfigKey);
// 
// 		ASSERT(oRoot != NULL);
// 		if(oRoot == NULL)
// 		{
// 			return FALSE;
// 		}
// 
// 		XmlRead(oRoot, CXFileMngrXMLKeys::g_pFileMngrXMLKeys);
// 		return TRUE;
// 	}


	return FALSE;
}