#pragma once
#include "d:\workpm\source\module\baseclass\exbaseobject.h"
#include "PMXmlRWKey.h"

class CUICfgFont :
	public CExBaseObject
{
public:
	CUICfgFont(void);
	~CUICfgFont(void);

	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return m_PMXmlRWKey.m_strFont;     }

	//Create new Children Mathods
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	virtual UINT GetClassID();

	CPMXmlRWKey m_PMXmlRWKey;
protected:
	CString m_strBkColor;
	CString m_strColor;
	LONG m_nitalic;
	LONG m_nSize;
	LONG m_nBold;
};
