#pragma once
#include "PpPackage.h"


class CPpParsePackge :	public CPpPackage
{
public:
	CPpParsePackge(void);
	~CPpParsePackge(void);

public:
	virtual UINT GetClassID() {        return CLASSID_BASECLASS;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRPackageKey;     }

	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

};
