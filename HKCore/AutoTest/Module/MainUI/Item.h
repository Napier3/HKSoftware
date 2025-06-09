#pragma once
#include "..\..\..\Module\BaseClass\exbaseobject.h"

#include "PMXmlRWKey.h"

class CItem :
	public CExBaseObject
{
public:
	CItem(void);
	~CItem(void);

	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	void SetFile(const CString& strFileName){m_strFile = strFileName ;}
	void SetProgram(const CString& strProgram){m_strProgram = strProgram;}
	CString GetFile(){return m_strFile;}

	virtual UINT GetClassID() {        return ITEMCLASSID;                               }
	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strItem;     }

public:
	// Ù–‘
	CString m_strFile;
	CString m_strProgram;
	CString m_strBmpFile;
	LONG	m_nShow;

};
