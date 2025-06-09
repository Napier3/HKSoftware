#include "StdAfx.h"
#include "UIGroup.h"
#include "Item.h"
#include "UICfgFont.h"

CUIGroup::CUIGroup(void)
{
}

CUIGroup::~CUIGroup(void)
{
	DeleteAll();
}

long CUIGroup::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CUIGroup::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CUIGroup::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CUIGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strItem)
	{
		CItem* pItem = new CItem;
		return pItem;
	}
	else if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strFont)
	{
		CUICfgFont* pFont = new CUICfgFont;
		return pFont;
	}
	else
		return NULL;

}

CExBaseObject* CUIGroup::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}

