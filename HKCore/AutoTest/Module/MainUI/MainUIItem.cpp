#include "StdAfx.h"
#include "MainUIItem.h"

CMainUIItem::CMainUIItem(void)
{
}

CMainUIItem::~CMainUIItem(void)
{
}

long CMainUIItem::IsEqual(CExBaseObject* pObj)
{
	return 0;
}
long CMainUIItem::Copy(CExBaseObject* pDesObj)
{
	return 0;
}
CExBaseObject* CMainUIItem::Clone()
{
	return NULL;
}

void CMainUIItem::Init()
{
	
}

long CMainUIItem::InitAfterSerialize()
{
	return 0;
}


long CMainUIItem::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strConfigFile,oNode,m_strConfigFile);

	return 0;
}

long CMainUIItem::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strConfigFile, _bstr_t(m_strConfigFile));

	return 0;
}

long CMainUIItem::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}
