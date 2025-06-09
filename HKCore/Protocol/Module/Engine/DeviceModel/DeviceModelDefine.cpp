#include "stdafx.h"
#include"DeviceModelDefine.h"
#include "DeviceModelXmlKeys.h"
#include "..\..\..\..\Module\API\FileApi.h"

CPpDeviceModelDefine::CPpDeviceModelDefine()
{
	m_pDvTemplate=NULL;
	m_pDeviceModel=NULL;

	m_strName = "DeviceModelDefine";
	m_strID = m_strName;
}

CPpDeviceModelDefine::~CPpDeviceModelDefine()
{

}

void CPpDeviceModelDefine::Init()
{

}

void CPpDeviceModelDefine::InitAfterRead()
{
	
}

long CPpDeviceModelDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CPpDeviceModelDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

BOOL CPpDeviceModelDefine::IsEqualOwn(CBaseObject* pObj)
{
	return 0;
}

BOOL CPpDeviceModelDefine::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	return TRUE;
}

CExBaseObject* CPpDeviceModelDefine::Clone()
{
	CPpDeviceModelDefine *pNew = new CPpDeviceModelDefine();

	Copy(pNew);

	return pNew;
}

CExBaseObject* CPpDeviceModelDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject* CPpDeviceModelDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelTemplateKey)
	{
		m_pDvTemplate =  new CDeviceModelTemplate();
		return m_pDvTemplate;
	}

	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelKey)
	{
		m_pDeviceModel =  new CPpDeviceDefine();
		return m_pDeviceModel;
	}

	return NULL;
}

//打开文件
BOOL CPpDeviceModelDefine::OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys)
{
	_bstr_t bstr = L"//";
	bstr += CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelDefineKey;

	return CBaseObject::OpenXmlFile(strFile, NULL, CDeviceModelXmlKeys::g_pXmlRWKeys);
}

BOOL CPpDeviceModelDefine::SaveXmlFile(const CString &strFile)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,CDeviceModelXmlKeys::g_pXmlRWKeys);
	ClearFileReadOnlyAttr(strFile);
	BSTR strTemp = strFile.AllocSysString();
	docPtr->save(strTemp);
	::SysFreeString(strTemp);

	return TRUE;
}

