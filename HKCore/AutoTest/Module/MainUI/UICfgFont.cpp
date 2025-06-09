#include "StdAfx.h"
#include "UICfgFont.h"

CUICfgFont::CUICfgFont(void)
{
}

CUICfgFont::~CUICfgFont(void)
{
}

long CUICfgFont::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strBkColor,oNode,m_strBkColor);
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strColor,oNode,m_strColor);
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strItalic,oNode,m_nitalic);
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strSize,oNode,m_nSize);
	xml_GetAttibuteValue(((CPMXmlRWKey*)pXmlRWKeys)->m_strBold,oNode,m_nBold);

	return 0;
}

long CUICfgFont::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strBkColor),_bstr_t(m_strBkColor));
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strColor),_bstr_t(m_strColor));
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strItalic),m_nitalic);
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strSize),m_nSize);
	oElement->setAttribute(_bstr_t(((CPMXmlRWKey*)pXmlRWKeys)->m_strBold),m_nBold);

	return 0;
}

long CUICfgFont::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	
	return 0;
}

CExBaseObject* CUICfgFont::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	return 0;
}

CExBaseObject* CUICfgFont::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}

UINT CUICfgFont::GetClassID()
{
	return UICFGFONTCLASSID;
}