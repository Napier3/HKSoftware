#pragma once
#include "..\baseclass\exbaseobject.h"
#include "XmlDbDefine.h"

class CTXmlDbTag :
	public CExBaseObject
{
public:
	CTXmlDbTag(void);
	virtual ~CTXmlDbTag(void);

	//属性
	CString m_strDataType;
	LONG    m_nIsKey;

	//方法
	virtual UINT GetClassID()	{	return CLASSID_TXMLDBTAG;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//串行化
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strTagKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
