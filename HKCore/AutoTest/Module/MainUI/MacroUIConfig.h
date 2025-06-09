#pragma once
//#include "exbaselist.h"
#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "PMXmlRWKey.h"

class CUIPage;

class CMacroUIConfig :
	public CExBaseList
{
public:
	CMacroUIConfig(void);
	~CMacroUIConfig(void);
	//ÎÄ¼þ¶ÁÐ´
	BOOL ReadFromFile();
	BOOL WriteToFile(CString strFileName);

	void OpenXMLFile(CString strFileName);
	//XML¶ÁÐ´


	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//Create new Children Mathods
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	virtual BSTR GetXmlElementKey()  {      return m_PMXmlRWKey.m_strSubUICfg;     }
	virtual UINT GetClassID() {        return MACROUICONFIGCLASSID;                               }

	CPMXmlRWKey m_PMXmlRWKey;
	//XML key

	CString m_strActivePage;
	//CUIPage* m_pActivePage;
	CXmlRWKeys* m_pXMLKeys;
};
