#pragma once
#include "..\..\..\Module\BaseClass\exbaselist.h"
#include "Version.h"
#include "PMXmlRWKey.h"

class CMainUIConfig :
	public CExBaseList
{
public:
	CMainUIConfig(void);
	~CMainUIConfig(void);

	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseList* Clone();

public:
	CVersion* m_pCurrentVersion;
	CString m_strCurrVersion;

public:
	//基本方法
	virtual void Init();
	virtual long InitAfterSerialize();

	//文件读写
	BOOL ReadFromFile();
	BOOL WriteToFile();

	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//Create new Children Mathods
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);


	void OpenXMLFile(CString strFileName);
	void SaveXMLFile(CString strFileName);

	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strMainUIConfig;     }
	virtual UINT GetClassID() {        return MAINUICONFIGCLASSID;                               }

	void SetCurrentVersion();
};
