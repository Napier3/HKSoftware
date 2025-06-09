#include "StdAfx.h"
#include "DataInterface.h"

CDataInterface::CDataInterface(void)
{
}

CDataInterface::~CDataInterface(void)
{
}

long CDataInterface::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strProcessDataInterfaceVarID, oNode, m_ProID);
	xml_GetAttibuteValue(pKeys->m_strProcessDataInterfacePkgID, oNode, m_PkID);

	return 0;
}

long CDataInterface::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strProcessDataInterfaceVarID, oElement, m_ProID);
	xml_SetAttributeValue(pKeys->m_strProcessDataInterfacePkgID,oElement,m_PkID);

	return 0;
}