#include "StdAfx.h"
#include "UIPageButton.h"

CUIPageButton::CUIPageButton(void)
{
}

CUIPageButton::~CUIPageButton(void)
{
}

long CUIPageButton::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strPara,oNode,m_strPara);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strOptr,oNode,m_nOptr);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strBmpFile,oNode,m_strBmpFile);
	return 0;
}

long CUIPageButton::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strPara,(_bstr_t)m_strPara);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strOptr,m_nOptr);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strBmpFile,(_bstr_t)m_strBmpFile);

	return 0;
}

long CUIPageButton::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}