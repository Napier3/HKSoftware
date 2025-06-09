#pragma once
#include "..\baseclass\exbaseobject.h"
#include "XmlDbDefine.h"

class CXmlDbTag :
	public CExBaseObject
{
public:
	CXmlDbTag(void);
	virtual ~CXmlDbTag(void);

	//属性
	CString m_strData;
	
	//方法
	virtual UINT GetClassID()	{	return CLASSID_XMLDBTAG;	}
	virtual void Init();
	virtual void InitAfterSerialize();
	
	//串行化
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strTagKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	//树形控件相关的操作
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);
};
