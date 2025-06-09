#pragma once
#include "../../../module/baseclass/exbaseobject.h"
#include "ProtocolXmlRWKeys.h"
class CDataInterface :
	public CExBaseObject
{
public:
	CDataInterface(void);
	virtual ~CDataInterface(void);

	virtual UINT GetClassID(){ return PPCLASSID_PPDATAINTERFACE; };
	virtual BSTR GetXmlElementKey()  {  return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey;   }

	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	CString m_PkID;
	CString m_ProID;
};
