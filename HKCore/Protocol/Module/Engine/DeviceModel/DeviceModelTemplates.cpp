#include "stdafx.h"
#include"DeviceModelTemplates.h"

CDeviceModelTemplates::CDeviceModelTemplates()
{
	m_strName = "DeviceModelTemplates";
	m_strID = m_strName;

}

CDeviceModelTemplates::~CDeviceModelTemplates()
{

}

void CDeviceModelTemplates::Init()
{

}

void CDeviceModelTemplates::InitAfterRead()
{

}

long CDeviceModelTemplates::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	//xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strRemark,oNode,m_strRemark);

	return 0;
}

long CDeviceModelTemplates::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	//xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strRemark,oXMLDoc,m_strRemark);

	return 0;

}

BOOL CDeviceModelTemplates::IsEqualOwn(CExBaseObject* pObj)
{
	return 0;
}

BOOL CDeviceModelTemplates::CopyOwn(CExBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CopyOwn(pDesObj);


	return 0;
}

CExBaseObject* CDeviceModelTemplates::Clone()
{
	CDeviceModelTemplates *pNew = new CDeviceModelTemplates();

	Copy(pNew);

	return pNew;
}

CExBaseObject*  CDeviceModelTemplates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject*  CDeviceModelTemplates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelTemplateKey)
	{
		return new CDeviceModelTemplate();
	}

	return NULL;
}
