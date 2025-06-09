#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "TXmlDbTags.h"
#include "TXmlDbTag.h"

class CTXmlDbTable :
	public CExBaseList
{
public:
	CTXmlDbTable(void);
	virtual ~CTXmlDbTable(void);

	//属性
	CTXmlDbTags *m_pTags;

	//方法
	virtual UINT GetClassID()	{	return CLASSID_TXMLDBTABLE;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//串行化
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDbTableKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//树形控件相关的操作
	//virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	//查找模板表
	CTXmlDbTable *GetTDbTable(const CString &strTableID);

	//查找自身属性
	CTXmlDbTag *GetAttr(const CString &strTTagID);
	long GetAttrIndex(const CString &strTTagID);
};
