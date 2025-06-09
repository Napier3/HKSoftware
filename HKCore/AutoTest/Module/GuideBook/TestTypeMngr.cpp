#include "stdafx.h"
#include "TestTypeMngr.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestTypeMngr* CTestTypeMngr::g_pTestTypeXMLKeys = NULL;
CTestTypes* CTestTypeMngr::g_pTestTypes = NULL;
long CTestTypeMngr::g_nTestTypeXMLKeysRef = 0;

CTestTypes* CTestTypeMngr::Create()
{
	g_nTestTypeXMLKeysRef ++;

	if(g_nTestTypeXMLKeysRef == 1)
	{
// 		g_pTestTypeXMLKeys = new CTestTypeMngr();
		g_pTestTypes = new CTestTypes();
		
		g_pTestTypes->Open();
	}

	return g_pTestTypes;
}

void CTestTypeMngr::Release()
{
	g_nTestTypeXMLKeysRef -- ;

	if(g_nTestTypeXMLKeysRef == 0)
	{
// 		delete g_pTestTypeXMLKeys;
// 		g_pTestTypeXMLKeys = NULL;
		delete g_pTestTypes;
		g_pTestTypes = NULL;
	}
}

CTestTypeMngr::CTestTypeMngr()
{
	m_strTestTypesKey = L"TestTypes";
	m_strTestTypeKey = L"TestType";
}
// 
// long CTestType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
// 
// 	return 0;
// }
// 
// BSTR CTestType::GetXmlElementKey()
// {
// 	return CTestTypeMngr::g_pTestTypeXMLKeys->m_strTestTypeKey;
// }
// 
CTestTypes::CTestTypes()
{
	
}

CTestTypes::~CTestTypes()
{

}

long CTestTypes::Open()
{
	CString strFile;
    strFile = _P_GetConfigPath();
    strFile += g_strTestTypeXMLFile;

	BOOL b = OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	//xlang_TranslateByResourceFile(this, g_strTestTypeXMLFile);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(this, g_strTestTypeXMLFile);
#endif
    return b;
}

long CTestTypes::Open(const CString& strFile)
{
	BOOL b = OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CString strTemp = GetPathFileNameFromFilePathName(strFile);
	//xlang_TranslateByResourceFile(this, strTemp);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(this, strTemp);
#endif

	return b;
}

// 
// long CTestTypes::OpenXMLFile(const CString& strFile)
// {
// 	DeleteAll();
// 
// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));
// 
// 	_variant_t varXml(strFile);
// 	_variant_t varOut((bool)TRUE);
// 	varOut = docPtr->load(varXml);
// 
// 	if((BOOL)varOut == FALSE)
// 	{
// 		return FALSE;
// 	}
// 	
// 	MSXML2::IXMLDOMNodePtr oDocRoot = docPtr->GetdocumentElement();
// 	_bstr_t bstr = L"//";
// 	bstr +=  CTestTypeMngr::g_pTestTypeXMLKeys->m_strTestTypesKey;
// 
// 	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(bstr);
// 	ASSERT(oRoot != NULL);
// 
// 	if(oRoot == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	XmlRead(oRoot,CTestTypeMngr::g_pTestTypeXMLKeys);
// 
// 	return TRUE;
// }
