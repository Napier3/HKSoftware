#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "TXmlDbTable.h"

class CTXmlDatabase :
	public CExBaseList
{
public:
	CTXmlDatabase(void);
	virtual ~CTXmlDatabase(void);

	//属性
	CString m_strDbName;
	CString m_strDbID;

	//方法
	virtual UINT GetClassID()	{	return CLASSID_TXMLDATABASE;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//串行化
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDbKey;     }
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

	//文件打开/保存
	BOOL OpenXmlFile(const CString& strFile);
	BOOL SaveXmlFile(const CString& strFile);

	//查找
	CTXmlDbTable *GetTDbTable(const CString &strID);
};
