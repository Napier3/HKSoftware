#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "XmlDbTags.h"

class CXmlDbData :
	public CExBaseList
{
public:
	CXmlDbData(void);
	virtual ~CXmlDbData(void);

	//属性
	CXmlDbTags *m_pTags;

	//方法
	virtual UINT GetClassID()	{	return CLASSID_XMLDBDATA;	}
	virtual void Init();
	virtual long InitAfterSerialize();
	
	//串行化
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDataKey;     }
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
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	//获取自身属性数据
	BOOL GetAttribute(const CString &strTID, CString &strAttrData);
	BOOL GetAttribute(UINT nTIDIndex, CString &strAttrData);

	//查找子对象数据
	CXmlDbData* Find(UINT nTIDIndex, const CString& strAttData);
};
