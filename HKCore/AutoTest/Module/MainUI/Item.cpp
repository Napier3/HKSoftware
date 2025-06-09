#include "StdAfx.h"
#include "Item.h"


CItem::CItem(void)
{
}

CItem::~CItem(void)
{
}

long CItem::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strFile,oNode,m_strFile);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strProgram,oNode,m_strProgram);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strShow,oNode,m_nShow);
	return 0;
}

long CItem::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strFile,(_bstr_t)m_strFile);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strProgram,(_bstr_t)m_strProgram);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strShow,m_nShow);

	return 0;
}

long CItem::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}