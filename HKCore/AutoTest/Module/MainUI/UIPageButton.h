#pragma once
//#include "exbaseobject.h"
#include "..\..\..\Module\BaseClass\exbaseobject.h"
#include "PMXmlRWKey.h"

class CUIPageButton :
	public CExBaseObject
{
public:
	CUIPageButton(void);
	~CUIPageButton(void);

public:

	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strPageButton;     }
	virtual UINT GetClassID() {        return UIPAGEBUTTONCLASSID;                               }

	CString m_strPara;
	CString m_strBmpFile;
	LONG m_nOptr;
};
