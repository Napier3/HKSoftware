#pragma once
//#include "exbaselist.h"
#include "..\..\..\Module\BaseClass\exbaselist.h"
#include "PMXmlRWKey.h"

class CUIGroups :
	public CExBaseList
{
public:
	CUIGroups(void);
	~CUIGroups(void);
	//
	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//Create new Children Mathods
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strGroups;     }
	virtual UINT GetClassID() {        return UIGROUPSCLASSID;                               }

};
