#include "StdAfx.h"
#include "Version.h"

CVersion::CVersion(void)
{
}

CVersion::~CVersion(void)
{
	DeleteAll();
}

void CVersion::Init()
{
	
}
long CVersion::InitAfterSerialize()
{
	return 0;
}

long CVersion::IsEqual(CExBaseList* pObj)
{
	return 0;
}
long CVersion::Copy(CExBaseList *pDesObj)
{
	return 0;
}
CExBaseObject* CVersion::Clone()
{
	return 0;
}
CExBaseObject* CVersion::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID==CPMXmlRWKey::g_pPMXmlRWKeys->m_strSubUICfgItem)
	{
		CMainUIItem* pMainUIItem = new CMainUIItem;
		return pMainUIItem;
	}
	else
		return 0;
}
CExBaseObject* CVersion::CreateNewChild(long nClassID, BOOL &bAddToTail)
{
	return 0;
}



long CVersion::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	return 0;
}

long CVersion::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CVersion::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{

	return 0;
}