#pragma once
#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "PMXmlRWKey.h"
#include "UIGroups.h"

class CUIPage :
	public CExBaseList
{
public:
	CUIPage(void);
	~CUIPage(void);
	//	virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	
	//Add Serialize Mathods 
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//Create new Children Mathods
	virtual CExBaseObject* CreateNewChild(long nClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	CExBaseObject*  GetGroups();
	virtual BSTR GetXmlElementKey()  {      return CPMXmlRWKey::g_pPMXmlRWKeys->m_strPage;     }

	virtual UINT GetClassID(){return UIPAGECLASSID ;}

protected:
	LONG m_nbtnWidth;

};
