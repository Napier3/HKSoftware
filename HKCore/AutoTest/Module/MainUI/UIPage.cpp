#include "StdAfx.h"
#include "UIPage.h"
#include "UIGroups.h"
#include "UIPageButtons.h"
#include "UICfgFont.h"

CUIPage::CUIPage(void)
{
}

CUIPage::~CUIPage(void)
{
	DeleteAll();
}

long CUIPage::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CPMXmlRWKey::g_pPMXmlRWKeys->m_strBtnWidth,oNode,m_nbtnWidth);
	return 0;
}

long CUIPage::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CPMXmlRWKey::g_pPMXmlRWKeys->m_strBtnWidth,m_nbtnWidth);
	return 0;
}

long CUIPage::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CUIPage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strGroups)
	{
		CUIGroups* pUIGroups = new CUIGroups;
		return pUIGroups;
	}
	else if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strPageButtons)
	{
		CUIPageButtons* pUIPageButtons = new CUIPageButtons;
		return pUIPageButtons;
	}
	else if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strFont)
	{
		CUICfgFont* pFont = new CUICfgFont;
		return pFont;
	}
	else
		return 0;
}

CExBaseObject* CUIPage::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}


CExBaseObject* CUIPage::GetGroups()
{
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject* pObj = GetNext(pos);
		LONG nClassID = pObj->GetClassID();
		if (nClassID == UIGROUPSCLASSID)
		{
			return pObj;
		}
	}

	return NULL;
}