#include "StdAfx.h"
#include "DeviceTypeRoot.h"
#include "DeviceTypePath.h"
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceTypeRoot::CDeviceTypeRoot(void)
{
}

CDeviceTypeRoot::~CDeviceTypeRoot(void)
{
}

long CDeviceTypeRoot::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CDeviceTypeRoot::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElemen,pXmlRWKeys);

	return 0;

}

CExBaseObject* CDeviceTypeRoot::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

CExBaseObject* CDeviceTypeRoot::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if(strClassID==CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strPath) 	
	{
		return new CDeviceTypePath();
	}
	else if(strClassID==CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strDevice)
	{
		return new CDeviceType();
	}

	return NULL;
}


BOOL CDeviceTypeRoot::OpenXMLFile()
{
	CString strFileName;
	strFileName = _P_GetConfigPath();
	strFileName += _T("\\DeviceTypeConfig.xml");
// 	xml_OpenFile(docPtr,strFileName);
//
// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	_variant_t varXml(strFileName);
// 	_variant_t varOut((bool)TRUE);
// 	varOut = docPtr->load(varXml);
// 	ATLASSERT((BOOL)varOut != FALSE);
// 	if((BOOL)varOut == FALSE)
// 	{
// 		AfxMessageBox(g_sLangTxt_OpenXMLFail/*_T("打开XML文件失败！")*/);
// 		return FALSE;
// 	}
// 
// 	MSXML2::IXMLDOMNodePtr oDocRoot = docPtr->GetdocumentElement();
// 	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(_T("//devicetyperoot"));
// 	ATLASSERT(oRoot != NULL);
// 	if(oRoot == NULL)
// 	{
// 		AfxMessageBox(g_sLangTxt_OpenXMLFail/*_T("打开XML文件失败！")*/);
// 	}
// 
// 	XmlRead(oRoot,CDeviceTypePathXmlKeys::g_pXmlRWKeys);

	return CBaseObject::OpenXmlFile(strFileName, CDeviceTypePathXmlKeys::g_pXmlRWKeys);
}

BOOL CDeviceTypeRoot::SaveXMLFile()
{
// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	HRESULT hr = docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));
// 
// 	if(!SUCCEEDED(hr)) 
// 	{ 
// 		AfxMessageBox(g_sLangTxt_SaveSetFileFail/*L"保存通讯配置文件失败！"*/);
// 		return FALSE;
// 	} 
// 
// 	CString strFileName;
// 	strFileName = _P_GetConfigPath();
// 	strFileName +=L"\\Commconfig.xml";
// 
// 	//CString strFile = L"D:\\Program Files\\PONOVO\\PMC2000\\Config\\Commconfig.xml";
// 	XmlWrite(docPtr,NULL,CDeviceTypePathXmlKeys::g_pXmlRWKeys);
// 	BSTR strTemp = strFileName.AllocSysString();
// 	ClearFileReadOnlyAttr(strFileName);
// 	docPtr->save(strTemp);
// 	::SysFreeString(strTemp);


	CString strFileName;
	strFileName = _P_GetConfigPath();
    strFileName += _T("/Commconfig.xml");

	return CBaseObject::SaveXmlFile(strFileName, CDeviceTypePathXmlKeys::g_pXmlRWKeys);
}
