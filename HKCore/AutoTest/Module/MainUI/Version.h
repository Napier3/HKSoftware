#pragma once
//#include "exbaselist.h"
#include "..\..\..\Module\BaseClass\exbaselist.h"
#include "MainUIItem.h"
#include "PMXmlRWKey.h"

class CVersion :
	public CExBaseList
{
public:
	CVersion(void);
	~CVersion(void);
public:
	//基本方法
	virtual void Init();
	virtual long InitAfterSerialize();
	//串行化

	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual long IsEqual(CExBaseList* pObj);
	virtual long Copy(CExBaseList* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strVersion;     }
	virtual UINT GetClassID() {        return VERSIONCLASSID;                               }

public:
	CString m_strActiveItem;
	CMainUIItem* m_pActiveItem;

	CMainUIItem* pCurrentItem;
};
