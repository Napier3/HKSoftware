#include "StdAfx.h"
#include "UIPageButtons.h"
#include "UIPageButton.h"
#include "UICfgFont.h"

CUIPageButtons::CUIPageButtons(void)
{
}

CUIPageButtons::~CUIPageButtons(void)
{
	DeleteAll();
}

long CUIPageButtons::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CUIPageButtons::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CUIPageButtons::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CUIPageButtons::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strPageButton)
	{
		CUIPageButton* pObject = new CUIPageButton;
		return pObject;
	}
	else if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strFont)
	{
		CUICfgFont* pFont = new CUICfgFont;
		return pFont;
	}
	else
		return 0;
}

CExBaseObject* CUIPageButtons::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}
