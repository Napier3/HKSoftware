#pragma once
//#include "exbaseobject.h"
#include "..\..\..\Module\BaseClass\exbaseobject.h"
#include "PMXmlRWKey.h"

class CMainUIItem :
	public CExBaseObject
{
public:
	CMainUIItem(void);
	~CMainUIItem(void);
public:
		CString m_strConfigFile;

		virtual long IsEqual(CExBaseObject* pObj);
		virtual long Copy(CExBaseObject* pDesObj);
		virtual CExBaseObject* Clone();
		//基本方法
		virtual void Init();
		virtual long InitAfterSerialize();

		//Add Serialize Mathods 
		virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
		virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

		BOOL InitMacroUIConfig();

		virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strSubUICfgItem;     }
		virtual UINT GetClassID() {        return MAINUIITEMCLASSID;                               }
};
