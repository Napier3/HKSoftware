#include "StdAfx.h"
#include "UIGroups.h"
#include "UIGroup.h"

CUIGroups::CUIGroups(void)
{
}

CUIGroups::~CUIGroups(void)
{
	DeleteAll();
}

long CUIGroups::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CUIGroups::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CUIGroups::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}

CExBaseObject* CUIGroups::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CPMXmlRWKey::g_pPMXmlRWKeys->m_strGroup)
	{
		CUIGroup* pUIGroup = new CUIGroup;
		return pUIGroup;
	}
	else
		return 0;
}

CExBaseObject* CUIGroups::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}

